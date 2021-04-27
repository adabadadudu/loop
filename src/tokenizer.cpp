#include "tokenizer.h"

bool Tokenizer::isEOF()
{
    if (index < src.length() && lastChar != '\0' && lastChar != char(-1))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Tokenizer::advance(int offset)
{
    if (offset + index < src.length())
    {
        index += offset;
    }
    else
    {
        index = src.length();
    }
    lastChar = src[index];
}

char Tokenizer::peek(int offset)
{
    if (offset + index < src.length())
    {
        return src[index + offset];
    }
    else
    {
        return src[src.length() - 1];
    }
}

std::vector<Token> tokenize(std::string data)
{
    std::vector<Token> tokens;
    Tokenizer tokenizer;
    tokenizer.src = data;
    tokenizer.lastChar = tokenizer.src[0];
    while (!tokenizer.isEOF())
    {
        tokenizer.lastToken.value.clear();
        while (isspace(tokenizer.lastChar))
        {
            tokenizer.advance(1);
        }
        if (tokenizer.lastChar == '"')
        {
            int peekBy = 1;
            std::string value;
            value += tokenizer.lastChar;
            while (tokenizer.peek(peekBy) != '"')
            {
                value += tokenizer.peek(peekBy);
                ++peekBy;
            }
            if (value == "\"")
            {
                Error::syntax(Error::MISSING_QUOTATION_MARK, "Missing quotation mark", data.c_str(), tokenizer.index + 1, tokenizer.index + 1);
            }
            tokenizer.lastToken.kind = T_STRING;
            tokenizer.lastToken.value = value;
            tokenizer.advance(peekBy);
        }
        else if (tokenizer.lastChar == '=')
        {
            if (tokenizer.peek(1) == '=')
            {
                tokenizer.lastToken.kind = T_DOUBLE_EQUAL;
                tokenizer.lastToken.value = '=';
                tokenizer.advance(1);
            }
            else
            {
                tokenizer.lastToken.kind = T_EQUAL;
            }
        }
        else if (tokenizer.lastChar == '+')
        {
            if (tokenizer.peek(1) == '=')
            {
                tokenizer.lastToken.kind = T_EQUAL_PLUS;
                tokenizer.lastToken.value = '+';
                tokenizer.advance(1);
            }
            else if (tokenizer.peek(1) == '+')
            {
                tokenizer.lastToken.kind = T_DOUBLE_PLUS;
                tokenizer.lastToken.value = '+';
                tokenizer.advance(1);
            }
            else
            {
                tokenizer.lastToken.kind = T_PLUS;
            }
        }
        else if (tokenizer.lastChar == '-')
        {
            if (tokenizer.peek(1) == '=')
            {
                tokenizer.lastToken.kind = T_EQUAL_MINUS;
                tokenizer.lastToken.value = '-';
                tokenizer.advance(1);
            }
            else if (tokenizer.peek(1) == '-')
            {
                tokenizer.lastToken.kind = T_DOUBLE_MINUS;
                tokenizer.lastToken.value = '-';
                tokenizer.advance(1);
            }
            else
            {
                tokenizer.lastToken.kind = T_MINUS;
            }
        }
        else if (tokenizer.lastChar == '|')
        {
            if (tokenizer.peek(1) == '=')
            {
                tokenizer.lastToken.kind = T_EQUAL_PIPE;
                tokenizer.lastToken.value = '|';
                tokenizer.advance(1);
            }
            else if (tokenizer.peek(1) == '|')
            {
                tokenizer.lastToken.kind = T_DOUBLE_PIPE;
                tokenizer.lastToken.value = '|';
                tokenizer.advance(1);
            }
            else
            {
                tokenizer.lastToken.kind = T_PIPE;
            }
        }
        else if (tokenizer.lastChar == '<')
        {
            if (tokenizer.peek(1) == '=')
            {
                tokenizer.lastToken.kind = T_EQUAL_LESSER_BRACKET;
                tokenizer.lastToken.value = '<';
                tokenizer.advance(1);
            }
            else
            {
                tokenizer.lastToken.kind = T_LESSER_BRACKET;
            }
        }
        else if (tokenizer.lastChar == '>')
        {
            if (tokenizer.peek(1) == '=')
            {
                tokenizer.lastToken.kind = T_EQUAL_GREETER_BRACKET;
                tokenizer.lastToken.value = '>';
                tokenizer.advance(1);
            }
            else
            {
                tokenizer.lastToken.kind = T_GREETER_BRACKET;
            }
        }
        else if (tokenizer.lastChar == '/')
        {
            tokenizer.lastToken.kind = T_SLASH;
        }
        else if (tokenizer.lastChar == '%')
        {
            tokenizer.lastToken.kind = T_PERCENT;
        }
        else if (tokenizer.lastChar == ';')
        {
            tokenizer.lastToken.kind = T_SEMICOLON;
        }
        else if (tokenizer.lastChar == '(')
        {
            tokenizer.lastToken.kind = T_LEFT_BRACKET;
        }
        else if (tokenizer.lastChar == ')')
        {
            tokenizer.lastToken.kind = T_RIGHT_BRACKET;
        }
        else if (tokenizer.lastChar == '{')
        {
            tokenizer.lastToken.kind = T_LEFT_CURLY_BRACKET;
        }
        else if (tokenizer.lastChar == '}')
        {
            tokenizer.lastToken.kind = T_RIGHT_CURLY_BRACKET;
        }
        else
        {
            Error::syntax(Error::UNRECOGNIZED_TOKEN, "Unrecognized Token", data.c_str(), tokenizer.index + 1, tokenizer.index + 1);
        }
        tokenizer.lastToken.value += tokenizer.lastChar;
        tokenizer.lastToken.position = {tokenizer.index + 1, tokenizer.index + 1};
        tokens.push_back(tokenizer.lastToken);
        tokenizer.advance(1);
    }
    return tokens;
}
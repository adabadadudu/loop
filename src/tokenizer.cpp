#include "tokenizer.h"

bool Tokenizer::isEOF() // End Of File
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

bool Tokenizer::isLCOF() // Is Last Char Of File
{
    if (index < src.length() - 1)
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
        return src[src.length()];
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
            if (tokenizer.isLCOF())
            {
                Error::syntax(Error::MISSING_QUOTATION_MARK, "Quated String Must Be Finished", tokenizer.src.c_str(), tokenizer.index);
            }
            tokenizer.lastToken.value += tokenizer.lastChar;
            tokenizer.advance(1);
            while (!tokenizer.isEOF())
            {
                if (tokenizer.lastChar == '"')
                {
                    tokenizer.lastToken.kind = T_STRING;
                    break;
                }
                else
                {
                    if (tokenizer.lastChar == '\\' && tokenizer.peek(1) == '"')
                    {
                        tokenizer.lastToken.value += tokenizer.lastChar;
                        tokenizer.advance(1);
                    }
                    tokenizer.lastToken.value += tokenizer.lastChar;
                    tokenizer.advance(1);
                }
            }
        }
        else if (tokenizer.lastChar == '\'')
        {
            if (tokenizer.isLCOF())
            {
                Error::syntax(Error::MISSING_APOSTROPHE_MARK, "Quated Char Must Be Finished", tokenizer.src.c_str(), tokenizer.index);
            }
            tokenizer.lastToken.value += tokenizer.lastChar;
            tokenizer.advance(1);
            if (tokenizer.lastChar == '\'')
            {
                Error::syntax(Error::NO_NULL_CHAR, "Chars Must Be Initialized", tokenizer.src.c_str(), tokenizer.index);
            }
            else
            {
                if (tokenizer.lastChar == '\\')
                {
                    tokenizer.lastToken.value += tokenizer.lastChar;
                    tokenizer.advance(1);
                }

                tokenizer.lastToken.value += tokenizer.lastChar;
                tokenizer.advance(1);

                if (tokenizer.lastChar != '\'')
                {
                    Error::syntax(Error::MORE_THAN_ONE_BYTE, "You Can't Give More Than 1 Byte To Char", tokenizer.src.c_str(), tokenizer.index);
                }
            }
            tokenizer.lastToken.kind = T_CHAR;
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
                tokenizer.lastToken.kind = T_LEFT_ANGLE_BRACKET;
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
                tokenizer.lastToken.kind = T_RIGHT_ANGLE_BRACKET;
            }
        }
        else if (tokenizer.lastChar == '&')
        {
            if (tokenizer.peek(1) == '&')
            {
                tokenizer.lastToken.kind = T_LOGIC_AND;
                tokenizer.lastToken.value = '&';
                tokenizer.advance(1);
            }
            else
            {
                tokenizer.lastToken.kind = T_AND;
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
            tokenizer.lastToken.kind = T_LEFT_ROUNDED_BRACKET;
        }
        else if (tokenizer.lastChar == ')')
        {
            tokenizer.lastToken.kind = T_RIGHT_ROUNDED_BRACKET;
        }
        else if (tokenizer.lastChar == '{')
        {
            tokenizer.lastToken.kind = T_LEFT_CURLY_BRACKET;
        }
        else if (tokenizer.lastChar == '}')
        {
            tokenizer.lastToken.kind = T_RIGHT_CURLY_BRACKET;
        }
        else if (tokenizer.lastChar == '[')
        {
            tokenizer.lastToken.kind = T_LEFT_SQUARE_BRACKET;
        }
        else if (tokenizer.lastChar == ']')
        {
            tokenizer.lastToken.kind = T_RIGHT_SQUARE_BRACKET;
        }
        else
        {
            Error::syntax(Error::UNRECOGNIZED_TOKEN, "Unrecognized Token", data.c_str(), tokenizer.index);
        }
        tokenizer.lastToken.value += tokenizer.lastChar;
        tokenizer.lastToken.position = {tokenizer.index + 1, tokenizer.index + 1};
        tokens.push_back(tokenizer.lastToken);
        tokenizer.advance(1);
    }
    return tokens;
}
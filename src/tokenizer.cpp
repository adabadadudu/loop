#include "tokenizer.h"

bool Tokenizer::isEOF()
{
    if (columnIndex < lastLine.length() && lastChar != '\0' && lastChar != char(-1))
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
    if (offset + columnIndex < lastLine.length())
    {
        columnIndex += offset;
    }
    else
    {
        columnIndex = lastLine.length();
    }
    lastChar = lastLine[columnIndex];
}

char Tokenizer::peek(int offset)
{
    if (offset + columnIndex < lastLine.length())
    {
        return lastLine[columnIndex + offset];
    }
    else
    {
        return lastLine[lastLine.length() - 1];
    }
}

std::vector<Token> tokenize(const char *path)
{
    std::vector<Token> tokens;
    std::ifstream file(path);
    if (file.is_open())
    {
        Tokenizer tokenizer;
        while (getline(file, tokenizer.lastLine))
        {
            tokenizer.lastChar = tokenizer.lastLine[0];
            while (!tokenizer.isEOF())
            {
                tokenizer.lastToken.value.clear();
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
                        Error::syntax(Error::MISSING_QUOTATION_MARK, "Missing quotation mark", path, tokenizer.lineIndex + 1, tokenizer.columnIndex + 1);
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
                    Error::syntax(Error::UNRECOGNIZED_TOKEN, "Unrecognized Token", path, tokenizer.lineIndex + 1, tokenizer.columnIndex + 1);
                }
                tokenizer.lastToken.value += tokenizer.lastChar;
                tokenizer.lastToken.position = {tokenizer.lineIndex + 1, tokenizer.columnIndex + 1};
                tokens.push_back(tokenizer.lastToken);
                tokenizer.advance(1);
            }
            tokenizer.columnIndex = 0;
            tokenizer.lineIndex++;
        }
    }
    else
    {
        Error::compiler(Error::FILE_NOT_FOUND, "No Such File");
    }
    return tokens;
}
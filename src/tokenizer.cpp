#include "tokenizer.h"

bool isEOF(Tokenizer tokenizer)
{
    if (tokenizer.columnIndex < tokenizer.lastLine.length() && tokenizer.lastChar != '\0' && tokenizer.lastChar != char(-1))
    {
        return false;
    }
    else
    {
        return true;
    }
}

void advance(Tokenizer &tokenizer, size_t offset)
{
    if (offset + tokenizer.columnIndex < tokenizer.lastLine.length())
    {
        tokenizer.columnIndex += offset;
    }
    else
    {
        tokenizer.columnIndex = tokenizer.lastLine.length();
    }
    tokenizer.lastChar = tokenizer.lastLine[tokenizer.columnIndex];
}

char peek(Tokenizer tokenizer, size_t offset)
{
    if (offset + tokenizer.columnIndex < tokenizer.lastLine.length())
    {
        return tokenizer.lastLine[tokenizer.columnIndex + offset];
    }
    else
    {
        return tokenizer.lastLine[tokenizer.lastLine.length() - 1];
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
            while (!isEOF(tokenizer))
            {
                tokenizer.lastToken.value.clear();
                if (tokenizer.lastChar == '=')
                {
                    if (peek(tokenizer, 1) == '+')
                    {
                        tokenizer.lastToken.kind = T_EQUAL_PLUS;
                    }
                    else if (peek(tokenizer, 1) == '-')
                    {
                        tokenizer.lastToken.kind = T_EQUAL_MINUS;
                    }
                    else
                    {
                        tokenizer.lastToken.kind = T_EQUAL;
                        continue;
                    }
                    tokenizer.lastToken.value = '=';
                    advance(tokenizer, 1);
                }
                else if (tokenizer.lastChar == '"')
                {
                    int peekBy = 1;
                    std::string value;
                    value += peek(tokenizer, 0);
                    while(peek(tokenizer, peekBy) != '"')
                    {
                        value += peek(tokenizer, peekBy);
                        ++peekBy;
                    }
                    if(value == "\""){
                        Error::syntax(Error::MISSING_QUOTATION_MARK, "Missing quotation mark", path, tokenizer.lineIndex + 1, tokenizer.columnIndex + 1);
                    }
                    tokenizer.lastToken.kind = T_STRING;
                    tokenizer.lastToken.value = value;
                    advance(tokenizer, peekBy);
                }
                else if (tokenizer.lastChar == '+')
                {
                    tokenizer.lastToken.kind = T_PLUS;
                }
                else if (tokenizer.lastChar == '-')
                {
                    tokenizer.lastToken.kind = T_MINUS;
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
                advance(tokenizer, 1);
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
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
                tokenizer.lastToken.value = tokenizer.lastChar;
                if (tokenizer.lastChar == '=')
                {
                    tokenizer.lastToken.kind = T_EQUAL;
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
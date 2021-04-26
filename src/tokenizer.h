#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "error.h"

enum TOKENS
{
    T_ID,
    T_STRING,
    T_CHAR,
    T_INT,
    T_SEMICOLON,
    T_EQUAL
};

struct TokenPosition
{
    size_t line = 1;
    size_t column = 1;
};

struct Token
{
    std::string value;
    TOKENS kind;
    TokenPosition position;
};

struct Tokenizer
{
    size_t columnIndex = 0;
    size_t lineIndex = 0;
    std::string lastLine;
    char lastChar;
    Token lastToken;
};

std::vector<Token> tokenize(const char *path);

#endif //TOKENIZER_H
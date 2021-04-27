#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <string>
#include <vector>
#include <iostream>
#include "error.h"

enum TOKENS
{
    T_ID, // Identifiers: using, return and etc
    T_STRING, // "String"
    T_CHAR, // 'Char'
    T_INT, // 27
    T_EQUAL, // =
    T_PLUS, // +
    T_MINUS, // -
    T_SLASH, // /
    T_PERCENT, // %
    T_PIPE, // |
    T_SEMICOLON, // ;
    T_LEFT_BRACKET, // (
    T_RIGHT_BRACKET, // )
    T_LEFT_CURLY_BRACKET, // {
    T_RIGHT_CURLY_BRACKET, // }
    T_LESSER_BRACKET, // <
    T_GREETER_BRACKET, // >
    T_DOUBLE_EQUAL, // ==
    T_DOUBLE_PLUS, // ++
    T_DOUBLE_MINUS, // --
    T_DOUBLE_PIPE, // ||
    T_EQUAL_PLUS, // +=
    T_EQUAL_MINUS, // -=
    T_EQUAL_PIPE, // |=
    T_EQUAL_LESSER_BRACKET, // <=
    T_EQUAL_GREETER_BRACKET, // >=
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
    size_t index = 0;
    std::string src;
    char lastChar;
    Token lastToken;
    bool isEOF();
    bool isLCOF();
    char peek(int offset);
    void advance(int offset);
};

std::vector<Token> tokenize(std::string data);

#endif //TOKENIZER_H
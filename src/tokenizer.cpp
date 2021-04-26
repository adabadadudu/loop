#include "tokenizer.h"

bool isEOF(Tokenizer tokenizer){
    if (tokenizer.columnIndex < tokenizer.lastLine.length() && tokenizer.lastChar != '\0' && tokenizer.lastChar != char(-1)){
        return false;
    }else{
        return true;
    }
}

void advance(Tokenizer &tokenizer, size_t offset){
    if (offset + tokenizer.columnIndex < tokenizer.lastLine.length()){
        tokenizer.columnIndex += offset;
    }else{
        tokenizer.columnIndex = tokenizer.lastLine.length();
    }
    tokenizer.lastChar = tokenizer.lastLine[tokenizer.columnIndex];
}

std::vector<Token> tokenize(const char *path){
    std::vector<Token> tokens;
    std::ifstream file(path);
    if (file.is_open()){
        Tokenizer tokenizer;
        size_t lineIndex = 0;
        while (getline(file, tokenizer.lastLine)){
            tokenizer.lastChar = tokenizer.lastLine[0];
            while (!isEOF(tokenizer)){
                if (tokenizer.lastChar == '='){
                    tokenizer.lastToken.value = tokenizer.lastChar;
                    tokenizer.lastToken.kind = T_EQUAL;
                    tokenizer.lastToken.position = {lineIndex + 1, tokenizer.columnIndex + 1};
                    tokens.push_back(tokenizer.lastToken);
                    advance(tokenizer, 1);
                }else{
                    Error::syntax(Error::UNRECOGNIZED_TOKEN, "Unrecognized Token", path, tokenizer.lastToken.position.line, tokenizer.lastToken.position.column);
                }
            }
            tokenizer.columnIndex = 0;
            lineIndex++;
        }
    }else{
        Error::compiler(Error::FILE_NOT_FOUND, "No Such File");
    }
    return tokens;
}
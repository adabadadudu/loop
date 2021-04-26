#include <iostream>
#include "tokenizer.h"

int main(int argc, char *argv[])
{
    if (argc > 0)
    {
        std::vector<Token> tokens = tokenize(argv[1]);
        for (Token token : tokens)
        {
            std::cout << token.kind << " : " << token.value << "\n";
        }
    }
    return 0;
}

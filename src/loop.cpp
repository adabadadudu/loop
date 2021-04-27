#include <iostream>
#include "tokenizer.h"
#include "io.h"

int main(int argc, char *argv[])
{
    if (argc > 0)
    {
        IO io;
        io.read(argv[1]);
        std::vector<Token> tokens = tokenize(io.reads[0].data);
        for (Token token : tokens)
        {
            std::cout << token.kind << " : " << token.value << "\n";
        }
    }
    return 0;
}

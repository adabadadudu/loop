#include <iostream>
#include "tokenizer.h"
#include "io.h"

int main(int argc, char *argv[])
{
    if (argc > 0)
    {
        IO io;
        for (int i = 0; i < argc - 1; i++)
        {
            io.read(argv[i + 1]);
            std::vector<Token> tokens = tokenize(io.reads[i].data);
            for (Token token : tokens)
            {
                std::cout << token.kind << " : " << token.value << "\n";
            }
        }
    }
    return 0;
}

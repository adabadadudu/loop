#include "error.h"

void Error::compiler(ERRORS code, const char *message)
{
    std::cerr << "\x1b[0;91;1mERROR[E" << std::setfill('0') << std::setw(3) << code << "]\x1b[0;1m: " << message << std::endl;
    exit(1);
}

void Error::syntax(ERRORS code, const char *message, const char *file_path, size_t line, size_t column)
{
    std::cerr << "\x1b[91;1mE" << code << " \x1b[0mIn \x1b[4m" << file_path << ':' << line << ':' << column << "\n\x1b[0;91;1mERROR\x1b[0;1m: " << message << std::endl;
    exit(1);
}
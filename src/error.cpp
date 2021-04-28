#include "error.h"
#ifdef _WIN32
#define color 0
#else
#define color 1
#endif

void Error::compiler(ERRORS code, const char *message)
{
    if(color){
        std::cerr << "\x1b[0;91;1mERROR[E" << std::setfill('0') << std::setw(3) << code << "]\x1b[0;1m: " << message << std::endl;
    }else {
        std::cerr "E" << std::setfill('0') << std::setw(3) << code << "]:" << message << std::endl;
    exit(1);
}

void Error::syntax(ERRORS code, const char *message, const char *file_path, size_t index)
{
    std::cerr << "\x1b[91;1mE" << code << " \x1b[0mIn \x1b[4m" << file_path << ':' << index << "\n\x1b[0;91;1mERROR\x1b[0;1m: " << message << std::endl;
    exit(1);
}

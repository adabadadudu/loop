#ifndef ERROR_H
#define ERROR_H
#include <iostream>
#include <iomanip>
#include <limits>

namespace Error
{
    enum ERRORS
    {
        FILE_NOT_FOUND,
        UNRECOGNIZED_TOKEN
    };
    void syntax(ERRORS code, const char *message, const char *file_path, size_t line, size_t column);
    void compiler(ERRORS code, const char *message);
}

#endif //ERROR_H
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
        IS_DIRECTORY,
        IST_REGULAR_FILE,
        UNRECOGNIZED_TOKEN,
        MISSING_QUOTATION_MARK
    };
    void syntax(ERRORS code, const char *message, const char *file_path, size_t index);
    void compiler(ERRORS code, const char *message);
}

#endif //ERROR_H
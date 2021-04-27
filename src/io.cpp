#include "io.h"

void IO::read(std::string path)
{
    namespace fs = std::filesystem;
    if (!fs::exists(path))
    {
        Error::compiler(Error::FILE_NOT_FOUND, "Expected File Does not Exists");
    }
    else if (fs::is_directory(path))
    {
        Error::compiler(Error::IS_DIRECTORY, "Expected File Is A Directory");
    }
    else if (!fs::is_regular_file(path))
    {
        Error::compiler(Error::IST_REGULAR_FILE, "Expected File Is't Regular");
    }

    File file;
    std::stringstream content;
    std::ifstream in(path);
    content << in.rdbuf();
    in.close();

    file.path = path;
    file.data = content.str();
    reads.push_back(file);
}
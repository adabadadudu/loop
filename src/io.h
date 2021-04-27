#ifndef IO_H
#define IO_H

#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "error.h"

struct File
{
    std::string path;
    std::string data;
};


struct IO
{
    std::vector<File> reads;
    void read(std::string path);
    void write(File file);
};


#endif
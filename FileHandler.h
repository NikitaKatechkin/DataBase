#ifndef FILEHANDLER_H_INCLUDED
#define FILEHANDLER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

namespace FileHandler
{
    const char END_OF_TEXT_ASCII_SYMBOL = '\3';

    bool createFile(const std::string& file_name);
    bool deleteFile(const std::string& file_name);
}

#endif // FILEHANDLER_H_INCLUDED

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

    bool openReadFile(const std::string& file_name, std::ifstream& file_read_stream);
    bool openRewriteFile(const std::string& file_name, std::ofstream& file_write_stream);
    bool openWriteFile(const std::string& file_name, std::ofstream& file_write_stream);
    bool closeFile(std::ifstream& file_read_stream);
    bool closeFile(std::ofstream& file_write_stream);
}

#endif // FILEHANDLER_H_INCLUDED

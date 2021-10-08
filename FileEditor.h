#ifndef FILEEDITOR_H_INCLUDED
#define FILEEDITOR_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

#include "FileHandler.h"

namespace FileEditor
{
    bool goToLine(unsigned int l_line_number, std::ifstream& l_file);
    bool copyLine(unsigned int l_line_number, std::ifstream& l_file, std::string& l_line);
    bool copyLineV2(unsigned int l_line_number, std::string l_file_path, std::string& l_line);
    bool changeLine(int l_line_number, std::string l_file_path,
                    std::string l_new_line, std::string l_end);
    bool changeLineRemoveCompetable(int l_line_number, std::string l_file_path,
                                                std::string l_new_line, std::string l_end);
    bool insertLine(int l_line_number, std::string l_file_path,
                    std::string l_new_line, std::string l_end);
    bool removeLine(int l_line_number, std::string l_file_path);
    bool addToLine(int l_line_number, std::string l_file_path, std::string l_new_line,
                   std::string l_end, int l_addition_index = -1);
}

#endif // FILEEDITOR_H_INCLUDED

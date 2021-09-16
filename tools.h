#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

namespace tools{
    /*enum FieldType
    {
        FIELD_TYPE_INT = 0,
        FIELD_TYPE_FLOAT,
        FIELD_TYPE_STRING,
        FIELD_TYPE_BOOLEAN
    };*/

    struct Field
    {
        std::string m_name;
        bool m_key_field;
        //FieldType m_type;
    };

    bool createDBfile(std::string l_DB_name);
    bool addField(Field l_field, std::string l_DB_file_path);

    bool goToLine(int l_line_number, std::ifstream& l_file);
    bool changeLine(int l_line_number, std::string l_DB_file_path, std::string l_new_line, std::string l_end = ";");
    bool insertLine(int l_line_number, std::string l_DB_file_path, std::string l_new_line, std::string l_end = ";");
    bool addToLine(int l_line_number, std::string l_DB_file_path, std::string l_new_line, std::string l_end = ";");

    template <typename T>
    void input(std::string l_input_invite, T* l_to_record)
    {
        std::cout << l_input_invite << ": ";
        std::cin >> *l_to_record;
    }

    bool removeLine(int l_line_number, std::string l_DB_file_path);
    std::vector<int> searchForStr(std::string l_DB_file_path, std::string l_str_to_find);
}

#endif // TOOLS_H_INCLUDED

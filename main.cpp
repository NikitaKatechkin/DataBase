#include "DataBase.h"
//#include "tools.h"
/*enum FieldType
{
    FIELD_TYPE_INT = 0,
    FIELD_TYPE_FLOAT,
    FIELD_TYPE_STRING,
    FIELD_TYPE_BOOLEAN
};

struct Field
{
    std::string m_name;
    bool m_key_field;
    FieldType m_type;
};

bool createDBfile(std::string l_DB_name);
bool addField(Field l_field, std::string l_DB_file_path);

bool goToLine(int l_line_number, std::ifstream& l_file);
bool changeLine(int l_line_number, std::string l_DB_file_path, std::string l_new_line, std::string l_end = ";");
bool insertLine(int l_line_number, std::string l_DB_file_path, std::string l_new_line, std::string l_end = ";");
bool addToLine(int l_line_number, std::string l_DB_file_path, std::string l_new_line, std::string l_end = ";");*/

int main()
{
    //tools::createDBfile("file.txt");
    //changeLine(0, "file.txt", "it's nice");
    //insertLine(0, "file.txt", "inserted string");
    //addToLine(0, "file.txt", "additional string");
    /*tools::addField({"name", true, tools::FieldType::FIELD_TYPE_STRING}, "file.txt");
    tools::addField({"age", false, tools::FieldType::FIELD_TYPE_INT}, "file.txt");
    tools::addField({"sex", false, tools::FieldType::FIELD_TYPE_BOOLEAN}, "file.txt");*/

    /*bool answer;
    tools::input("Input num", &answer);
    std::cout << answer << std::endl;*/

    DataBase DB;

    return 0;
}

/*bool createDBfile(std::string l_DB_name)
{
    std::cout << "createDBfile(): " << std::endl;

    std::ifstream file_read(l_DB_name);
    if(file_read.is_open())
    {
        std::cout << "DB already exist" << std::endl;
    }
    else
    {
        std::ofstream file_create(l_DB_name);
        if(file_create.is_open())
        {
            std::cout << "DB file " << l_DB_name << " was created" << std::endl;
            file_create << '\n';
            file_create.close();
            return true;
        }
        else
        {
            std:: cout << "Can't create file with " << l_DB_name << " name" << std::endl;
        }
    }

    std::cout << "createDBfile() END_FUNC" << std::endl;
    return false;
}

bool addField(Field l_field, std::string l_DB_file_path)
{
    std::cout << "createDBfile(): " << std::endl;

    addToLine(0, l_DB_file_path, l_field.m_name);
    addToLine(1, l_DB_file_path, std::to_string(int(l_field.m_key_field)));
    addToLine(2, l_DB_file_path, std::to_string(int(l_field.m_type)));

    std::cout << "createDBfile() END_FUNC" << std::endl;
    return true;
}

bool goToLine(int l_line_number, std::ifstream& l_file)
{
    std::cout << "goToLine(): " << std::endl;

    bool success_flag = true;

    l_file.seekg(0);
    std::string tmp_line;
    for (int i = 0; i < l_line_number; i++)
    {
        if (l_file.eof())
        {
            success_flag = false;
            break;
        }
        std::getline(l_file, tmp_line);
    }
    success_flag = success_flag && (l_file.tellg() != -1);

    if (success_flag) { std::cout << "Success" << std::endl; l_file.seekg(l_file.tellg()); }
    else { std::cout << "EOF REACHED" << std::endl; l_file.seekg(0); }

    std::cout << "goToLine() END_FUNC" << std::endl;
    return success_flag;
}

bool changeLine(int l_line_number, std::string l_DB_file_path, std::string l_new_line, std::string l_end)
{
    std::cout << "changeLine(): " << std::endl;

    std::ifstream tmp_read(l_DB_file_path);
    if(!tmp_read.is_open()) { std::cout << "Can't open file" << std::endl; return false; }
    if(!goToLine(l_line_number, tmp_read)) { std::cout << "Wrong Line Number" << std::endl; return false; }

    int insert_position = tmp_read.tellg();

    std::string data;
    std::getline(tmp_read, data);
    data = "";

    tmp_read.seekg(0);
    //std::cout << tmp_read.tellg() << std::endl;
    while(tmp_read.tellg() != insert_position)
    {
        std::string line;
        std::getline(tmp_read, line);
        data += (line + "\n");
    }

    data = data + l_new_line + l_end + std::string("\n");

    std::string line;
    std::getline(tmp_read, line);

    while(!tmp_read.eof())
    {
        std::getline(tmp_read, line);
        data += (line + "\n");
    }

    tmp_read.close();

    std::ofstream tmp_write(l_DB_file_path);
    tmp_write << data;
    tmp_write.close();

    std::cout << "Success" << std::endl;
    std::cout << "changeLine() END_FUNC" << std::endl;
    return true;
}

bool insertLine(int l_line_number, std::string l_DB_file_path, std::string l_new_line, std::string l_end)
{
    std::cout << "insertLine(): " << std::endl;

    std::ifstream tmp_read(l_DB_file_path);
    if(!tmp_read.is_open()) { std::cout << "Can't open file" << std::endl; return false; }
    if(!goToLine(l_line_number, tmp_read)) { std::cout << "Wrong Line Number" << std::endl; return false; }

    int insert_position = tmp_read.tellg();

    std::string data;
    std::getline(tmp_read, data);
    data = "";

    tmp_read.seekg(0);
    //std::cout << tmp_read.tellg() << std::endl;
    while(tmp_read.tellg() != insert_position)
    {
        std::string line;
        std::getline(tmp_read, line);
        data += (line + "\n");
    }

    data = data + l_new_line + l_end + std::string("\n");

    std::string line;

    while(!tmp_read.eof())
    {
        std::getline(tmp_read, line);
        data += (line + "\n");
    }

    tmp_read.close();

    std::ofstream tmp_write(l_DB_file_path);
    tmp_write << data;
    tmp_write.close();

    std::cout << "Success" << std::endl;
    std::cout << "insertLine() END_FUNC" << std::endl;
    return true;
}

bool addToLine(int l_line_number, std::string l_DB_file_path, std::string l_new_line, std::string l_end)
{
    std::cout << "addToLine(): " << std::endl;

    std::ifstream tmp_read(l_DB_file_path);
    if(!tmp_read.is_open()) { std::cout << "Can't open file" << std::endl; return false; }
    if(!goToLine(l_line_number, tmp_read)) { std::cout << "Wrong Line Number" << std::endl; return false; }

    int insert_position = tmp_read.tellg();

    std::string data;
    std::getline(tmp_read, data);
    data = "";

    tmp_read.seekg(0);
    //std::cout << tmp_read.tellg() << std::endl;
    while(tmp_read.tellg() != insert_position)
    {
        std::string line;
        std::getline(tmp_read, line);
        data += (line + "\n");
    }


    std::string line;
    std::getline(tmp_read, line);
    data = data + line + l_new_line + l_end + std::string("\n");


    while(!tmp_read.eof())
    {
        std::getline(tmp_read, line);
        data += (line + "\n");
    }

    tmp_read.close();

    std::ofstream tmp_write(l_DB_file_path);
    tmp_write << data;
    tmp_write.close();

    std::cout << "Success" << std::endl;
    std::cout << "addToLine() END_FUNC" << std::endl;
    return true;
}*/

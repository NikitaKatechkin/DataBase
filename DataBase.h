#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "tools.h"
#include <iostream>
#include <vector>

//struct Field{};

class DataBase
{
public:
    DataBase();
    ~DataBase();
private:
    std::string m_name;

    std::vector<tools::Field> m_fields;
};

#endif // DATABASE_H_INCLUDED

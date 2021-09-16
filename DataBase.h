#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include "tools.h"


//struct Field{};
enum ServiceRows
{
    SERVICE_ROWS_NAMES = 0,
    SERVICE_ROWS_KEY_MARKS,
    SERVICE_ROWS_TYPES
};

class DataBase
{
public:
    void addField();

    void create();

    DataBase();
    ~DataBase();
private:
    std::string m_name;

    bool newFieldAddCheck(std::string l_add_condidate);
    //std::vector<tools::Field> m_fields;
};

#endif // DATABASE_H_INCLUDED

#include "DataBase.h"
//#include "tools.h"

void DataBase::addField()
{
    tools::Field field;

    bool is_unic_field_name = false;
    while (!is_unic_field_name)
    {
        tools::input("Input field name", &field.m_name);
        is_unic_field_name = newFieldAddCheck(field.m_name);
    }

    tools::input("Input is field key (1 - key field, 0 - generic field)", &field.m_key_field);

    int type;
    tools::input("Input field type (0 - int, 1 - float, 2 - string, 3 - boolean)", &type);
    field.m_type = tools::FieldType(type);

    tools::addField(field, m_name);
    /*tools::changeLine(0, m_name, "hello");*/
}

void DataBase::create()
{
    bool is_created = false;
    while(!is_created)
    {
        tools::input("Input DB name", &m_name);
        m_name += std::string(".txt");
        is_created = tools::createDBfile(m_name);
    }

    bool is_continue_add_fields = true;
    while (is_continue_add_fields)
    {
        addField();
        tools::input("To continue add press 1, otherwise - press any other key", &is_continue_add_fields);
    }
}

bool DataBase::newFieldAddCheck(std::string l_add_condidate)
{
    std::ifstream tmp_names(m_name);
    tools::goToLine(ServiceRows::SERVICE_ROWS_NAMES, tmp_names);
    std::string names;
    std::getline(tmp_names, names);

    return (names.find(l_add_condidate) == std::string::npos);
}

DataBase::DataBase()
{

}

DataBase::~DataBase()
{

}



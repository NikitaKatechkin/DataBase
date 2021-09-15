#include "DataBase.h"
//#include "tools.h"

DataBase::DataBase()
{
    bool is_created = false;
    while(!is_created)
    {
        tools::input("Input DB name", &m_name);
        is_created = tools::createDBfile(m_name + std::string(".txt"));
    }
}

DataBase::~DataBase()
{

}

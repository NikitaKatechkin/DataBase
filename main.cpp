#include "DataBase.h"

int main()
{
    //tools::createDBfile("file.txt");
    //tools::changeLine(0, "file.txt", "it's nice");
    //insertLine(0, "file.txt", "inserted string");
    //addToLine(0, "file.txt", "additional string");
    /*tools::addField({"name", true, tools::FieldType::FIELD_TYPE_STRING}, "file.txt");
    tools::addField({"age", false, tools::FieldType::FIELD_TYPE_INT}, "file.txt");
    tools::addField({"sex", false, tools::FieldType::FIELD_TYPE_BOOLEAN}, "file.txt");*/

    /*bool answer;
    tools::input("Input num", &answer);
    std::cout << answer << std::endl;*/

    DataBaseCreator DB;
    DB.create();
    //DB.addField();

    //tools::addField("file.txt");
    //std::cout << tools::newFieldAddCheck("name", "file.txt") << std::endl;

    return 0;
}

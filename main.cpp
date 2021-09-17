#include "DataBase.h"
#include "TestSuits.h"

int main()
{
    /*tools::createDBfile("file.txt");
    tools::changeLine(19, "file.txt", "it's nice");
    tools::insertLine(0, "file.txt", "inserted string");
    std::ifstream file_read("file.txt");
    std::string line = "@";
    while(line != "\0")
    {
        std::getline(file_read, line);
        if (line != "\0") { std::cout << line << std::endl; }
    }*/

    /*std::vector<int> result = tools::searchForStr("file.txt", "inserted string");
    for (auto it = result.begin(); it != result.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;*/

    //tools::createDBfile("file.txt");
    //tools::changeLine(0, "file.txt", "it's nice");
    //insertLine(0, "file.txt", "inserted string");
    //addToLine(0, "file.txt", "additional string");
    //tools::addField({"name", true, tools::FieldType::FIELD_TYPE_STRING}, "file.txt");
    //tools::addField({"age", false, tools::FieldType::FIELD_TYPE_INT}, "file.txt");
    //tools::addField({"sex", false, tools::FieldType::FIELD_TYPE_BOOLEAN}, "file.txt");

    //tools::removeLine(-2, "file.txt");

    /*bool answer;
    tools::input("Input num", &answer);
    std::cout << answer << std::endl;*/

    /*DataBase DB;
    DB.create();*/
    //DB.addField();

    //tools::addField("file.txt");
    //std::cout << tools::newFieldAddCheck("name", "file.txt") << std::endl;

    tests::test_createFile();
    tests::test_deleteFile();

    return 0;
}

#include "FileHandler.h"

bool FileHandler::createFile(const std::string& file_name)
{
    std::cout << "createFile() START_FUNC >>" << std::endl;

    bool FILE_SUCCESSFUL_CREATION_FLAG = false;
    std::ifstream file_read(file_name);
    if(file_read.is_open())
    {
        std::cout << "File "<< file_name << " already exist" << std::endl;
        file_read.close();
    }
    else
    {
        std::ofstream file_create(file_name);
        if(file_create.is_open())
        {
            std::cout << "File " << file_name << " was created" << std::endl;
            file_create << END_OF_TEXT_ASCII_SYMBOL;
            file_create.close();
            FILE_SUCCESSFUL_CREATION_FLAG = true;
        }
        else
        {
            std:: cout << "Can't create file with " << file_name << " name" << std::endl;
        }
    }

    std::cout << "<< createFile() END_FUNC" << std::endl;
    return FILE_SUCCESSFUL_CREATION_FLAG;
}

bool FileHandler::deleteFile(const std::string& file_name)
{
    std::cout << "deleteFile() START_FUNC >>" << std::endl;

    bool FILE_SUCCESSFUL_DELETION_FLAG = std::ifstream(file_name).is_open();
    if (!FILE_SUCCESSFUL_DELETION_FLAG) { std::cout << "There is no file " << file_name << std::endl; }

    std::remove(file_name.c_str());
    FILE_SUCCESSFUL_DELETION_FLAG = (FILE_SUCCESSFUL_DELETION_FLAG && !std::ifstream(file_name).is_open());

    if (!FILE_SUCCESSFUL_DELETION_FLAG) { std::cout << "Error when deleting file " << file_name << std::endl; }
    else { std::cout << "File " << file_name << " was deleted" << std::endl; }

    std::cout << "<< deleteFile() END_FUNC" << std::endl;
    return FILE_SUCCESSFUL_DELETION_FLAG;
}



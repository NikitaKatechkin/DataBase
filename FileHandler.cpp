#include "FileHandler.h"

bool FileHandler::createFile(const std::string& file_name)
{
    std::cout << "createFile() START_FUNC >>" << std::endl;

    bool FILE_SUCCESSFUL_CREATION_FLAG = std::ifstream (file_name).is_open();
    //std::ifstream file_read(file_name);
    if(FILE_SUCCESSFUL_CREATION_FLAG)
    {
        std::cout << "File "<< file_name << " already exist" << std::endl;
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

bool FileHandler::openReadFile(const std::string& file_name, std::ifstream& file_read_stream)
{
    std::cout << "openReadFile() START_FUNC >>" << std::endl;

    bool FILE_SUCCESSFUL_OPENING_FLAG = file_read_stream.is_open();
    if (!FILE_SUCCESSFUL_OPENING_FLAG) { file_read_stream.open(file_name); }


    FILE_SUCCESSFUL_OPENING_FLAG = file_read_stream.is_open();
    if(!FILE_SUCCESSFUL_OPENING_FLAG) { std::cout << "Error opening file " << file_name << " for reading" << std::endl; }
    else { std::cout << "File " << file_name << " was opened for reading" << std::endl; }

    std::cout << "<< openReadFile() END_FUNC" << std::endl;
    return FILE_SUCCESSFUL_OPENING_FLAG;
}

bool FileHandler::openRewriteFile(const std::string& file_name, std::ofstream& file_write_stream)
{
    std::cout << "openRewriteFile() START_FUNC >>" << std::endl;

    std::ifstream test;
    bool FILE_SUCCESSFUL_OPENING_FLAG = FileHandler::openReadFile(file_name, test);
    test.close();

    if(FILE_SUCCESSFUL_OPENING_FLAG)
    {
        file_write_stream.open(file_name);
        FILE_SUCCESSFUL_OPENING_FLAG = file_write_stream.is_open();
    }

    if(!FILE_SUCCESSFUL_OPENING_FLAG) { std::cout << "Error opening file " << file_name << " for rewriting" << std::endl; }
    else { std::cout << "File " << file_name << " was opened for rewriting" << std::endl; }

    std::cout << "<< openRewriteFile() END_FUNC" << std::endl;
    return FILE_SUCCESSFUL_OPENING_FLAG;
}

bool FileHandler::openWriteFile(const std::string& file_name, std::ofstream& file_write_stream)
{
    std::cout << "openWriteFile() START_FUNC >>" << std::endl;

    std::ifstream test;
    bool FILE_SUCCESSFUL_OPENING_FLAG = FileHandler::openReadFile(file_name, test);
    test.close();

    if(FILE_SUCCESSFUL_OPENING_FLAG)
    {
        file_write_stream.open(file_name, std::ofstream::out | std::ofstream::app);
        FILE_SUCCESSFUL_OPENING_FLAG = file_write_stream.is_open();
    }

    if(!FILE_SUCCESSFUL_OPENING_FLAG) { std::cout << "Error opening file " << file_name << " for appending" << std::endl; }
    else { std::cout << "File " << file_name << " was opened for appending" << std::endl; }

    std::cout << "<< openWriteFile() END_FUNC" << std::endl;
    return FILE_SUCCESSFUL_OPENING_FLAG;
}

bool FileHandler::closeFile(std::ifstream& file_read_stream)
{
    std::cout << "closeFile() START_FUNC >>" << std::endl;

    bool FILE_SUCCESSFUL_CLOSING_FLAG = file_read_stream.is_open();
    if (FILE_SUCCESSFUL_CLOSING_FLAG) { std::cout << "File " << " was closed" << std::endl; file_read_stream.close(); }
    else { std::cout << "File " << " was not closed, because it was not open" << std::endl; }

    std::cout << "<< closeFile() END_FUNC" << std::endl;
    return FILE_SUCCESSFUL_CLOSING_FLAG;
}

bool FileHandler::closeFile(std::ofstream& file_write_stream)
{
    std::cout << "closeFile() START_FUNC >>" << std::endl;

    bool FILE_SUCCESSFUL_CLOSING_FLAG = file_write_stream.is_open();
    if (FILE_SUCCESSFUL_CLOSING_FLAG) { std::cout << "File " << " was closed" << std::endl; file_write_stream.close(); }
    else { std::cout << "File " << " was not closed, because it was not open" << std::endl; }

    std::cout << "<< closeFile() END_FUNC" << std::endl;
    return FILE_SUCCESSFUL_CLOSING_FLAG;
}

void FileHandler::saveFile(std::ifstream& file_read_stream)
{
    return;
}

bool FileHandler::saveFile(const std::string& file_name, std::ofstream& file_write_stream)
{
    std::cout << "saveFile() START_FUNC >>" << std::endl;

    bool FILE_SUCCESSFUL_CLOSING_FLAG = file_write_stream.is_open();
    if (FILE_SUCCESSFUL_CLOSING_FLAG)
    {
        FILE_SUCCESSFUL_CLOSING_FLAG = FileHandler::closeFile(file_write_stream);
        if(FILE_SUCCESSFUL_CLOSING_FLAG)
        {
            FILE_SUCCESSFUL_CLOSING_FLAG = FileHandler::openWriteFile(file_name, file_write_stream);
        }
    }

    std::cout << "<< saveFile() END_FUNC" << std::endl;
    return FILE_SUCCESSFUL_CLOSING_FLAG;
}


#include "FileHandler.h"

bool FileHandler::createFile(const std::string& file_name)
{
    if (debug_flag) { std::cout << "createFile() START_FUNC >>" << std::endl; }

    bool FILE_SUCCESSFUL_CREATION_FLAG = std::ifstream (file_name).is_open();
    if(FILE_SUCCESSFUL_CREATION_FLAG)
    {
        if (debug_flag) { std::cout << "File '"<< file_name << "' already exist" << std::endl; }
        FILE_SUCCESSFUL_CREATION_FLAG = false;
    }
    else
    {
        std::ofstream file_create(file_name);
        if(file_create.is_open())
        {
            if (debug_flag) { std::cout << "File '" << file_name << "' was created" << std::endl; }
            file_create << END_OF_TEXT_ASCII_SYMBOL;
            file_create.close();
            FILE_SUCCESSFUL_CREATION_FLAG = true;
        }
        else
        {
            if (debug_flag) { std:: cout << "Can't create file '" << file_name << "'" << std::endl; }
        }
    }

    if (debug_flag) { std::cout << "<< createFile() END_FUNC" << std::endl; }
    return FILE_SUCCESSFUL_CREATION_FLAG;
}

bool FileHandler::deleteFile(const std::string& file_name)
{
    if (debug_flag) { std::cout << "deleteFile() START_FUNC >>" << std::endl; }

    bool FILE_SUCCESSFUL_DELETION_FLAG = true;
    bool IS_EXIST = std::ifstream(file_name).is_open();
    if (!IS_EXIST) { if (debug_flag) { std::cout << "There is no file '" << file_name << "'" << std::endl; } }
    std::remove(file_name.c_str());
    if(std::ifstream(file_name).is_open() && IS_EXIST)
    {
        if (debug_flag) { std::cout << "Failed to delete file '" << file_name << "'" << std::endl; }
        FILE_SUCCESSFUL_DELETION_FLAG = false;
    }

    if (FILE_SUCCESSFUL_DELETION_FLAG)
    {
        if ((!IS_EXIST && !std::ifstream(file_name).is_open())) { if (debug_flag) { std::cout << "Error when deleting file '" << file_name << "'" << std::endl; } FILE_SUCCESSFUL_DELETION_FLAG = true; }
        else { if (debug_flag) { std::cout << "File '" << file_name << "' was deleted" << std::endl; } }
    }

    if (debug_flag) { std::cout << "<< deleteFile() END_FUNC" << std::endl; }
    return FILE_SUCCESSFUL_DELETION_FLAG;
}

bool FileHandler::openReadFile(const std::string& file_name, std::ifstream& file_read_stream)
{
    if (debug_flag) { std::cout << "openReadFile() START_FUNC >>" << std::endl; }

    bool FILE_SUCCESSFUL_OPENING_FLAG = file_read_stream.is_open();
    if (!FILE_SUCCESSFUL_OPENING_FLAG) { file_read_stream.open(file_name); }


    FILE_SUCCESSFUL_OPENING_FLAG = file_read_stream.is_open();
    if(!FILE_SUCCESSFUL_OPENING_FLAG) { if (debug_flag) { std::cout << "Error opening file '" << file_name << "' for reading" << std::endl; } }
    else { if (debug_flag) { std::cout << "File '" << file_name << "' was opened for reading" << std::endl; } }

    if (debug_flag) { std::cout << "<< openReadFile() END_FUNC" << std::endl; }
    return FILE_SUCCESSFUL_OPENING_FLAG;
}

bool FileHandler::openRewriteFile(const std::string& file_name, std::ofstream& file_write_stream)
{
    if (debug_flag) { std::cout << "openRewriteFile() START_FUNC >>" << std::endl; }

    bool FILE_SUCCESSFUL_OPENING_FLAG;
    if (file_write_stream.is_open())
    {
        FILE_SUCCESSFUL_OPENING_FLAG = true;
        if (debug_flag) { std::cout << "File '" << file_name << "' was already opened for rewriting" << std::endl; }
    }
    else
    {
        std::ifstream test;
        FILE_SUCCESSFUL_OPENING_FLAG = FileHandler::openReadFile(file_name, test);
        test.close();

        if(FILE_SUCCESSFUL_OPENING_FLAG)
        {
            file_write_stream.open(file_name);
            FILE_SUCCESSFUL_OPENING_FLAG = file_write_stream.is_open();
        }
    }

    if(!FILE_SUCCESSFUL_OPENING_FLAG) { if (debug_flag) { std::cout << "Error opening file '" << file_name << "' for rewriting" << std::endl; } }
    else { if (debug_flag) { std::cout << "File '" << file_name << "' was opened for rewriting" << std::endl; } }

    if (debug_flag) { std::cout << "<< openRewriteFile() END_FUNC" << std::endl; }
    return FILE_SUCCESSFUL_OPENING_FLAG;
}

bool FileHandler::openWriteFile(const std::string& file_name, std::ofstream& file_write_stream)
{
    if (debug_flag) { std::cout << "openWriteFile() START_FUNC >>" << std::endl; }

    bool FILE_SUCCESSFUL_OPENING_FLAG;
    if (file_write_stream.is_open())
    {
        FILE_SUCCESSFUL_OPENING_FLAG = true;
        if (debug_flag) { std::cout << "File '" << file_name << "' was already opened for rewriting" << std::endl; }
    }
    else
    {
        std::ifstream test;
        FILE_SUCCESSFUL_OPENING_FLAG = FileHandler::openReadFile(file_name, test);
        test.close();

        if(FILE_SUCCESSFUL_OPENING_FLAG)
        {
            file_write_stream.open(file_name, std::ofstream::out | std::ofstream::app);
            FILE_SUCCESSFUL_OPENING_FLAG = file_write_stream.is_open();
        }
    }

    if(!FILE_SUCCESSFUL_OPENING_FLAG) { if (debug_flag) { std::cout << "Error opening file " << file_name << " for appending" << std::endl; } }
    else { if (debug_flag) { std::cout << "File " << file_name << " was opened for appending" << std::endl; } }

    if (debug_flag) { std::cout << "<< openWriteFile() END_FUNC" << std::endl; }
    return FILE_SUCCESSFUL_OPENING_FLAG;
}

bool FileHandler::closeFile(std::ifstream& file_read_stream)
{
    if (debug_flag) { std::cout << "closeFile() START_FUNC >>" << std::endl; }

    bool FILE_SUCCESSFUL_CLOSING_FLAG = file_read_stream.is_open();
    if (FILE_SUCCESSFUL_CLOSING_FLAG)
    {
        if (debug_flag) { std::cout << "File " << " was closed" << std::endl; }
        file_read_stream.close();
        FILE_SUCCESSFUL_CLOSING_FLAG = !file_read_stream.is_open();
        if (!FILE_SUCCESSFUL_CLOSING_FLAG)
        {
            if (debug_flag) { std::cout << "Error when closing files" << std::endl; }
        }
    }
    else { if (debug_flag) { std::cout << "File " << " was not closed, because it was not open" << std::endl; } }

    if (debug_flag) { std::cout << "<< closeFile() END_FUNC" << std::endl; }
    return FILE_SUCCESSFUL_CLOSING_FLAG;
}

bool FileHandler::closeFile(std::ofstream& file_write_stream)
{
    if (debug_flag) { std::cout << "closeFile() START_FUNC >>" << std::endl; }

    bool FILE_SUCCESSFUL_CLOSING_FLAG = file_write_stream.is_open();
    if (FILE_SUCCESSFUL_CLOSING_FLAG)
    {
        if (debug_flag) { std::cout << "File " << " was closed" << std::endl; }
        file_write_stream.close();
        FILE_SUCCESSFUL_CLOSING_FLAG = !file_write_stream.is_open();
        if (!FILE_SUCCESSFUL_CLOSING_FLAG)
        {
            if (debug_flag) { std::cout << "Error when closing files" << std::endl; }
        }
    }
    else { if (debug_flag) { std::cout << "File " << " was not closed, because it was not open" << std::endl; } }

    if (debug_flag) { std::cout << "<< closeFile() END_FUNC" << std::endl; }
    return FILE_SUCCESSFUL_CLOSING_FLAG;
}

bool FileHandler::saveFile(std::ifstream& file_read_stream)
{
    return true;
}

bool FileHandler::saveFile(const std::string& file_name, std::ofstream& file_write_stream)
{
    if (debug_flag) { std::cout << "saveFile() START_FUNC >>" << std::endl; }

    bool FILE_SUCCESSFUL_CLOSING_FLAG = file_write_stream.is_open();
    if (FILE_SUCCESSFUL_CLOSING_FLAG)
    {
        FILE_SUCCESSFUL_CLOSING_FLAG = FileHandler::closeFile(file_write_stream);
        if(FILE_SUCCESSFUL_CLOSING_FLAG)
        {
            FILE_SUCCESSFUL_CLOSING_FLAG = FileHandler::openWriteFile(file_name, file_write_stream);
            if (FILE_SUCCESSFUL_CLOSING_FLAG) { if (debug_flag) { std::cout << "File " << file_name << " was saved" <<  std::endl; } }
            else { if (debug_flag) { std::cout << "File " << file_name << " was failed to reopen" << std::endl; } }
        }
        else { if (debug_flag) { std::cout << "Error, when closing file for saving" << std::endl; } }
    }
    else { if (debug_flag) { std::cout << "File " << file_name << " was not open. Can not save." << std::endl; } }

    if (debug_flag) { std::cout << "<< saveFile() END_FUNC" << std::endl; }
    return FILE_SUCCESSFUL_CLOSING_FLAG;
}


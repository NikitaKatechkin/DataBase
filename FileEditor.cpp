#include "FileEditor.h"

bool FileEditor::goToLine(unsigned int l_line_number, std::ifstream& l_file)
{
    std::cout << "goToLine() START_FUNC >>" << std::endl;

    bool success_flag = l_file.is_open();

    if (success_flag)
    {
        l_file.seekg(0);
        std::string tmp_line;
        for (unsigned int i = 0; i < l_line_number; i++)
        {
            if (l_file.eof())
            {
                success_flag = false;
                break;
            }
            std::getline(l_file, tmp_line);
        }
        success_flag = success_flag && (l_file.tellg() != -1);
    }


    if (success_flag) { std::cout << "Placed cursor to " << l_line_number << " line" << std::endl; }
    else { std::cout << "EOF REACHED" << std::endl; l_file.seekg(0); }

    std::cout << "<< goToLine() END_FUNC" << std::endl;
    return success_flag;
}

bool FileEditor::copyLine(unsigned int l_line_number, std::ifstream& l_file, std::string& l_line)
{
    std::cout << "copyLine() START_FUNC >>" << std::endl;
    bool SUCCESS_COPY_FLAG = goToLine(l_line_number, l_file);

    if (SUCCESS_COPY_FLAG) { std::getline(l_file, l_line); }

    std::cout << "<< copyLine() END_FUNC" << std::endl;
    return SUCCESS_COPY_FLAG;
}

bool FileEditor::copyLineV2(unsigned int l_line_number, std::string l_file_path, std::string& l_line)
{
    std::cout << "copyLineV2() START_FUNC >>" << std::endl;

    std::ifstream tmp_file_read;
    bool SUCCESS_CHANGELINE_FLAG = FileHandler::openReadFile(l_file_path, tmp_file_read);
    if (SUCCESS_CHANGELINE_FLAG) { SUCCESS_CHANGELINE_FLAG = goToLine(l_line_number, tmp_file_read); }
    else { std::cout << "Error opening file " << l_file_path << std::endl; }

    if (SUCCESS_CHANGELINE_FLAG)
    {
        std::getline(tmp_file_read, l_line);
        FileHandler::closeFile(tmp_file_read);
    }
    else { std::cout << "Error going to line # " << l_line_number << std::endl; }

    std::cout << "<< copyLineV2() END_FUNC" << std::endl;
    return SUCCESS_CHANGELINE_FLAG;
}

bool FileEditor::changeLine(int l_line_number, std::string l_file_path, std::string l_new_line, std::string l_end)
{
    std::cout << "changeLine() START_FUNC >>" << std::endl;

    std::ifstream tmp_file_read;
    bool SUCCESS_CHANGELINE_FLAG = FileHandler::openReadFile(l_file_path, tmp_file_read);
    if (SUCCESS_CHANGELINE_FLAG) { SUCCESS_CHANGELINE_FLAG = goToLine(l_line_number, tmp_file_read); }
    else { std::cout << "Error opening file " << l_file_path << std::endl; }

    if (SUCCESS_CHANGELINE_FLAG)
    {
        int insert_position = tmp_file_read.tellg();

        std::string data;
        std::getline(tmp_file_read, data);
        data = "";

        FileHandler::closeFile(tmp_file_read);
        FileHandler::openReadFile(l_file_path, tmp_file_read);

        while(tmp_file_read.tellg() != insert_position)
        {
            std::string line;
            std::getline(tmp_file_read, line);
            data += (line + "\n");
        }

        data = data + l_new_line + l_end /*+ std::string("\n")*/;

        //if(LAST_LINE_CASE_FLAG) { data.pop_back();}

        std::string line;
        std::getline(tmp_file_read, line);

        //if (!tmp_file_read.eof()) { data += "\n"; }

        //int counter = 0;
        while(!tmp_file_read.eof())
        {
            /*if (counter == 0)
            {
                std::getline(tmp_file_read, line);
                data += line;
                counter++;
                continue;
            }*/
            data += "\n";
            std::getline(tmp_file_read, line);
            data += line;
            //if (!tmp_file_read.eof()) { data += "\n"; }
        }
        data += "\0";

        std::ofstream tmp_write(l_file_path);
        tmp_write << data;
        FileHandler::closeFile(tmp_file_read);
        FileHandler::closeFile(tmp_write);

        std::cout << "Success" << std::endl;
    }
    else { std::cout << "Error going to line # " << l_line_number << std::endl; }

    std::cout << "<< changeLine() END_FUNC" << std::endl;
    return SUCCESS_CHANGELINE_FLAG;
}

bool FileEditor::changeLineRemoveCompetable(int l_line_number, std::string l_file_path, std::string l_new_line, std::string l_end)
{
    std::cout << "changeLine() START_FUNC >>" << std::endl;

    std::ifstream tmp_file_read;
    bool SUCCESS_CHANGELINE_FLAG = FileHandler::openReadFile(l_file_path, tmp_file_read);
    if (SUCCESS_CHANGELINE_FLAG) { SUCCESS_CHANGELINE_FLAG = goToLine(l_line_number, tmp_file_read); }
    else { std::cout << "Error opening file " << l_file_path << std::endl; }

    if (SUCCESS_CHANGELINE_FLAG)
    {
        int insert_position = tmp_file_read.tellg();

        std::string data;
        std::getline(tmp_file_read, data);
        data = "";

        bool LAST_FLAG = false;
        if (FileEditor::goToLine(l_line_number - 1, tmp_file_read))
        {
            if (!(FileEditor::goToLine(l_line_number + 1, tmp_file_read)))
            {
                LAST_FLAG = true;
            }
            else { FileHandler::closeFile(tmp_file_read); }
        }
        else { FileHandler::closeFile(tmp_file_read); }
        std::cout << LAST_FLAG << std::endl;

        FileHandler::closeFile(tmp_file_read);
        FileHandler::openReadFile(l_file_path, tmp_file_read);

        while(tmp_file_read.tellg() != insert_position)
        {
            std::string line;
            std::getline(tmp_file_read, line);
            data += (line + "\n");
        }

        data = data + l_new_line + l_end /*+ std::string("\n")*/;


        //if(LAST_LINE_CASE_FLAG) { data.pop_back();}

        std::string line;
        std::getline(tmp_file_read, line);

        //if (!tmp_file_read.eof()) { data += "\n"; }

        int counter = 0;
        while(!tmp_file_read.eof())
        {
            if (counter == 0)
            {
                std::getline(tmp_file_read, line);
                data += line;
                counter++;
                continue;
            }
            data += "\n";
            std::getline(tmp_file_read, line);
            data += line;
            //if (!tmp_file_read.eof()) { data += "\n"; }
        }
        if (LAST_FLAG) { data.pop_back(); std::cout << "AAAAAAAAAAAAAAAAA" << std::endl; }
        data += "\0";

        std::ofstream tmp_write(l_file_path);
        tmp_write << data;
        FileHandler::closeFile(tmp_file_read);
        FileHandler::closeFile(tmp_write);

        std::cout << "Success" << std::endl;
    }
    else { std::cout << "Error going to line # " << l_line_number << std::endl; }

    std::cout << "<< changeLine() END_FUNC" << std::endl;
    return SUCCESS_CHANGELINE_FLAG;
}

bool FileEditor::insertLine(int l_line_number, std::string l_file_path, std::string l_new_line, std::string l_end)
{
    std::cout << "insertLine() START_FUNC >>" << std::endl;

    std::ifstream tmp_file_read;
    bool SUCCESS_CHANGELINE_FLAG = FileHandler::openReadFile(l_file_path, tmp_file_read);
    if (SUCCESS_CHANGELINE_FLAG) { SUCCESS_CHANGELINE_FLAG = goToLine(l_line_number, tmp_file_read); }
    else { std::cout << "Error opening file " << l_file_path << std::endl; }

    if (SUCCESS_CHANGELINE_FLAG)
    {
        int insert_position = tmp_file_read.tellg();
        std::cout << insert_position << std::endl;

        std::string data;
        std::getline(tmp_file_read, data);
        bool empty_file = (data == "\0");
        data = "";

        FileHandler::closeFile(tmp_file_read);
        FileHandler::openReadFile(l_file_path, tmp_file_read);

        std::string line;
        while(tmp_file_read.tellg() != insert_position)
        {
            std::getline(tmp_file_read, line);
            data += (line + "\n");
        }

        data = data + l_new_line + l_end /*+ std::string("\n")*/;

        while(!tmp_file_read.eof())
        {
            if (!empty_file) { data += "\n"; }
            std::getline(tmp_file_read, line);
            data += line;
            //if (!tmp_file_read.eof()) { data += "\n"; }
        }
        data += "\0";

        std::ofstream tmp_write(l_file_path);
        tmp_write << data;
        FileHandler::closeFile(tmp_file_read);
        FileHandler::closeFile(tmp_write);

        std::cout << "Success" << std::endl;
    }
    else { std::cout << "Error going to line # " << l_line_number << std::endl; }

    std::cout << "<< insertLine() END_FUNC" << std::endl;
    return SUCCESS_CHANGELINE_FLAG;
}

bool FileEditor::removeLine(int l_line_number, std::string l_file_path)
{
    /*std::cout << "removeLine() START_FUNC >>" << std::endl;

    std::ifstream tmp_file_read;
    bool SUCCESS_CHANGELINE_FLAG = FileHandler::openReadFile(l_file_path, tmp_file_read);
    if (SUCCESS_CHANGELINE_FLAG) { SUCCESS_CHANGELINE_FLAG = goToLine(l_line_number, tmp_file_read); }
    else { std::cout << "Error opening file " << l_file_path << std::endl; }

    if (SUCCESS_CHANGELINE_FLAG)
    {
        int insert_position = tmp_file_read.tellg();

        std::string data;
        std::getline(tmp_file_read, data);
        data = "";

        std::getline(tmp_file_read, data);
        data = "";
        bool LAST_LINE_CASE_FLAG = tmp_file_read.eof();

        FileHandler::closeFile(tmp_file_read);
        FileHandler::openReadFile(l_file_path, tmp_file_read);

        std::string line;
        while(tmp_file_read.tellg() != insert_position)
        {
            std::getline(tmp_file_read, line);
            data += (line + "\n");
        }

        std::getline(tmp_file_read, line);

        if (!tmp_file_read.eof()) { std::getline(tmp_file_read, line); data += line; }
        while(!tmp_file_read.eof())
        {
            if(LAST_LINE_CASE_FLAG) { break; }
            data += "\n";
            std::getline(tmp_file_read, line);
            data += line;
            //if (!tmp_file_read.eof()) { data += "\n"; }
        }
        data += "\0";

        std::ofstream tmp_write(l_file_path);
        tmp_write << data;
        FileHandler::closeFile(tmp_file_read);
        FileHandler::closeFile(tmp_write);

        std::cout << "Success" << std::endl;
    }
    else { std::cout << "Error going to line # " << l_line_number << std::endl; }

    std::cout << "<< removeLine() END_FUNC" << std::endl;
    return SUCCESS_CHANGELINE_FLAG;*/
    std::cout << "removeLine() START_FUNC >>" << std::endl;

    std::ifstream tmp_file_read;
    bool SUCCESS_CHANGELINE_FLAG = FileHandler::openReadFile(l_file_path, tmp_file_read);
    if (SUCCESS_CHANGELINE_FLAG) { SUCCESS_CHANGELINE_FLAG = goToLine(l_line_number, tmp_file_read); }
    else { std::cout << "Error opening file " << l_file_path << std::endl; }

    if (SUCCESS_CHANGELINE_FLAG)
    {
        SUCCESS_CHANGELINE_FLAG = FileEditor::changeLineRemoveCompetable(l_line_number, l_file_path, "", "");

        if (SUCCESS_CHANGELINE_FLAG) { std::cout << "Success" << std::endl; }
    }
    else { std::cout << "Error going to line # " << l_line_number << std::endl; }

    std::cout << "<< removeLine() END_FUNC" << std::endl;
    return SUCCESS_CHANGELINE_FLAG;
}

bool FileEditor::addToLine(int l_line_number, std::string l_file_path, std::string l_new_line,
                           std::string l_end, int l_addition_index)
{
    std::cout << "insertLine() START_FUNC >>" << std::endl;

    std::ifstream tmp_file_read;
    bool SUCCESS_CHANGELINE_FLAG = FileHandler::openReadFile(l_file_path, tmp_file_read);
    if (SUCCESS_CHANGELINE_FLAG) { SUCCESS_CHANGELINE_FLAG = goToLine(l_line_number, tmp_file_read); }
    else { std::cout << "Error opening file " << l_file_path << std::endl; }

    if (SUCCESS_CHANGELINE_FLAG)
    {
        int insert_position = tmp_file_read.tellg();
        std::cout << insert_position << std::endl;

        std::string data;
        std::getline(tmp_file_read, data);
        bool empty_file = (data == "\0");
        data = "";

        FileHandler::closeFile(tmp_file_read);
        FileHandler::openReadFile(l_file_path, tmp_file_read);

        std::string line;
        while(tmp_file_read.tellg() != insert_position)
        {
            std::getline(tmp_file_read, line);
            data += (line + "\n");
        }

        std::getline(tmp_file_read, line);

        int insert_index;
        if (l_addition_index == -1)
        {
            insert_index = line.size();
        }
        else
        {
            if ((l_addition_index < 0) || (l_addition_index > int(line.size())))
            {
                insert_index = line.size();
            }
            else
            {
                insert_index = l_addition_index;
            }
        }
        line.insert(insert_index, (l_new_line + l_end));
        data = data + line/* + l_new_line + l_end*/ /*+ std::string("\n")*/;

        while(!tmp_file_read.eof())
        {
            if (!empty_file) { data += "\n"; }
            std::getline(tmp_file_read, line);
            data += line;
            //if (!tmp_file_read.eof()) { data += "\n"; }
        }
        data += "\0";

        std::ofstream tmp_write(l_file_path);
        tmp_write << data;
        FileHandler::closeFile(tmp_file_read);
        FileHandler::closeFile(tmp_write);

        std::cout << "Success" << std::endl;
    }
    else { std::cout << "Error going to line # " << l_line_number << std::endl; }

    std::cout << "<< insertLine() END_FUNC" << std::endl;
    return SUCCESS_CHANGELINE_FLAG;
}

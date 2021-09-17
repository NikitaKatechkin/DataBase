#include "TestSuits.h"

void tests::test_createFile()
{
    FileHandler::createFile("test_file.txt");

    FileHandler::createFile("test_file.txt");

    FileHandler::createFile("");
}

void tests::test_deleteFile()
{
    FileHandler::deleteFile("test_file.txt");

    FileHandler::deleteFile("test_file.txt");

    FileHandler::deleteFile("");
}

void tests::test_openReadFile()
{
    std::ifstream file_stream;
    FileHandler::openReadFile("test_file.txt", file_stream);
    file_stream.close();

    FileHandler::openReadFile("test_file.txt", file_stream);
    file_stream.close();

    FileHandler::openReadFile("", file_stream);
    file_stream.close();
}

void tests::test_openRewriteFile()
{
    std::ofstream file_stream;
    FileHandler::openRewriteFile("test_file.txt", file_stream);
    file_stream.close();

    FileHandler::openRewriteFile("tesle.txt", file_stream);
    file_stream.close();

    FileHandler::openRewriteFile("", file_stream);
    file_stream.close();
}

void tests::test_openWriteFile()
{
    std::ofstream file_stream;
    FileHandler::openWriteFile("test_file.txt", file_stream);
    file_stream << "\nhui";
    file_stream.close();

    FileHandler::openWriteFile("tesle.txt", file_stream);
    file_stream.close();

    FileHandler::openWriteFile("", file_stream);
    file_stream.close();
}

void tests::test_closeReadFile()
{
    std::ifstream file_stream;
    FileHandler::openReadFile("test_file.txt", file_stream);
    FileHandler::closeFile(file_stream);

    FileHandler::openReadFile("test_file.txt", file_stream);
    FileHandler::closeFile(file_stream);

    FileHandler::openReadFile("test.txt", file_stream);
    FileHandler::closeFile(file_stream);
}

void tests::test_closeWriteFile()
{
    std::ofstream file_stream;
    FileHandler::openRewriteFile("test_file.txt", file_stream);
    FileHandler::closeFile(file_stream);

    FileHandler::openRewriteFile("test_file.txt", file_stream);
    file_stream << "\nshit";
    FileHandler::closeFile(file_stream);

    FileHandler::openWriteFile("test.txt", file_stream);
    FileHandler::closeFile(file_stream);

    FileHandler::openRewriteFile("test.txt", file_stream);
    FileHandler::closeFile(file_stream);
}

void tests::test_saveWriteFile()
{
    std::ofstream file_stream;
    FileHandler::openWriteFile("test_file.txt", file_stream);
    FileHandler::saveFile("test_file.txt", file_stream);
    file_stream << "\nshit";
    FileHandler::closeFile(file_stream);
}

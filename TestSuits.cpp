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

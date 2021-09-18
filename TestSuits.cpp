#include "TestSuits.h"

void tests::test_createFile()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileHandler::createFile() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result;
    std::cout << "TEST_1_START >> Creation without obstacles" << std::endl;
    test_result = FileHandler::createFile("test_file.txt");
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Creation without obstacles << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_2_START >> Creation with obstacle (FILE ALREADY EXIST RESULT EXPECTED)" << std::endl;
    test_result = FileHandler::createFile("test_file.txt");
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Creation with obstacle (FILE ALREADY EXIST RESULT EXPECTED) << TEST_2_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_3_START >> Creation with obstacle (INVALID NAME ERROR RESULT EXPECTED)" << std::endl;
    test_result =  FileHandler::createFile("");
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Creation with obstacle (INVALID NAME ERROR RESULT EXPECTED) << TEST_3_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileHandler::createFile() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void tests::test_deleteFile()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileHandler::deleteFile() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result;

    std::cout << "TEST_1_START >> Deletion without obstacles" << std::endl;
    FileHandler::createFile("test_file.txt");
    test_result = FileHandler::deleteFile("test_file.txt");
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Deletion without obstacles << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_2_START >> Deletion with obstacles (NO FILE EXISTS)" << std::endl;
    std::cout << "EXPECTED ERROR MESSAGE BUT SUCCESS STATUS RETURNED" << std::endl;
    test_result = FileHandler::deleteFile("test_file.txt");
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Deletion with obstacles (NO FILE EXISTS) << TEST_2_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_3_START >> Deletion with obstacles (INVALID FILE NAME)" << std::endl;
    std::cout << "EXPECTED ERROR MESSAGE BUT SUCCESS STATUS RETURNED" << std::endl;
    test_result = FileHandler::deleteFile("");
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Deletion with obstacles (INVALID FILE NAME) << TEST_3_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileHandler::deleteFile() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void tests::test_openReadFile()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileHandler::openReadFile() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result;

    std::cout << "TEST_1_START >> Opening for reading without obstackels" << std::endl;
    FileHandler::createFile("test_file.txt");
    std::ifstream file_stream;
    test_result = FileHandler::openReadFile("test_file.txt", file_stream);
    file_stream.close();
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Opening for reading without obstackels << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_2_START >> Opening for reading with obstacles (NO FILE EXISTS)" << std::endl;
    test_result = FileHandler::openReadFile("test_file.txt", file_stream);
    file_stream.close();
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Opening for reading with obstacles (NO FILE EXISTS) << TEST_2_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_3_START >> Opening for reading with obstacles (INVALID FILE NAME)" << std::endl;
    test_result = FileHandler::openReadFile("", file_stream);
    file_stream.close();
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Opening for reading with obstacles (INVALID FILE NAME) << TEST_3_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_4_START >> Opening for reading with obstacles (ALREADY OPENED)" << std::endl;
    FileHandler::createFile("test_file.txt");
    FileHandler::openReadFile("test_file.txt", file_stream);
    test_result = FileHandler::openReadFile("test_file.txt", file_stream);
    file_stream.close();
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Opening for reading with obstacles (ALREADY OPENED) << TEST_4_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileHandler::openReadFile() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
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

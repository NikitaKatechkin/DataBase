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

    std::cout << "TEST_1_START >> Opening for reading without obstacles" << std::endl;
    FileHandler::createFile("test_file.txt");
    std::ifstream file_stream;
    test_result = FileHandler::openReadFile("test_file.txt", file_stream);
    file_stream.close();
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Opening for reading without obstacles << TEST_1_END" << std::endl;

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
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileHandler::openRewriteFile() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result;

    std::cout << "TEST_1_START >> Opening for rewriting without obstacles" << std::endl;
    FileHandler::createFile("test_file.txt");
    std::ofstream file_stream;
    test_result = FileHandler::openRewriteFile("test_file.txt", file_stream);
    file_stream.close();
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Opening for rewriting without obstacles << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_2_START >> Opening for rewriting with obstacles (NO FILE EXISTS)" << std::endl;
    test_result = FileHandler::openRewriteFile("test_file.txt", file_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    file_stream.close();
    std::cout << "Opening for rewriting with obstacles (NO FILE EXISTS)<< TEST_2_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_3_START >> Opening for rewriting with obstacles (ALREADY OPENED)" << std::endl;
    FileHandler::createFile("test_file.txt");
    FileHandler::openRewriteFile("test_file.txt", file_stream);
    test_result = FileHandler::openRewriteFile("test_file.txt", file_stream);
    file_stream.close();
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Opening for rewriting with obstacles (ALREADY OPENED)<< TEST_3_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileHandler::openRewriteFile() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void tests::test_openWriteFile()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileHandler::openWriteFile() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result;

    std::cout << "TEST_1_START >> Opening for writing without obstacles" << std::endl;
    FileHandler::createFile("test_file.txt");
    std::ofstream file_stream;
    test_result = FileHandler::openWriteFile("test_file.txt", file_stream);
    file_stream.close();
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Opening for writing without obstacles << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_2_START >> Opening for writing with obstacles (NO FILE EXISTS)" << std::endl;
    test_result = FileHandler::openWriteFile("test_file.txt", file_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    file_stream.close();
    std::cout << "Opening for writing with obstacles (NO FILE EXISTS)<< TEST_2_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_3_START >> Opening for writing with obstacles (ALREADY OPENED)" << std::endl;
    FileHandler::createFile("test_file.txt");
    FileHandler::openRewriteFile("test_file.txt", file_stream);
    test_result = FileHandler::openWriteFile("test_file.txt", file_stream);
    file_stream.close();
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Opening for writing with obstacles (ALREADY OPENED)<< TEST_3_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileHandler::openWriteFile() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void tests::test_closeReadFile()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileHandler::closeReadFile() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result;

    std::ifstream file_stream;

    std::cout << "TEST_1_START >> Closing without obstacles" << std::endl;
    FileHandler::createFile("test_file.txt");
    FileHandler::openReadFile("test_file.txt", file_stream);
    test_result = FileHandler::closeFile(file_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Closing without obstacles << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_2_START >> Closing with obstacles (FILE WAS NOT OPENED)" << std::endl;
    FileHandler::createFile("test_file.txt");
    test_result = FileHandler::closeFile(file_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Closing with obstacles (FILE WAS NOT OPENED) << TEST_2_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_3_START >> Closing with obstacles (FILE DO NOT EXISTS)" << std::endl;
    test_result = FileHandler::closeFile(file_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Closing with obstacles (FILE DO NOT EXISTS) << TEST_3_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileHandler::closeReadFile() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void tests::test_closeWriteFile()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileHandler::closeWriteFile() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result;

    std::ofstream file_stream;

    std::cout << "TEST_1_START >> Closing without obstacles" << std::endl;
    FileHandler::createFile("test_file.txt");
    FileHandler::openWriteFile("test_file.txt", file_stream);
    test_result = FileHandler::closeFile(file_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Closing without obstacles << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_2_START >> Closing with obstacles (FILE WAS NOT OPENED)" << std::endl;
    FileHandler::createFile("test_file.txt");
    test_result = FileHandler::closeFile(file_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Closing with obstacles (FILE WAS NOT OPENED) << TEST_2_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_3_START >> Closing with obstacles (FILE DO NOT EXISTS)" << std::endl;
    test_result = FileHandler::closeFile(file_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Closing with obstacles (FILE DO NOT EXISTS) << TEST_3_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileHandler::closeWriteFile() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void tests::test_saveWriteFile()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileHandler::saveWriteFile() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result;

    std::ofstream file_stream;

    std::cout << "TEST_1_START >> Saving without obstacles" << std::endl;
    FileHandler::createFile("test_file.txt");
    FileHandler::openWriteFile("test_file.txt", file_stream);
    test_result = FileHandler::saveFile("test_file.txt", file_stream);
    FileHandler::closeFile(file_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Saving without obstacles << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_2_START >> Saving with obstacles (FILE CLOSED)" << std::endl;
    FileHandler::createFile("test_file.txt");
    FileHandler::openWriteFile("test_file.txt", file_stream);
    FileHandler::closeFile(file_stream);
    test_result = FileHandler::saveFile("test_file.txt", file_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    FileHandler::deleteFile("test_file.txt");
    std::cout << "Saving with obstacles (FILE CLOSED) << TEST_2_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileHandler::saveWriteFile() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

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

void tests::test_goToLine()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileEditor::goToLine() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result;
    std::string checkpoint_line;

    std::ifstream file_read_stream;

    std::cout << "TEST_1_START >> Going to line # without obstacles" << std::endl;
    FileHandler::openReadFile("text_file.txt", file_read_stream);
    test_result = FileEditor::goToLine(1, file_read_stream);
    checkpoint_line = "";
    if (test_result) { std::getline(file_read_stream, checkpoint_line); }
    FileHandler::closeFile(file_read_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    if (test_result) { std::cout << checkpoint_line << std::endl; }
    std::cout << "Going to line # without obstacles << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_2_START >> Going to line # with obstacles (OUT OF BORDERS)" << std::endl;
    FileHandler::openReadFile("text_file.txt", file_read_stream);
    test_result = FileEditor::goToLine(6, file_read_stream);
    checkpoint_line = "";
    if (test_result) { std::getline(file_read_stream, checkpoint_line); }
    FileHandler::closeFile(file_read_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    if (test_result) { std::cout << checkpoint_line << std::endl; }
    std::cout << "Going to line # with obstacles (OUT OF BORDERS) << TEST_2_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_3_START >> Going to line # with obstacles (FILE DO NOT OPEN)" << std::endl;
    test_result = FileEditor::goToLine(6, file_read_stream);
    checkpoint_line = "";
    if (test_result) { std::getline(file_read_stream, checkpoint_line); }
    FileHandler::closeFile(file_read_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    if (test_result) { std::cout << checkpoint_line << std::endl; }
    std::cout << "Going to line # with obstacles (FILE DO NOT OPEN) << TEST_3_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileEditor::goToLine() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void tests::test_copyLine()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileEditor::copyLine() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result;
    std::string checkpoint_line;

    std::ifstream file_read_stream;

    std::cout << "TEST_1_START >> Copying line # without obstacles" << std::endl;
    FileHandler::openReadFile("text_file.txt", file_read_stream);
    checkpoint_line = "";
    test_result = FileEditor::copyLine(1, file_read_stream, checkpoint_line);
    FileHandler::closeFile(file_read_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    if (test_result) { std::cout << "Copied string: "<< checkpoint_line << std::endl; }
    std::cout << "Copying line # without obstacles << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_2_START >> Copying line # with obstacles (OUT OF BORDERS)" << std::endl;
    FileHandler::openReadFile("text_file.txt", file_read_stream);
    checkpoint_line = "";
    test_result = FileEditor::copyLine(6, file_read_stream, checkpoint_line);
    FileHandler::closeFile(file_read_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    if (test_result) { std::cout << "Copied string: "<< checkpoint_line << std::endl; }
    std::cout << "Copying line # with obstacles (OUT OF BORDERS) << TEST_2_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_3_START >> Copying line # with obstacles (FILE DO NOT OPEN)" << std::endl;
    checkpoint_line = "";
    test_result = FileEditor::copyLine(6, file_read_stream, checkpoint_line);
    FileHandler::closeFile(file_read_stream);
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    if (test_result) { std::cout << "Copied string: "<< checkpoint_line << std::endl; }
    std::cout << "Copying line # with obstacles (FILE DO NOT OPEN) << TEST_3_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileEditor::copyLine() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void tests::test_changeLine()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileEditor::changeLine() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result = false;

    std::cout << "TEST_1_START >> Complex test changing line # with obstacles (OUT OF BOUNDS)" << std::endl;
    int counter = 0;
    while (!test_result)
    {
        test_result = !(FileEditor::changeLine(counter, "text_file.txt", "Another diff 124 line", ";"));
        counter++;
    }
    std::cout << "Complex test changing line # with obstacles (OUT OF BOUNDS) << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_2_START >> Changing line # with obstacles (NO FILE EXISTS)" << std::endl;
    test_result = FileEditor::changeLine(counter, "wrong_file.txt", "Another diff 124 line", ";");
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Changing line # with obstacles (NO FILE EXISTS) << TEST_2_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileEditor::changeLine() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void tests::test_insertLine()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileEditor::insertLine() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result = false;

    std::cout << "TEST_1_START >> Complex test inserting line # with obstacles (OUT OF BOUNDS)" << std::endl;
    for (int counter = 0; counter < 4; counter++)
    {
        test_result = !(FileEditor::insertLine(counter, "text_file.txt", "Inserted 124 line", ";"));
    }
    std::cout << "Complex test inserting line # with obstacles (OUT OF BOUNDS) << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_2_START >> Inserting line # with obstacles (NO FILE EXISTS)" << std::endl;
    test_result = FileEditor::insertLine(0, "wrong_file.txt", "Another diff 124 line", ";");
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Inserting line # with obstacles (NO FILE EXISTS) << TEST_2_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    std::cout << "TEST_3_START >> Inserting line # with obstacles (WRONG LINE)" << std::endl;
    test_result = FileEditor::insertLine(15, "text_file.txt", "Another diff 124 line", ";");
    std::cout << "RESULT OF EXECUTION: " << test_result << std::endl;
    std::cout << "Inserting line # with obstacles (WRONG LINE) << TEST_3_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileEditor::insertLine() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void tests::test_removeLine()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileEditor::removeLine() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result = false;

    std::cout << "TEST_1_START >> Complex test removing line # with obstacles (OUT OF BOUNDS)" << std::endl;
    for (int counter = 0; counter < 5; counter++)
    {
        test_result = !(FileEditor::removeLine(1, "text_file.txt"));
        std::cout << "RESULT OF EXECUTION: " << !test_result << std::endl;
    }
    std::cout << "Complex test removing line # with obstacles (OUT OF BOUNDS) << TEST_1_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileEditor::removeLine() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

void tests::test_addToLine()
{
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "~~FileEditor::addToLine() TEST_SUITE_START~~" << std::endl;
    std::cout << std::endl;

    bool test_result = false;

    std::cout << "TEST_1_START >> Complex test adding to line # with obstacles (OUT OF BOUNDS)" << std::endl;
    for (int counter = 0; counter < 4; counter++)
    {
        test_result = !(FileEditor::addToLine(counter, "text_file.txt", "Additional", ";"));
        std::cout << "RESULT OF EXECUTION: " << !test_result << std::endl;
    }
    std::cout << "Complex test adding to line # with obstacles (OUT OF BOUNDS) << TEST_1_END" << std::endl;

    std::cout << "-----------------------------------" << std::endl;

    test_result = false;
    std::cout << "TEST_2_START >> Complex test adding to line # with obstacles (OUT OF BOUNDS)" << std::endl;
    for (int counter = 0; counter < 4; counter++)
    {
        test_result = !(FileEditor::addToLine(counter, "text_file.txt", "Additional", ";", 5));
        std::cout << "RESULT OF EXECUTION: " << !test_result << std::endl;
    }
    std::cout << "Complex test adding to line # with obstacles (OUT OF BOUNDS) << TEST_2_END" << std::endl;

    std::cout << std::endl;
    std::cout << "~~~FileEditor::addToLine() TEST_SUITE_END~~~" << std::endl;
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
}

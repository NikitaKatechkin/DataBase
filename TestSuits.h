#ifndef TESTSUITS_H_INCLUDED
#define TESTSUITS_H_INCLUDED

#include "FileHandler.h"
#include "FileEditor.h"
#include "tools.h"

namespace tests
{
    void test_createFile();
    void test_deleteFile();

    void test_openReadFile();
    void test_openRewriteFile();
    void test_openWriteFile();
    void test_closeReadFile();
    void test_closeWriteFile();
    void test_saveWriteFile();

    void test_goToLine();
    void test_copyLine();
    void test_changeLine();
    void test_insertLine();
    void test_removeLine();
    void test_addToLine();
}


#endif // TESTSUITS_H_INCLUDED

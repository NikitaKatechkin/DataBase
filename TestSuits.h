#ifndef TESTSUITS_H_INCLUDED
#define TESTSUITS_H_INCLUDED

#include "FileHandler.h"

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
}


#endif // TESTSUITS_H_INCLUDED

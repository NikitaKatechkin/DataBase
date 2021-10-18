#include "DataBase.h"
#include "TestSuits.h"
#include "testField.h"

#include <string>
#include "DataBaseHandler.h"

/*void print_vec(const std::vector<int>& vec)
{
    for (auto x: vec) {
         std::cout << ' ' << x;
    }
    std::cout << '\n';
}*/

int main()
{
    //tests::test_createFile();
    //tests::test_closeWriteFile();
    //tests::test_deleteFile();
    //tests::test_openReadFile();
    //tests::test_openRewriteFile();
    //tests::test_openWriteFile();
    //tests::test_closeReadFile();
    //tests::test_closeWriteFile();
    //tests::test_saveWriteFile();
    //tests::test_goToLine();
    //tests::test_copyLine();
    //tests::test_changeLine();
    //tests::test_insertLine();
    //tests::test_removeLine();
    //tests::test_addToLine();

    /*std::string test = prototype_functionality::safeInputString("Input string");
    std::cout << test << std::endl;
    bool testBool = prototype_functionality::safeInputBool("Input bool");
    std::cout << testBool << std::endl;*/

    //prototype_functionality::createDataBase();

    /*std::string line = "name;name1;name2;";
    std::string str = "name";

    std::string test = "";
    std::vector<int> occurencies;
    std::cout << DataBaseFeatureHandler::getPosOfOccurencies(line, ";", occurencies) << std::endl;
    std::cout << DataBaseFeatureHandler::independentGetFeature(0, line, ";", test) << std::endl;
    std::cout << test << std::endl;

    std::vector<int> result = occurencies;
    for (auto itr = result.begin(); itr!=result.end(); itr++)
    {
        std::cout << *itr << std::endl;
    }

    std::vector<std::string> features;
    std::cout << DataBaseFeatureHandler::independentGetVecOfFeatures(line, ";", features) << std::endl;
    for (auto itr = features.begin(); itr!=features.end(); itr++)
    {
        std::cout << *itr << std::endl;
    }

    test = "";
    std::cout << DataBaseFeatureHandler::mergeVecOfFeaturesToStr(features, ";", test) << std::endl;
    std::cout << test << std::endl;

    std::cout << DataBaseFeatureHandler::insertFeature(line, ";", "name3", 3) << std::endl;
    std::cout << line << std::endl;*/

    /*std::vector<int> vec(3,100);
    print_vec(vec);

    auto it = vec.begin();
    it = vec.insert(it + 0, 200);
    print_vec(vec);*/


    //DataBaseHandler::createDataBase();
    //DataBaseHandler::deletingDataBase();

    /*std::vector<int> results;
    std::ifstream database_read_stream;
    std::string data_base_file_name;
    std::vector<std::string> key_features_list;
    std::vector<std::string> non_key_features_list;
    std::vector<std::string> search_features_values_list;
    std::vector<unsigned int> search_features_order_indexes_list;
    std::vector<std::string> features_list;

    bool status = DataBaseHandlerPrototypeFunctionality::searchObjectsDataBaseV2Acknowledge(results, database_read_stream, data_base_file_name, key_features_list, non_key_features_list,
                                                                                            search_features_values_list, search_features_order_indexes_list, features_list);
    std::cout << status << std::endl;
    //std::cout << "FOUNDED RECORDS:" << std::endl;
    std::vector<std::string> founded_records;
    for (auto iter = results.begin(); iter < results.end(); iter++)
    {
        std::string line;
        bool ALARM_FLAG  = FileEditor::copyLineV2(*iter, data_base_file_name, line);
        if (!ALARM_FLAG) {std::cout << "BAD EXCEPTION INVALID NOT PROCESSED OUTPUT" << std::endl; break;}
        founded_records.push_back(line);
    }

    std::cout << "FOUNDED RECORDS:" << std::endl;
    for (auto iter = founded_records.begin(); iter < founded_records.end(); iter++)
    {
        std::cout << (*iter) << std::endl;
    }*/

    /*std::cout << CleanDBHandler::isStringDataBaseFileName(".txt", ".txt") << std::endl;
    std::cout << CleanDBHandler::isStringDataBaseFileName("1.txt", ".txt") << std::endl;
    std::cout << CleanDBHandler::isStringDataBaseFileName("txt", ".txt") << std::endl;
    std::cout << CleanDBHandler::isStringDataBaseFileName("28.txt1", ".txt") << std::endl;*/

    /*std::string file_name = "testDB.txt";
    CleanDBHandler::createDataBase(file_name);*/
    //std::cout << CleanDBHandler::clearDataBase(file_name) << std::endl;

    //std::ifstream file_stream;
    //FileHandler::openReadFile(file_name, file_stream);
    //std::cout << FileEditor::addToLine() << std::endl;

    /*std::string file_name = "hello.txt";
    std::cout << CleanDBHandler::createDataBase(file_name) << std::endl;
    CleanDBHandler::deletingDataBase(file_name);*/

    /*std::vector<int> results;
    std::ifstream database_read_stream;
    std::string data_base_file_name = "Database.txt";
    std::vector<std::string> key_features_list;
    std::vector<std::string> non_key_features_list;
    std::vector<std::string> search_features_values_list;
    std::vector<unsigned int> search_features_order_indexes_list;
    std::vector<std::string> features_list;

    bool status = CleanDBHandler::searchObjectsDataBaseV2Acknowledge(results, database_read_stream, data_base_file_name, key_features_list, non_key_features_list,
                                                                                            search_features_values_list, search_features_order_indexes_list, features_list);
    std::cout << status << std::endl;
    std::vector<std::string> founded_records;
    for (auto iter = results.begin(); iter < results.end(); iter++)
    {
        std::string line;
        bool ALARM_FLAG  = FileEditor::copyLineV2(*iter, data_base_file_name, line);
        if (!ALARM_FLAG) {std::cout << "BAD EXCEPTION INVALID NOT PROCESSED OUTPUT" << std::endl; break;}
        founded_records.push_back(line);
    }

    std::cout << "FOUNDED RECORDS:" << std::endl;
    for (auto iter = founded_records.begin(); iter < founded_records.end(); iter++)
    {
        std::cout << (*iter) << std::endl;
    }*/

    /*std::string file_name = "text_file.txt";
    std::ifstream read_stream(file_name);
    FileEditor::removeLine(0, file_name);*/
    //std::cout << FileEditor::goToLine(4, read_stream) << std::endl;
    //FileEditor::changeLine(2, file_name, "", "");

    /*std::vector<int> results;
    std::ifstream database_read_stream;
    std::string data_base_file_name;
    std::vector<std::string> key_features_list;
    std::vector<std::string> non_key_features_list;
    std::vector<std::string> search_features_values_list;
    std::vector<unsigned int> search_features_order_indexes_list;
    std::vector<std::string> features_list;
    DataBaseHandler::deleteObjectDataBaseV2Acknowledge(results, database_read_stream, data_base_file_name, key_features_list, non_key_features_list,
                                                                                            search_features_values_list, search_features_order_indexes_list, features_list);
    std::cout << "FOUNDED RECORDS:" << std::endl;
    for (auto iter = key_features_list.begin(); iter < key_features_list.end(); iter++)
    {
        std::cout << (*iter) << std::endl;
    }*/

    /*std::vector<unsigned int> results;

    std::string data_base_file_name = "Database.txt";

    bool status = DataBaseHandler::searchRecordsDataBase(data_base_file_name, results);
    std::cout << status << std::endl;
    std::vector<std::string> founded_records;
    for (auto iter = results.begin(); iter < results.end(); iter++)
    {
        std::string line;
        bool ALARM_FLAG  = FileEditor::copyLineV2(*iter, data_base_file_name, line);
        if (!ALARM_FLAG) {std::cout << "BAD EXCEPTION INVALID NOT PROCESSED OUTPUT" << std::endl; break;}
        founded_records.push_back(line);
    }

    std::cout << "FOUNDED RECORDS:" << std::endl;
    for (auto iter = founded_records.begin(); iter < founded_records.end(); iter++)
    {
        std::cout << (*iter) << std::endl;
    }*/

    /*std::string data_base_file_name = "Database.txt";
    bool status = DataBaseHandler::addRecordsDataBase(data_base_file_name);
    std::cout << status << std::endl;*/

    /*std::string data_base_file_name = "Database.txt";
    bool status = DataBaseHandler::deleteRecordsDataBase(data_base_file_name);
    std::cout << status << std::endl;*/

    std::string file_name;
    DataBaseHandler::editRecordsDataBase(file_name);

    return 0;
}

#include "DataBaseHandler.h"

/*void DataBaseHandler::rclean(std::string& string_to_clean, const char& character_to_clean)
{
    while(string_to_clean[0] == character_to_clean)
    {
        string_to_clean.erase(0, 1);
    }
}

void DataBaseHandler::lclean(std::string& string_to_clean, const char& character_to_clean)
{
    while(string_to_clean[(string_to_clean.size() - 1)] == character_to_clean)
    {
        string_to_clean.erase((string_to_clean.size() - 1), 1);
    }
}

std::string DataBaseHandler::safeInputString(const std::string& l_invitation)
{
    std::string output = "";

    std::cout << l_invitation << " >> ";
    std::cin >> output;
    DataBaseHandler::rclean(output, ' ');
    DataBaseHandler::lclean(output, ' ');

    return output;
}

bool DataBaseHandler::safeInputBool(const std::string& l_invitation)
{
    std::string output = DataBaseHandler::safeInputString(l_invitation);
    DataBaseHandler::rclean(output, ' ');
    DataBaseHandler::lclean(output, ' ');
    while (!((output == "1") || (output == "0")))
    {
        std::cout << "Input error. Please try again (press 1 or 0)!!!" << std::endl;
        output = DataBaseHandler::safeInputString(l_invitation);
        DataBaseHandler::rclean(output, ' ');
        DataBaseHandler::lclean(output, ' ');
    }

    return (output=="1");
}

bool DataBaseHandler::addFieldToDataBase(const std::string& data_base_file_name)
{
    //TRYONG TO ADD FIELD NAME IN SERVICE NAMES LINE
    std::string field_name = DataBaseHandler::safeInputString("Input field name");
    bool NAME_ADDING_FLAG = FileEditor::addToLine(ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name,
                                                  field_name, ";");
    if (!NAME_ADDING_FLAG)
    {
        FileEditor::addToLine(ServiceLines::DATABASE_NAME_LINE, data_base_file_name, "", "\n");
        NAME_ADDING_FLAG = FileEditor::addToLine(ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, field_name, ";");
    }
    if (!NAME_ADDING_FLAG) { return NAME_ADDING_FLAG; }

    //CHECKING NAME FOR VALIDITY
    std::string name_service_line;
    bool CORRECT_READ_NAME_SERVICE_LINE_FLAG = FileEditor::copyLineV2(DataBaseHandler::ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, name_service_line);
    if (!CORRECT_READ_NAME_SERVICE_LINE_FLAG) { return CORRECT_READ_NAME_SERVICE_LINE_FLAG; }

    std::vector<std::string> features_list;
    bool FEATURE_EXISTANCE_FLAG = DataBaseFeatureHandler::independentGetVecOfFeatures(name_service_line, ";", features_list);
    if (!FEATURE_EXISTANCE_FLAG) { return FEATURE_EXISTANCE_FLAG; }

    std::string inspected_feature = (features_list.empty()) ? "" : *(features_list.end() - 1);
    features_list.pop_back();
    if (std::find(features_list.begin(), features_list.end(), inspected_feature) != features_list.end())
    {
        std::cout << "FIELD WITH NAME " << inspected_feature << "ALLREADY EXIST. PERFORMING ROLLING BACK" << std::endl;
        std::string rollback_line;
        bool CORRECT_ROLLBACK_LINE_FLAG = DataBaseFeatureHandler::mergeVecOfFeaturesToStr(features_list, ";", rollback_line);
        if (!CORRECT_ROLLBACK_LINE_FLAG) { return CORRECT_ROLLBACK_LINE_FLAG; }

        bool CORRECT_ROLLBACK_DONE_FLAG = FileEditor::changeLine(DataBaseHandler::ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, rollback_line, "");

        return CORRECT_ROLLBACK_DONE_FLAG;
    }

    //TRYONG TO ADD FIELD KEY SIGN IN SERVICE KEY SIGNS LINE
    std::string key_sign = (DataBaseHandler::safeInputBool("Input key sign (1 - key field / 0 - not key field)") ? "1" : "0");
    bool KEY_ADDING_FLAG = FileEditor::addToLine(ServiceLines::DATABASE_KEY_SIGNS_LINE, data_base_file_name, key_sign, ";");
    if (!KEY_ADDING_FLAG)
    {
        FileEditor::addToLine(ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, "", "\n");
        KEY_ADDING_FLAG = FileEditor::addToLine(ServiceLines::DATABASE_KEY_SIGNS_LINE, data_base_file_name, key_sign, ";");
    }

    return KEY_ADDING_FLAG;
}

bool DataBaseHandler::createDataBase()
{
    std::string data_base_file_name = DataBaseHandler::safeInputString("Input DataBase name to create");
    data_base_file_name += ".txt";

    bool CREATING_FILE_FLAG = FileHandler::createFile(data_base_file_name);
    if (!CREATING_FILE_FLAG) { return CREATING_FILE_FLAG; }

    bool WRITING_NAME_FILE_FLAG = FileEditor::changeLine(0, data_base_file_name, data_base_file_name, "");
    if (!WRITING_NAME_FILE_FLAG) { return WRITING_NAME_FILE_FLAG; }

    bool WRITING_FIELD_WITH_KEY_SIGN;
    for (int i = 0; i < 3; i++)
    {
        WRITING_FIELD_WITH_KEY_SIGN = DataBaseHandler::addFieldToDataBase(data_base_file_name);
        if (!WRITING_FIELD_WITH_KEY_SIGN) { break; }
    }

    std::string key_signs_service_line;
    bool CORRECT_READ_KEY_SIGNS_SERVICE_LINE_FLAG = FileEditor::copyLineV2(DataBaseHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE, data_base_file_name, key_signs_service_line);
    if (!CORRECT_READ_KEY_SIGNS_SERVICE_LINE_FLAG) { return CORRECT_READ_KEY_SIGNS_SERVICE_LINE_FLAG; }

    std::vector<std::string> features_list;
    bool FEATURE_EXISTANCE_FLAG = DataBaseFeatureHandler::independentGetVecOfFeatures(key_signs_service_line, ";", features_list);
    if (!FEATURE_EXISTANCE_FLAG) { return FEATURE_EXISTANCE_FLAG; }

    bool KEY_FIELD_EXISTANCE_FLAG = (std::find(features_list.begin(), features_list.end(), "1") != features_list.end());
    if (!KEY_FIELD_EXISTANCE_FLAG)
    {
        std::cout << "THERE IS NO KEY FIELD IN DATABASE. ABORTING CREATING PROCESS" << std::endl;
        return FileHandler::deleteFile(data_base_file_name);
    }

    return KEY_FIELD_EXISTANCE_FLAG;
}

bool DataBaseHandler::deletingDataBase()
{
    std::string data_base_file_name = DataBaseHandler::safeInputString("Input DataBase name to delete");
    data_base_file_name += ".txt";

    return FileHandler::deleteFile(data_base_file_name);
}

bool DataBaseHandler::openingReadDataBase(std::ifstream& l_database_read_file_stream)
{
    std::string data_base_file_name = DataBaseHandler::safeInputString("Input DataBase name to open");
    data_base_file_name += ".txt";

    return FileHandler::openReadFile(data_base_file_name, l_database_read_file_stream);
}

bool DataBaseHandler::openRewriteDataBase(std::ofstream& l_database_write_file_stream)
{
    std::string data_base_file_name = DataBaseHandler::safeInputString("Input DataBase name to open");
    data_base_file_name += ".txt";

    return FileHandler::openRewriteFile(data_base_file_name, l_database_write_file_stream);
}

bool DataBaseHandler::openWriteFileDataBase(std::ofstream& l_database_write_file_stream)
{
    std::string data_base_file_name = DataBaseHandler::safeInputString("Input DataBase name to open");
    data_base_file_name += ".txt";

    return FileHandler::openWriteFile(data_base_file_name, l_database_write_file_stream);
}

bool DataBaseHandler::openingReadDataBaseFileNameAcknowledge(std::ifstream& l_database_read_file_stream, std::string& result_database_file_name)
{
    result_database_file_name = DataBaseHandler::safeInputString("Input DataBase name to open");
    result_database_file_name += ".txt";

    return FileHandler::openReadFile(result_database_file_name, l_database_read_file_stream);
}

bool DataBaseHandler::openRewriteDataBaseFileNameAcknowledge(std::ofstream& l_database_write_file_stream, std::string& result_database_file_name)
{
    result_database_file_name = DataBaseHandler::safeInputString("Input DataBase name to open");
    result_database_file_name += ".txt";

    return FileHandler::openRewriteFile(result_database_file_name, l_database_write_file_stream);
}

bool DataBaseHandler::openWriteFileDataBaseFileNameAcknowledge(std::ofstream& l_database_write_file_stream, std::string& result_database_file_name)
{
    result_database_file_name = DataBaseHandler::safeInputString("Input DataBase name to open");
    result_database_file_name += ".txt";

    return FileHandler::openWriteFile(result_database_file_name, l_database_write_file_stream);
}

bool DataBaseHandler::saveDataBase(std::ifstream& l_database_file_read_stream)
{
    return FileHandler::saveFile(l_database_file_read_stream);
}

bool DataBaseHandler::saveDataBase(const std::string& l_database_file_path, std::ofstream& l_database_file_write_stream)
{
    return FileHandler::saveFile(l_database_file_path, l_database_file_write_stream);
}

bool DataBaseHandler::clearDataBase()
{
    std::string data_base_file_name = DataBaseHandler::safeInputString("Input DataBase name to delete");
    data_base_file_name += ".txt";

    bool SUCCES_DELETE_DATABASE_FLAG = FileHandler::deleteFile(data_base_file_name);
    if (!SUCCES_DELETE_DATABASE_FLAG) { return SUCCES_DELETE_DATABASE_FLAG; }
    bool SUCCES_CREATE_DATABASE_FLAG = FileHandler::createFile(data_base_file_name);

    return SUCCES_CREATE_DATABASE_FLAG;
}


// DATABASE HANDLER PROTOTYPE FUNCTIONALITY
//Independent
bool DataBaseHandlerPrototypeFunctionality::retrievingRecordsFromLine(std::vector<std::string>& record_list, std::string& data_base_file_name, unsigned int line_number)
{
    std::string line;
    bool CORRECT_READ_LINE_FLAG = FileEditor::copyLineV2(line_number, data_base_file_name, line);
    if (!CORRECT_READ_LINE_FLAG) { return CORRECT_READ_LINE_FLAG; }

    bool RECORD_EXISTANCE_FLAG = DataBaseFeatureHandler::independentGetVecOfFeatures(line, ";", record_list);
    return RECORD_EXISTANCE_FLAG;
}
//Depend on DataBaseHandlerPrototypeFunctionality::retrievingRecordsFromLine 2
bool DataBaseHandlerPrototypeFunctionality::dividingKeyNonkeyFeatures(std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                                                      std::string& data_base_file_name)
{
    //RETRIEVING FEATURES LIST
    std::vector<std::string> features_list;
    bool SUCCESS_RETRIEVING_FEATURES_NAME_LIST = DataBaseHandlerPrototypeFunctionality::retrievingRecordsFromLine(features_list, data_base_file_name,
                                                                                                                  DataBaseHandler::ServiceLines::DATABASE_FIELDS_LINE);
    if (!SUCCESS_RETRIEVING_FEATURES_NAME_LIST) { return SUCCESS_RETRIEVING_FEATURES_NAME_LIST; }

    //RETRIEVING KEY LIST

    std::vector<std::string> key_signs_feature_list;
    bool SUCCESS_RETRIEVING_KEY_SIGNS_LIST = DataBaseHandlerPrototypeFunctionality::retrievingRecordsFromLine(key_signs_feature_list, data_base_file_name,
                                                                                                                  DataBaseHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE);
    if (!SUCCESS_RETRIEVING_KEY_SIGNS_LIST) { return SUCCESS_RETRIEVING_KEY_SIGNS_LIST; }

    //DEVIDING FEATURE BETWEEN KEY AND NON KEY
    unsigned int number_of_features = (features_list.size() != key_signs_feature_list.size()) ? 0 : features_list.size();
    for (unsigned int feature_index = 0; feature_index < number_of_features; feature_index++)
    {
        if (key_signs_feature_list[feature_index] == "1") { key_features_list.push_back(features_list[feature_index]); }
        else { non_key_features_list.push_back(features_list[feature_index]); }
    }

    return true;
}*/
//Independent 3
/*bool DataBaseHandlerPrototypeFunctionality::creatingSearchFeaturesOrderVector(std::vector<unsigned int>& search_features_order_indexes_list, std::vector<std::string>& key_features_list,
                                           std::vector<std::string>& non_key_features_list, std::vector<std::string>& features_list)
{
    bool user_answer;
    for (auto iter = key_features_list.begin(); iter != key_features_list.end(); )
    {
        //DataBaseHandler::safeInputBool("TEST: ");
        user_answer = DataBaseHandler::safeInputBool("Do you want to search by '" + (*iter) + "' key");
        if (!user_answer) { key_features_list.erase(iter); }
        else
        {
            unsigned int current_search_features_order_index = std::find(features_list.begin(), features_list.end(), (*iter)) - features_list.begin();
            search_features_order_indexes_list.push_back(current_search_features_order_index);
            iter++;
        }
    }
    //if (key_features_list.empty()) { std::cout << "No key feature has been choosen. Returning empty result list" << std::endl; return false; }

    for (auto iter = non_key_features_list.begin(); iter != non_key_features_list.end(); )
    {
        user_answer = DataBaseHandler::safeInputBool("Do you want to search by '" + (*iter) + "' key");
        if (!user_answer) { non_key_features_list.erase(iter); }
        else
        {
            unsigned int current_search_features_order_index = std::find(features_list.begin(), features_list.end(), (*iter)) - features_list.begin();
            search_features_order_indexes_list.push_back(current_search_features_order_index);
            iter++;
        }
    }

    if (key_features_list.empty() && non_key_features_list.empty()) { std::cout << "No feature has been choosen. Returning empty result list" << std::endl; return false; }
    std::sort(search_features_order_indexes_list.begin(), search_features_order_indexes_list.end());

    return true;
}*/
//Independent 1
/*void DataBaseHandlerPrototypeFunctionality::gettingSearchingValuesForSearchingFeatures(std::vector<std::string>& search_features_values_list,
                                                                                       std::vector<unsigned int>& search_features_order_indexes_list, std::vector<std::string>& features_list)
{
    std::string answer;
    for (auto iter = search_features_order_indexes_list.begin(); iter != search_features_order_indexes_list.end(); iter++)
    {
        answer = DataBaseHandler::safeInputString("Input searching value for '" + features_list[(*iter)] + "' feature");
        search_features_values_list.push_back(answer);
    }
}*/
//Independent 1
/*void DataBaseHandlerPrototypeFunctionality::searchingForFeaturesValues(std::vector<int>& founded_record_list, std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                                                       std::string& data_base_file_name)
{
    std::vector<std::string> current_object_feature_vector;
    std::vector<std::string> searched_values_current_object_feature;
    std::string object;
    unsigned int line_index = int(DataBaseHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE) + 1;

    while(FileEditor::copyLineV2(line_index, data_base_file_name, object))
    {
        //ERASEING NON SEARCHABLE FEATURES VALUES
        DataBaseFeatureHandler::independentGetVecOfFeatures(object, ";", current_object_feature_vector);
        for (unsigned int correction = 0; correction < search_features_order_indexes_list.size(); correction++)
        {
            searched_values_current_object_feature.push_back(current_object_feature_vector[search_features_order_indexes_list[correction]]);
        }


        if (searched_values_current_object_feature.size() != search_features_values_list.size()) { std::cout << "ALARM. FILTERING NOT WORKING WELL" << std::endl; return; }

        //ADDING MATCHING LINE INDEX
        if(searched_values_current_object_feature == search_features_values_list) { founded_record_list.push_back(line_index); }

        searched_values_current_object_feature.clear();
        current_object_feature_vector.clear();
        line_index++;
    }
}*/
//Depend on all above in the namespace 2
/*std::vector<int> DataBaseHandlerPrototypeFunctionality::searchObjectsDataBaseV2()
{
    std::vector<int> result;

    std::ifstream database_read_stream;
    std::string data_base_file_name;

    bool OPENING_FILE_FLAG = DataBaseHandler::openingReadDataBaseFileNameAcknowledge(database_read_stream, data_base_file_name);
    if (!OPENING_FILE_FLAG) { return result; }

    std::vector<std::string> key_features_list;
    std::vector<std::string> non_key_features_list;

    bool SUCCESS_DIVIDING_FLAG = DataBaseHandlerPrototypeFunctionality::dividingKeyNonkeyFeatures(key_features_list, non_key_features_list, data_base_file_name);
    if (!SUCCESS_DIVIDING_FLAG) { return result; }

    std::vector<std::string> features_list;
    bool SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG = DataBaseHandlerPrototypeFunctionality::retrievingRecordsFromLine(features_list, data_base_file_name,
                                                                                                                  DataBaseHandler::ServiceLines::DATABASE_FIELDS_LINE);
    if (!SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG) { return result; }

    std::vector<unsigned int> search_features_order_indexes_list;
    bool SUCCESS_CREATING_SEARCH_FEATURE_ORDER_VECTOR_FLAG = DataBaseHandlerPrototypeFunctionality::creatingSearchFeaturesOrderVector(search_features_order_indexes_list, key_features_list,
                                                                             non_key_features_list, features_list);
    if (!SUCCESS_CREATING_SEARCH_FEATURE_ORDER_VECTOR_FLAG) { return result; }

    std::vector<std::string> search_features_values_list;
    DataBaseHandlerPrototypeFunctionality::gettingSearchingValuesForSearchingFeatures(search_features_values_list, search_features_order_indexes_list, features_list);
    DataBaseHandlerPrototypeFunctionality::searchingForFeaturesValues(result, search_features_values_list, search_features_order_indexes_list, data_base_file_name);

    return result;
}*/
//All dependencies of DataBaseHandlerPrototypeFunctionality::searchObjectsDataBaseV2 2
/*bool DataBaseHandlerPrototypeFunctionality::searchObjectsDataBaseV2Acknowledge(std::vector<int>& founded_record_index_list, std::ifstream& database_read_stream, std::string& data_base_file_name,
                                                                               std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                                                               std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                                                               std::vector<std::string>& features_list)
{
    //std::ifstream database_read_stream;
    //std::string data_base_file_name;

    bool OPENING_FILE_FLAG = DataBaseHandler::openingReadDataBaseFileNameAcknowledge(database_read_stream, data_base_file_name);
    if (!OPENING_FILE_FLAG) { return OPENING_FILE_FLAG; }

    //std::vector<std::string> key_features_list;
    //std::vector<std::string> non_key_features_list;

    bool SUCCESS_DIVIDING_FLAG = DataBaseHandlerPrototypeFunctionality::dividingKeyNonkeyFeatures(key_features_list, non_key_features_list, data_base_file_name);
    if (!SUCCESS_DIVIDING_FLAG) { return SUCCESS_DIVIDING_FLAG; }

    //std::vector<std::string> features_list;
    bool SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG = DataBaseHandlerPrototypeFunctionality::retrievingRecordsFromLine(features_list, data_base_file_name,
                                                                                                                  DataBaseHandler::ServiceLines::DATABASE_FIELDS_LINE);
    if (!SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG) { return SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG; }

    //std::vector<unsigned int> search_features_order_indexes_list;
    bool SUCCESS_CREATING_SEARCH_FEATURE_ORDER_VECTOR_FLAG = DataBaseHandlerPrototypeFunctionality::creatingSearchFeaturesOrderVector(search_features_order_indexes_list, key_features_list,
                                                                             non_key_features_list, features_list);
    if (SUCCESS_CREATING_SEARCH_FEATURE_ORDER_VECTOR_FLAG)
    {
        std::vector<std::string> search_features_values_list;
        DataBaseHandlerPrototypeFunctionality::gettingSearchingValuesForSearchingFeatures(search_features_values_list, search_features_order_indexes_list, features_list);
        DataBaseHandlerPrototypeFunctionality::searchingForFeaturesValues(founded_record_index_list, search_features_values_list, search_features_order_indexes_list, data_base_file_name);
    }

    return SUCCESS_CREATING_SEARCH_FEATURE_ORDER_VECTOR_FLAG;
}*/

/*std::vector<int> DataBaseHandlerPrototypeFunctionality::searchObjectsDataBase()
{
    std::vector<int> result;

    std::ifstream database_read_stream;
    std::string data_base_file_name;

    bool OPENING_FILE_FLAG = DataBaseHandler::openingReadDataBaseFileNameAcknowledge(database_read_stream, data_base_file_name);
    if (!OPENING_FILE_FLAG) { return result; }

    std::vector<std::string> key_features_list;
    std::vector<std::string> non_key_features_list;

    //RETRIEVING FEATURES LIST
    std::string name_service_line;
    bool CORRECT_READ_NAME_SERVICE_LINE_FLAG = FileEditor::copyLineV2(DataBaseHandler::ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, name_service_line);
    if (!CORRECT_READ_NAME_SERVICE_LINE_FLAG) { return result; }

    std::vector<std::string> features_list;
    bool FEATURE_EXISTANCE_FLAG = DataBaseFeatureHandler::independentGetVecOfFeatures(name_service_line, ";", features_list);
    if (!FEATURE_EXISTANCE_FLAG) { return result; }


    //RETRIEVING KEY LIST
    std::string key_signs_service_line;
    bool CORRECT_READ_KEY_SIGNS_SERVICE_LINE_FLAG = FileEditor::copyLineV2(DataBaseHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE, data_base_file_name, key_signs_service_line);
    if (!CORRECT_READ_KEY_SIGNS_SERVICE_LINE_FLAG) { return result; }

    std::vector<std::string> key_signs_feature_list;
    bool KEY_EXISTANCE_FLAG = DataBaseFeatureHandler::independentGetVecOfFeatures(key_signs_service_line, ";", key_signs_feature_list);
    if (!KEY_EXISTANCE_FLAG) { return result; }

    //DEVIDING FEATURE BETWEEN KEY AND NON KEY
    unsigned int number_of_features = (features_list.size() != key_signs_feature_list.size()) ? 0 : features_list.size();
    for (unsigned int feature_index = 0; feature_index < number_of_features; feature_index++)
    {
        if (key_signs_feature_list[feature_index] == "1") { key_features_list.push_back(features_list[feature_index]); }
        else { non_key_features_list.push_back(features_list[feature_index]); }
    }


    //CREATING SEARCH FEATURE ORDER VECTOR
    std::vector<unsigned int> search_features_order_indexes_list;

    bool user_answer;
    for (auto iter = key_features_list.begin(); iter != key_features_list.end(); )
    {
        //DataBaseHandler::safeInputBool("TEST: ");
        user_answer = DataBaseHandler::safeInputBool("Do you want to search by '" + (*iter) + "' key");
        if (!user_answer) { key_features_list.erase(iter); }
        else
        {
            unsigned int current_search_features_order_index = std::find(features_list.begin(), features_list.end(), (*iter)) - features_list.begin();
            search_features_order_indexes_list.push_back(current_search_features_order_index);
            iter++;
        }
    }
    if (key_features_list.empty()) { std::cout << "No key feature has been choosen. Returning empty result list" << std::endl; return result; }

    for (auto iter = non_key_features_list.begin(); iter != non_key_features_list.end(); )
    {
        user_answer = DataBaseHandler::safeInputBool("Do you want to search by '" + (*iter) + "' key");
        if (!user_answer) { non_key_features_list.erase(iter); }
        else
        {
            unsigned int current_search_features_order_index = std::find(features_list.begin(), features_list.end(), (*iter)) - features_list.begin();
            search_features_order_indexes_list.push_back(current_search_features_order_index);
            iter++;
        }
    }

    std::sort(search_features_order_indexes_list.begin(), search_features_order_indexes_list.end());


    //ASKING FOR SEARCHING VALUES
    std::vector<std::string> search_features_values_list;

    std::string answer;
    for (auto iter = search_features_order_indexes_list.begin(); iter != search_features_order_indexes_list.end(); iter++)
    {
        answer = DataBaseHandler::safeInputString("Input searching value for '" + features_list[(*iter)] + "' feature");
        search_features_values_list.push_back(answer);
    }

    //SEARCHING
    std::vector<std::string> current_object_feature_vector;
    std::vector<std::string> searched_values_current_object_feature;
    std::string object;
    unsigned int line_index = int(DataBaseHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE) + 1;

    while(FileEditor::copyLineV2(line_index, data_base_file_name, object))
    {
        //ERASEING NON SEARCHABLE FEATURES VALUES
        DataBaseFeatureHandler::independentGetVecOfFeatures(object, ";", current_object_feature_vector);
        for (unsigned int correction = 0; correction < search_features_order_indexes_list.size(); correction++)
        {
            searched_values_current_object_feature.push_back(current_object_feature_vector[search_features_order_indexes_list[correction]]);
        }

        if (searched_values_current_object_feature.size() != search_features_values_list.size()) { std::cout << "ALARM. FILTERING NOT WORKING WELL" << std::endl; return result; }

        //ADDING MATCHING LINE INDEX
        if(searched_values_current_object_feature == search_features_values_list) { result.push_back(line_index); }

        searched_values_current_object_feature.clear();
        current_object_feature_vector.clear();
        line_index++;
    }


    return result;
}*/

/** CLEAN DATA BASE HANDLER FUNCTIONALITY **/

///DATA_BASE_HANDLER NAMESPACE FUNCTIONALITY

bool CleanDBHandler::isStringDataBaseFileName(const std::string& file_name, const std::string& extension)
{
    if (extension.size() >= file_name.size()) { return false; }

    for (unsigned int index = 0; index < extension.size(); index++)
    {
        if (file_name[(file_name.size() - 1) - index] != extension[(extension.size() - 1) - index]) { return false; }
    }

    return true;
}

bool CleanDBHandler::openingReadDataBaseFileNameAcknowledge(std::ifstream& data_base_read_file_stream, std::string& result_database_file_name)
{
    if(!isStringDataBaseFileName(result_database_file_name, ".txt"))
    {
        result_database_file_name = CustomIO::safeInputString("Input DataBase name to open");
        result_database_file_name += ".txt";
    }

    return FileHandler::openReadFile(result_database_file_name, data_base_read_file_stream);
}

bool CleanDBHandler::openRewriteDataBaseFileNameAcknowledge(std::ofstream& data_base_write_file_stream, std::string& result_database_file_name)
{
    if(!isStringDataBaseFileName(result_database_file_name, ".txt"))
    {
        result_database_file_name = CustomIO::safeInputString("Input DataBase name to open");
        result_database_file_name += ".txt";
    }

    return FileHandler::openRewriteFile(result_database_file_name, data_base_write_file_stream);
}

bool CleanDBHandler::openWriteFileDataBaseFileNameAcknowledge(std::ofstream& data_base_write_file_stream, std::string& result_database_file_name)
{
    if(!isStringDataBaseFileName(result_database_file_name, ".txt"))
    {
        result_database_file_name = CustomIO::safeInputString("Input DataBase name to open");
        result_database_file_name += ".txt";
    }

    return FileHandler::openWriteFile(result_database_file_name, data_base_write_file_stream);
}

bool CleanDBHandler::addFieldToDataBase(const std::string& data_base_file_name)
{
    //TRYONG TO ADD FIELD NAME IN SERVICE NAMES LINE
    std::string field_name = CustomIO::safeInputString("Input field name");
    bool NAME_ADDING_FLAG = FileEditor::addToLine(CleanDBHandler::ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name,
                                                  field_name, ";");
    if (!NAME_ADDING_FLAG)
    {
        FileEditor::addToLine(CleanDBHandler::ServiceLines::DATABASE_NAME_LINE, data_base_file_name, "", "\n");
        NAME_ADDING_FLAG = FileEditor::addToLine(CleanDBHandler::ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, field_name, ";");
    }
    if (!NAME_ADDING_FLAG) { return NAME_ADDING_FLAG; }

    //CHECKING NAME FOR VALIDITY
    std::string name_service_line;
    bool CORRECT_READ_NAME_SERVICE_LINE_FLAG = FileEditor::copyLineV2(CleanDBHandler::ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, name_service_line);
    if (!CORRECT_READ_NAME_SERVICE_LINE_FLAG) { return CORRECT_READ_NAME_SERVICE_LINE_FLAG; }

    std::vector<std::string> features_list;
    bool FEATURE_EXISTANCE_FLAG = DataBaseFeatureHandler::independentGetVecOfFeatures(name_service_line, ";", features_list);
    if (!FEATURE_EXISTANCE_FLAG) { return FEATURE_EXISTANCE_FLAG; }

    std::string inspected_feature = (features_list.empty()) ? "" : *(features_list.end() - 1);
    features_list.pop_back();
    if (std::find(features_list.begin(), features_list.end(), inspected_feature) != features_list.end())
    {
        std::cout << "FIELD WITH NAME " << inspected_feature << "ALLREADY EXIST. PERFORMING ROLLING BACK" << std::endl;
        std::string rollback_line;
        bool CORRECT_ROLLBACK_LINE_FLAG = DataBaseFeatureHandler::mergeVecOfFeaturesToStr(features_list, ";", rollback_line);
        if (!CORRECT_ROLLBACK_LINE_FLAG) { return CORRECT_ROLLBACK_LINE_FLAG; }

        bool CORRECT_ROLLBACK_DONE_FLAG = FileEditor::changeLine(CleanDBHandler::ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, rollback_line, "");

        return CORRECT_ROLLBACK_DONE_FLAG;
    }

    //TRYONG TO ADD FIELD KEY SIGN IN SERVICE KEY SIGNS LINE
    std::string key_sign = (CustomIO::safeInputBool("Input key sign (1 - key field / 0 - not key field)") ? "1" : "0");
    bool KEY_ADDING_FLAG = FileEditor::addToLine(CleanDBHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE, data_base_file_name, key_sign, ";");
    if (!KEY_ADDING_FLAG)
    {
        FileEditor::addToLine(CleanDBHandler::ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, "", "\n");
        KEY_ADDING_FLAG = FileEditor::addToLine(CleanDBHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE, data_base_file_name, key_sign, ";");
    }

    return KEY_ADDING_FLAG;
}

bool CleanDBHandler::deletingDataBase(std::string& data_base_file_name)
{
    if(!isStringDataBaseFileName(data_base_file_name, ".txt"))
    {
        data_base_file_name = CustomIO::safeInputString("Input DataBase name to delete");
        data_base_file_name += ".txt";
    }

    return FileHandler::deleteFile(data_base_file_name);
}

bool CleanDBHandler::clearDataBase(std::string& data_base_file_name)
{
    if(!isStringDataBaseFileName(data_base_file_name, ".txt"))
    {
        data_base_file_name = CustomIO::safeInputString("Input DataBase name to clear");
        data_base_file_name += ".txt";
    }

    std::ifstream tmp_data_base_read_file_stream;
    bool SUCCESS_OPEN_READ_FILE_FLAG = FileHandler::openReadFile(data_base_file_name, tmp_data_base_read_file_stream);
    if (!SUCCESS_OPEN_READ_FILE_FLAG) { return SUCCESS_OPEN_READ_FILE_FLAG; }

    bool SUCCESS_CLOSE_FLAG = FileHandler::closeFile(tmp_data_base_read_file_stream);
    if (!SUCCESS_CLOSE_FLAG) { return SUCCESS_CLOSE_FLAG; }

    std::string tmp_line = "";
    std::vector<std::string> service_lines_dump;
    bool SUCCESS_COPY_SERVICE_LINE_FLAG = true;
    for (int i = 0; i <= CleanDBHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE; i++)
    {
        SUCCESS_COPY_SERVICE_LINE_FLAG = FileEditor::copyLineV2(i, data_base_file_name, tmp_line);
        if (!SUCCESS_COPY_SERVICE_LINE_FLAG) { return SUCCESS_COPY_SERVICE_LINE_FLAG; }
        service_lines_dump.push_back(tmp_line);
    }

    bool SUCCES_DELETE_DATABASE_FLAG = FileHandler::deleteFile(data_base_file_name);
    if (!SUCCES_DELETE_DATABASE_FLAG) { return SUCCES_DELETE_DATABASE_FLAG; }
    bool SUCCES_CREATE_DATABASE_FLAG = FileHandler::createFile(data_base_file_name);
    if (!SUCCES_CREATE_DATABASE_FLAG) { return SUCCES_CREATE_DATABASE_FLAG; }

    bool WRITING_NAME_FILE_FLAG = FileEditor::changeLine(CleanDBHandler::ServiceLines::DATABASE_NAME_LINE, data_base_file_name, service_lines_dump[CleanDBHandler::ServiceLines::DATABASE_NAME_LINE], "");
    if (!WRITING_NAME_FILE_FLAG) { return WRITING_NAME_FILE_FLAG; }

    bool SUCCESS_SERVICE_LINE_ADDING_FLAG = true;
    for (int i = 1; i <= CleanDBHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE; i++)
    {
        SUCCESS_SERVICE_LINE_ADDING_FLAG = FileEditor::addToLine(i, data_base_file_name,
                                                  service_lines_dump[i], "");
        if (!SUCCESS_SERVICE_LINE_ADDING_FLAG)
        {
            FileEditor::addToLine(i - 1, data_base_file_name, "", "\n");
            SUCCESS_SERVICE_LINE_ADDING_FLAG = FileEditor::addToLine(i, data_base_file_name, service_lines_dump[i], "");
        }
        if (!SUCCESS_SERVICE_LINE_ADDING_FLAG) { return SUCCESS_SERVICE_LINE_ADDING_FLAG; }
    }

    return SUCCESS_SERVICE_LINE_ADDING_FLAG;
}

bool CleanDBHandler::createDataBase(std::string& data_base_file_name)
{
    if(!isStringDataBaseFileName(data_base_file_name, ".txt"))
    {
        data_base_file_name = CustomIO::safeInputString("Input DataBase name to create");
        data_base_file_name += ".txt";
    }

    bool CREATING_FILE_FLAG = FileHandler::createFile(data_base_file_name);
    if (!CREATING_FILE_FLAG) { return CREATING_FILE_FLAG; }

    bool WRITING_NAME_FILE_FLAG = FileEditor::changeLine(0, data_base_file_name, data_base_file_name, "");
    if (!WRITING_NAME_FILE_FLAG) { return WRITING_NAME_FILE_FLAG; }

    bool WRITING_FIELD_WITH_KEY_SIGN;
    for (int i = 0; i < 3; i++)
    {
        WRITING_FIELD_WITH_KEY_SIGN = CleanDBHandler::addFieldToDataBase(data_base_file_name);
        if (!WRITING_FIELD_WITH_KEY_SIGN) { /*return WRITING_FIELD_WITH_KEY_SIGN;*/ break; }
    }

    std::string key_signs_service_line;
    bool CORRECT_READ_KEY_SIGNS_SERVICE_LINE_FLAG = FileEditor::copyLineV2(CleanDBHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE, data_base_file_name, key_signs_service_line);
    if (!CORRECT_READ_KEY_SIGNS_SERVICE_LINE_FLAG) { return CORRECT_READ_KEY_SIGNS_SERVICE_LINE_FLAG; }

    std::vector<std::string> features_list;
    bool FEATURE_EXISTANCE_FLAG = DataBaseFeatureHandler::independentGetVecOfFeatures(key_signs_service_line, ";", features_list);
    if (!FEATURE_EXISTANCE_FLAG) { return FEATURE_EXISTANCE_FLAG; }

    bool KEY_FIELD_EXISTANCE_FLAG = (std::find(features_list.begin(), features_list.end(), "1") != features_list.end());
    if (!KEY_FIELD_EXISTANCE_FLAG)
    {
        std::cout << "THERE IS NO KEY FIELD IN DATABASE. ABORTING CREATING PROCESS" << std::endl;
        bool SUCCESS_ABORTING_FLAG = FileHandler::deleteFile(data_base_file_name);
        if(!SUCCESS_ABORTING_FLAG) { std::cout << "CRITICAL ERROR. FAILED TO DELETE INVALIDLY CREATED DATABASE" << std::endl; }

        return false;
    }

    return KEY_FIELD_EXISTANCE_FLAG;
}

bool CleanDBHandler::saveDataBase(std::ifstream& data_base_file_read_stream)
{
    return FileHandler::saveFile(data_base_file_read_stream);
}

bool CleanDBHandler::saveDataBase(const std::string& data_base_file_path, std::ofstream& data_base_file_write_stream)
{
    return FileHandler::saveFile(data_base_file_path, data_base_file_write_stream);
}

///DATA_BASE_HANDLER_PROTOTYPE_FUNCTIONALITY NAMESPACE FUNCTIONALITY

bool CleanDBHandler::retrievingRecordsFromLine(std::vector<std::string>& record_list, std::string& data_base_file_name, unsigned int line_number)
{
    std::string line;
    bool CORRECT_READ_LINE_FLAG = FileEditor::copyLineV2(line_number, data_base_file_name, line);
    if (!CORRECT_READ_LINE_FLAG) { return CORRECT_READ_LINE_FLAG; }

    bool RECORD_EXISTANCE_FLAG = DataBaseFeatureHandler::independentGetVecOfFeatures(line, ";", record_list);
    return RECORD_EXISTANCE_FLAG;
}

bool CleanDBHandler::creatingSearchFeaturesOrderVector(std::vector<unsigned int>& search_features_order_indexes_list, std::vector<std::string>& key_features_list,
                                           std::vector<std::string>& non_key_features_list, std::vector<std::string>& features_list)
{
    bool user_answer;
    for (auto iter = key_features_list.begin(); iter != key_features_list.end(); /*iter++*/)
    {
        user_answer = CustomIO::safeInputBool("Do you want to search by '" + (*iter) + "' key");
        if (!user_answer) { key_features_list.erase(iter); }
        else
        {
            unsigned int current_search_features_order_index = std::find(features_list.begin(), features_list.end(), (*iter)) - features_list.begin();
            search_features_order_indexes_list.push_back(current_search_features_order_index);
            iter++;
        }
    }

    for (auto iter = non_key_features_list.begin(); iter != non_key_features_list.end(); /*iter++*/)
    {
        user_answer = CustomIO::safeInputBool("Do you want to search by '" + (*iter) + "' key");
        if (!user_answer) { non_key_features_list.erase(iter); }
        else
        {
            unsigned int current_search_features_order_index = std::find(features_list.begin(), features_list.end(), (*iter)) - features_list.begin();
            search_features_order_indexes_list.push_back(current_search_features_order_index);
            iter++;
        }
    }

    if (key_features_list.empty() && non_key_features_list.empty()) { std::cout << "No feature has been choosen. Returning empty result list" << std::endl; return false; }
    std::sort(search_features_order_indexes_list.begin(), search_features_order_indexes_list.end());

    return true;
}

void CleanDBHandler::gettingSearchingValuesForSearchingFeatures(std::vector<std::string>& search_features_values_list,
                                                                                       std::vector<unsigned int>& search_features_order_indexes_list, std::vector<std::string>& features_list)
{
    std::string answer;
    for (auto iter = search_features_order_indexes_list.begin(); iter != search_features_order_indexes_list.end(); iter++)
    {
        answer = CustomIO::safeInputString("Input searching value for '" + features_list[(*iter)] + "' feature");
        search_features_values_list.push_back(answer);
    }
}

void CleanDBHandler::searchingForFeaturesValues(std::vector<int>& founded_record_list, std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                                                       std::string& data_base_file_name)
{
    std::vector<std::string> current_object_feature_vector;
    std::vector<std::string> searched_values_current_object_feature;
    std::string object;
    unsigned int line_index = int(CleanDBHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE) + 1;

    while(FileEditor::copyLineV2(line_index, data_base_file_name, object))
    {
        //ERASEING NON SEARCHABLE FEATURES VALUES
        DataBaseFeatureHandler::independentGetVecOfFeatures(object, ";", current_object_feature_vector);
        for (unsigned int correction = 0; correction < search_features_order_indexes_list.size(); correction++)
        {
            searched_values_current_object_feature.push_back(current_object_feature_vector[search_features_order_indexes_list[correction]]);
        }

        /*for (auto iter = searched_values_current_object_feature.begin(); iter < searched_values_current_object_feature.end(); iter++)
        {
            std::cout << (*iter) << std::endl;
        }
        for (auto iter = search_features_values_list.begin(); iter < search_features_values_list.end(); iter++)
        {
            std::cout << (*iter) << std::endl;
        }*/

        if (searched_values_current_object_feature.size() != search_features_values_list.size()) { std::cout << "ALARM. FILTERING NOT WORKING WELL" << std::endl; return; }

        //ADDING MATCHING LINE INDEX
        if(searched_values_current_object_feature == search_features_values_list) { founded_record_list.push_back(line_index); }

        searched_values_current_object_feature.clear();
        current_object_feature_vector.clear();
        line_index++;
    }
}

bool CleanDBHandler::dividingKeyNonkeyFeatures(std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                                                      std::string& data_base_file_name)
{
    //RETRIEVING FEATURES LIST
    /*std::string name_service_line;
    bool CORRECT_READ_NAME_SERVICE_LINE_FLAG = FileEditor::copyLineV2(CleanDBHandler::ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, name_service_line);
    if (!CORRECT_READ_NAME_SERVICE_LINE_FLAG) { return CORRECT_READ_NAME_SERVICE_LINE_FLAG; }

    std::vector<std::string> features_list;
    bool FEATURE_EXISTANCE_FLAG = DataBaseFeatureHandler::independentGetVecOfFeatures(name_service_line, ";", features_list);
    if (!FEATURE_EXISTANCE_FLAG) { return FEATURE_EXISTANCE_FLAG; }*/
    std::vector<std::string> features_list;
    bool SUCCESS_RETRIEVING_FEATURES_NAME_LIST = CleanDBHandler::retrievingRecordsFromLine(features_list, data_base_file_name,
                                                                                                                  CleanDBHandler::ServiceLines::DATABASE_FIELDS_LINE);
    if (!SUCCESS_RETRIEVING_FEATURES_NAME_LIST) { return SUCCESS_RETRIEVING_FEATURES_NAME_LIST; }

    //RETRIEVING KEY LIST
    /*std::string key_signs_service_line;
    bool CORRECT_READ_KEY_SIGNS_SERVICE_LINE_FLAG = FileEditor::copyLineV2(CleanDBHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE, data_base_file_name, key_signs_service_line);
    if (!CORRECT_READ_KEY_SIGNS_SERVICE_LINE_FLAG) { return CORRECT_READ_KEY_SIGNS_SERVICE_LINE_FLAG; }

    std::vector<std::string> key_signs_feature_list;
    bool KEY_EXISTANCE_FLAG = DataBaseFeatureHandler::independentGetVecOfFeatures(key_signs_service_line, ";", key_signs_feature_list);
    if (!KEY_EXISTANCE_FLAG) { return KEY_EXISTANCE_FLAG; }*/
    std::vector<std::string> key_signs_feature_list;
    bool SUCCESS_RETRIEVING_KEY_SIGNS_LIST = CleanDBHandler::retrievingRecordsFromLine(key_signs_feature_list, data_base_file_name,
                                                                                                                  CleanDBHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE);
    if (!SUCCESS_RETRIEVING_KEY_SIGNS_LIST) { return SUCCESS_RETRIEVING_KEY_SIGNS_LIST; }

    //DEVIDING FEATURE BETWEEN KEY AND NON KEY
    unsigned int number_of_features = (features_list.size() != key_signs_feature_list.size()) ? 0 : features_list.size();
    for (unsigned int feature_index = 0; feature_index < number_of_features; feature_index++)
    {
        if (key_signs_feature_list[feature_index] == "1") { key_features_list.push_back(features_list[feature_index]); }
        else { non_key_features_list.push_back(features_list[feature_index]); }
    }

    return true;
}

std::vector<int> CleanDBHandler::searchObjectsDataBaseV2()
{
    std::vector<int> result;

    std::ifstream database_read_stream;
    std::string data_base_file_name;

    bool OPENING_FILE_FLAG = CleanDBHandler::openingReadDataBaseFileNameAcknowledge(database_read_stream, data_base_file_name);
    if (!OPENING_FILE_FLAG) { return result; }

    std::vector<std::string> key_features_list;
    std::vector<std::string> non_key_features_list;

    bool SUCCESS_DIVIDING_FLAG = CleanDBHandler::dividingKeyNonkeyFeatures(key_features_list, non_key_features_list, data_base_file_name);
    if (!SUCCESS_DIVIDING_FLAG) { return result; }

    std::vector<std::string> features_list;
    bool SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG = CleanDBHandler::retrievingRecordsFromLine(features_list, data_base_file_name,
                                                                                                                  CleanDBHandler::ServiceLines::DATABASE_FIELDS_LINE);
    if (!SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG) { return result; }

    std::vector<unsigned int> search_features_order_indexes_list;
    bool SUCCESS_CREATING_SEARCH_FEATURE_ORDER_VECTOR_FLAG = CleanDBHandler::creatingSearchFeaturesOrderVector(search_features_order_indexes_list, key_features_list,
                                                                             non_key_features_list, features_list);
    if (!SUCCESS_CREATING_SEARCH_FEATURE_ORDER_VECTOR_FLAG) { return result; }

    std::vector<std::string> search_features_values_list;
    CleanDBHandler::gettingSearchingValuesForSearchingFeatures(search_features_values_list, search_features_order_indexes_list, features_list);
    CleanDBHandler::searchingForFeaturesValues(result, search_features_values_list, search_features_order_indexes_list, data_base_file_name);

    return result;
}
//All dependencies of DataBaseHandlerPrototypeFunctionality::searchObjectsDataBaseV2 2
bool CleanDBHandler::searchObjectsDataBaseV2Acknowledge(std::vector<int>& founded_record_index_list, std::ifstream& database_read_stream, std::string& data_base_file_name,
                                                                               std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                                                               std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                                                               std::vector<std::string>& features_list)
{
    //std::ifstream database_read_stream;
    //std::string data_base_file_name;

    bool OPENING_FILE_FLAG = CleanDBHandler::openingReadDataBaseFileNameAcknowledge(database_read_stream, data_base_file_name);
    if (!OPENING_FILE_FLAG) { return OPENING_FILE_FLAG; }

    //std::vector<std::string> key_features_list;
    //std::vector<std::string> non_key_features_list;

    bool SUCCESS_DIVIDING_FLAG = CleanDBHandler::dividingKeyNonkeyFeatures(key_features_list, non_key_features_list, data_base_file_name);
    if (!SUCCESS_DIVIDING_FLAG) { return SUCCESS_DIVIDING_FLAG; }

    //std::vector<std::string> features_list;
    bool SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG = CleanDBHandler::retrievingRecordsFromLine(features_list, data_base_file_name,
                                                                                                                  CleanDBHandler::ServiceLines::DATABASE_FIELDS_LINE);
    if (!SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG) { return SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG; }

    //std::vector<unsigned int> search_features_order_indexes_list;
    bool SUCCESS_CREATING_SEARCH_FEATURE_ORDER_VECTOR_FLAG = CleanDBHandler::creatingSearchFeaturesOrderVector(search_features_order_indexes_list, key_features_list,
                                                                             non_key_features_list, features_list);
    if (SUCCESS_CREATING_SEARCH_FEATURE_ORDER_VECTOR_FLAG)
    {
        std::vector<std::string> search_features_values_list;
        CleanDBHandler::gettingSearchingValuesForSearchingFeatures(search_features_values_list, search_features_order_indexes_list, features_list);
        CleanDBHandler::searchingForFeaturesValues(founded_record_index_list, search_features_values_list, search_features_order_indexes_list, data_base_file_name);
    }

    return SUCCESS_CREATING_SEARCH_FEATURE_ORDER_VECTOR_FLAG;
}

bool DataBaseHandler::addObjectDataBaseV2Acknowledge(std::vector<int>& founded_record_index_list, std::ifstream& database_read_stream, std::string& data_base_file_name,
                                            std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                            std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                            std::vector<std::string>& features_list)
{
    //std::ifstream database_read_stream;
    //std::string data_base_file_name;

    bool OPENING_FILE_FLAG = CleanDBHandler::openingReadDataBaseFileNameAcknowledge(database_read_stream, data_base_file_name);
    if (!OPENING_FILE_FLAG) { return OPENING_FILE_FLAG; }

    //std::vector<std::string> key_features_list;
    //std::vector<std::string> non_key_features_list;

    bool SUCCESS_DIVIDING_FLAG = CleanDBHandler::dividingKeyNonkeyFeatures(key_features_list, non_key_features_list, data_base_file_name);
    if (!SUCCESS_DIVIDING_FLAG) { return SUCCESS_DIVIDING_FLAG; }

    //std::vector<std::string> features_list;
    bool SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG = CleanDBHandler::retrievingRecordsFromLine(features_list, data_base_file_name,
                                                                                                                  CleanDBHandler::ServiceLines::DATABASE_FIELDS_LINE);
    if (!SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG) { return SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG; }

    //std::vector<unsigned int> search_features_order_indexes_list;

    //std::vector<std::string> search_features_values_list;
    //FOR ENTER
    for (auto iter = features_list.begin(); iter != features_list.end(); iter++)
    {
        unsigned int current_search_features_order_index = std::find(features_list.begin(), features_list.end(), (*iter)) - features_list.begin();
        search_features_order_indexes_list.push_back(current_search_features_order_index);
    }

    CleanDBHandler::gettingSearchingValuesForSearchingFeatures(search_features_values_list, search_features_order_indexes_list, features_list);

    std::string tmp_adding_line;
    bool SUCCESS_MERGE_FEATURES_TO_OBJECT_FLAG = DataBaseFeatureHandler::mergeVecOfFeaturesToStr(search_features_values_list, ";", tmp_adding_line);
    if (!SUCCESS_MERGE_FEATURES_TO_OBJECT_FLAG) { return SUCCESS_MERGE_FEATURES_TO_OBJECT_FLAG; }

    //FOR CHECK
    search_features_order_indexes_list.clear();
    for (auto iter = key_features_list.begin(); iter != key_features_list.end(); iter++)
    {
        unsigned int current_search_features_order_index = std::find(features_list.begin(), features_list.end(), (*iter)) - features_list.begin();
        search_features_order_indexes_list.push_back(current_search_features_order_index);
    }

    std::vector<std::string> search_key_features_values_list;
    for (auto iter = search_features_order_indexes_list.begin(); iter != search_features_order_indexes_list.end(); iter++)
    {
        //std::cout << "AAAAAAAAAAAAAAAA" << std::endl;
        //std::cout << search_features_values_list[(*iter)] << std::endl;
        search_key_features_values_list.push_back(search_features_values_list[(*iter)]);
    }

    CleanDBHandler::searchingForFeaturesValues(founded_record_index_list, search_key_features_values_list, search_features_order_indexes_list, data_base_file_name);

    bool VALID_ADDING_RECORD_FLAG = founded_record_index_list.empty();
    if (!VALID_ADDING_RECORD_FLAG) { return VALID_ADDING_RECORD_FLAG; }

    /*std::string tmp_adding_line;
    bool SUCCESS_MERGE_FEATURES_TO_OBJECT_FLAG = DataBaseFeatureHandler::mergeVecOfFeaturesToStr(search_features_values_list, ";", tmp_adding_line);
    if (!SUCCESS_MERGE_FEATURES_TO_OBJECT_FLAG) { return SUCCESS_MERGE_FEATURES_TO_OBJECT_FLAG; }*/

    bool SUCCESS_ADDING_RECORD_FLAG = FileEditor::insertLine(CleanDBHandler::ServiceLines::DATABASE_KEY_SIGNS_LINE + 1, data_base_file_name, tmp_adding_line, "");

    return SUCCESS_ADDING_RECORD_FLAG;
}

bool DataBaseHandler::deleteObjectDataBaseV2Acknowledge(std::vector<int>& founded_record_index_list, std::ifstream& database_read_stream, std::string& data_base_file_name,
                                            std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                            std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                            std::vector<std::string>& features_list)
{
    //std::ifstream database_read_stream;
    //std::string data_base_file_name;

    bool OPENING_FILE_FLAG = CleanDBHandler::openingReadDataBaseFileNameAcknowledge(database_read_stream, data_base_file_name);
    if (!OPENING_FILE_FLAG) { return OPENING_FILE_FLAG; }

    //std::vector<std::string> key_features_list;
    //std::vector<std::string> non_key_features_list;

    bool SUCCESS_DIVIDING_FLAG = CleanDBHandler::dividingKeyNonkeyFeatures(key_features_list, non_key_features_list, data_base_file_name);
    if (!SUCCESS_DIVIDING_FLAG) { return SUCCESS_DIVIDING_FLAG; }

    //std::vector<std::string> features_list;
    bool SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG = CleanDBHandler::retrievingRecordsFromLine(features_list, data_base_file_name,
                                                                                                                  CleanDBHandler::ServiceLines::DATABASE_FIELDS_LINE);
    if (!SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG) { return SUCCESS_RETRIEVING_FEATURES_NAME_LIST_FLAG; }

    //std::vector<unsigned int> search_features_order_indexes_list;
    bool SUCCESS_CREATING_SEARCH_FEATURE_ORDER_VECTOR_FLAG = CleanDBHandler::creatingSearchFeaturesOrderVector(search_features_order_indexes_list, key_features_list,
                                                                             non_key_features_list, features_list);
    if (SUCCESS_CREATING_SEARCH_FEATURE_ORDER_VECTOR_FLAG)
    {
        std::vector<std::string> search_features_values_list;
        CleanDBHandler::gettingSearchingValuesForSearchingFeatures(search_features_values_list, search_features_order_indexes_list, features_list);
        CleanDBHandler::searchingForFeaturesValues(founded_record_index_list, search_features_values_list, search_features_order_indexes_list, data_base_file_name);
    }

    int delet_offset = 0;
    bool SUCCESS_DELETING_FLAG;
    for (auto iter = founded_record_index_list.begin(); iter != founded_record_index_list.end(); iter++, delet_offset++)
    {
        SUCCESS_DELETING_FLAG = FileEditor::removeLine(((*iter) - delet_offset), data_base_file_name);
        if (!SUCCESS_DELETING_FLAG) { return SUCCESS_DELETING_FLAG; }
    }

    return SUCCESS_DELETING_FLAG;
}

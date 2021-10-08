#include "testField.h"

std::string prototype_functionality::safeInputString(const std::string& l_invitation)
{
    std::string output = "";

    std::cout << l_invitation << " >> ";
    std::cin >> output;
    rclean(output, ' ');
    lclean(output, ' ');

    return output;
}

void prototype_functionality::rclean(std::string& string_to_clean, const char& character_to_clean)
{
    while(string_to_clean[0] == character_to_clean)
    {
        string_to_clean.erase(0, 1);
    }
}

void prototype_functionality::lclean(std::string& string_to_clean, const char& character_to_clean)
{
    while(string_to_clean[(string_to_clean.size() - 1)] == character_to_clean)
    {
        string_to_clean.erase((string_to_clean.size() - 1), 1);
    }
}

bool prototype_functionality::safeInputBool(const std::string& l_invitation)
{
    std::string output = safeInputString(l_invitation);
    rclean(output, ' ');
    lclean(output, ' ');
    while (!((output == "1") || (output == "0")))
    {
        std::cout << "Input error. Please try again (press 1 or 0)!!!" << std::endl;
        output = safeInputString(l_invitation);
        rclean(output, ' ');
        lclean(output, ' ');
    }

    return (output=="1");
}

bool prototype_functionality::createDataBase()
{
    std::string data_base_file_name = safeInputString("Input DataBase name");
    data_base_file_name += ".txt";
    bool CREATING_FILE_FLAG = FileHandler::createFile(data_base_file_name);

    //NOT SUCCESSFUL ACCESS TO FILE
    if (!CREATING_FILE_FLAG) { return CREATING_FILE_FLAG; }

    //NOT SUCCESSFUL WRITING TO FILI NAME LINE
    bool WRITING_NAME_FILE_FLAG = FileEditor::changeLine(0, data_base_file_name, data_base_file_name, "");
    if (!WRITING_NAME_FILE_FLAG) { return WRITING_NAME_FILE_FLAG; }

    //NOT SUCCESSFUL WRITING TO FIELD NAME & KEY SIGNS LINES
    bool WRITING_FIELD_WITH_KEY_SIGN;
    for (int i = 0; i < 3; i++)
    {
        WRITING_FIELD_WITH_KEY_SIGN = addFieldToDataBase(data_base_file_name);
        if (!WRITING_FIELD_WITH_KEY_SIGN) { return WRITING_FIELD_WITH_KEY_SIGN; /*continue;*/ }

        //if(findString(FileEditor::copyLineV2(data_base_file_name)))
    }

    //CHECK FOR EXISTANCE AT LEAST ONE KEY FLAG
    /*bool KEY_LINE_VALIDITY_FLAG = checkDataBaseKeyLineValidity(data_base_file_name);
    if (!KEY_LINE_VALIDITY_FLAG)
    {
        FileHandler::deleteFile(data_base_file_name);
        return KEY_LINE_VALIDITY_FLAG;
    }*/

    return WRITING_FIELD_WITH_KEY_SIGN;
}

bool prototype_functionality::addFieldToDataBase(const std::string& data_base_file_name)
{
    //TRYONG TO ADD FIELD NAME IN SERVICE NAMES LINE
    std::string field_name = safeInputString("Input field name");
    bool NAME_ADDING_FLAG = FileEditor::addToLine(ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name,
                                                  field_name, ";");
    if (!NAME_ADDING_FLAG)
    {
        FileEditor::addToLine(ServiceLines::DATABASE_NAME_LINE, data_base_file_name, "", "\n");
        NAME_ADDING_FLAG = FileEditor::addToLine(ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, field_name, ";");
    }
    if (!NAME_ADDING_FLAG) { return false; }

    //TRYONG TO ADD FIELD KEY SIGN IN SERVICE KEY SIGNS LINE
    std::string key_sign = (safeInputBool("Input key sign (1 - key field / 0 - not key field)") ? "1" : "0");
    bool KEY_ADDING_FLAG = FileEditor::addToLine(ServiceLines::DATABASE_KEY_SIGNS_LINE, data_base_file_name, key_sign, ";");
    if (!KEY_ADDING_FLAG)
    {
        FileEditor::addToLine(ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, "", "\n");
        KEY_ADDING_FLAG = FileEditor::addToLine(ServiceLines::DATABASE_KEY_SIGNS_LINE, data_base_file_name, key_sign, ";");
    }

    return KEY_ADDING_FLAG;
}

std::vector<int> prototype_functionality::findString(const std::string& stringIn, const std::string& stringFor)
{
    std::vector<int> result;
    for(int line_index = 0; line_index != -1; line_index++)
    {
        if(stringIn.find(stringFor, line_index) != std::string::npos) { result.push_back(line_index); }
    }
    return result;
}

bool prototype_functionality::newFieldAddCheck(const std::string& data_base_file_name, const std::string& l_add_condidate)
{
    bool is_valid = false;

    //std::ifstream tmp_names;
    //FileHandler::openReadFile(data_base_file_name, tmp_names);
    //tools::goToLine(ServiceLines::DATABASE_NAME_LINE, tmp_names);
    std::string names;
    //std::getline(tmp_names, names);
    FileEditor::copyLineV2(ServiceLines::DATABASE_FIELDS_LINE, data_base_file_name, names);

    std::string::size_type start_string_pos = names.find(l_add_condidate);
    if (start_string_pos != std::string::npos)
    {
        std::string::size_type nearest_next_delimeter_pos = names.find(";");
        if ((int(start_string_pos) + int(l_add_condidate.length())) < int(nearest_next_delimeter_pos)) { is_valid = true; }
    }

    return is_valid;
}

bool prototype_functionality::checkDataBaseKeyLineValidity(const std::string& data_base_file_name)
{
    /*std::ifstream database_read_file;
    bool CREATING_FILE_FLAG = FileHandler::openReadFile(data_base_file_name, database_read_file);
    if (!CREATING_FILE_FLAG) { return CREATING_FILE_FLAG; }*/

    std::string database_key_sign_string;
    bool SUCCESS_ACCESS_TO_KEY_LINE_FLAG = FileEditor::copyLineV2(ServiceLines::DATABASE_KEY_SIGNS_LINE,
                                                                  data_base_file_name, database_key_sign_string);
    if (!SUCCESS_ACCESS_TO_KEY_LINE_FLAG) { return SUCCESS_ACCESS_TO_KEY_LINE_FLAG; }

    //bool SUCCESS_CLOSE_FILE = FileHandler::closeFile(database_read_file);
    bool VALIDITY_KEY_LINE_FLAG = ((findString(database_key_sign_string, "1")).empty() > 0);

    return /*(SUCCESS_CLOSE_FILE &&*/ VALIDITY_KEY_LINE_FLAG/*)*/;
}

std::vector<int> DBcreateNS::getPosOfOccurencies(const std::string& object, const std::string& feature_delimiter)
{
    std::vector<int> result;

    std::size_t search_index = object.find(feature_delimiter);
    while (search_index != std::string::npos)
    {
        result.push_back(int(search_index));
        search_index = object.find(feature_delimiter, search_index + feature_delimiter.size());
    }

    return result;
}

std::vector<std::string> DBcreateNS::getVecOfFeatures(const std::string& object, const std::vector<int>& delimiter_indexes)
{
    std::vector<std::string> features;

    std::string tmp_feature = "";
    for (int i = 0; i < int(delimiter_indexes.size()); i++)
    {
        NiceIdeas::getFeature(i, object, delimiter_indexes, tmp_feature);
        features.push_back(tmp_feature);
    }

    return features;
}

bool NiceIdeas::getFeature(unsigned int feature_num, const std::string& object, const std::vector<int>& delimiter_indexes, std::string& feature)
{
    if (int(feature_num) > int(delimiter_indexes.size())) { return false; }

    int start = (feature_num == 0) ? feature_num - 1 : delimiter_indexes[feature_num - 1];
    feature = object.substr(start + 1, delimiter_indexes[feature_num] - start - 1);

    return true;
}


bool NiceIdeas::DBsearchV1()
{
    std::string filename;
    std::string data_base_file_name = prototype_functionality::safeInputString("Input DataBase name");
    data_base_file_name += ".txt";
    bool CREATING_FILE_FLAG = FileHandler::createFile(data_base_file_name);

    //NOT SUCCESSFUL ACCESS TO FILE
    if (!CREATING_FILE_FLAG) { return CREATING_FILE_FLAG; }

    return true;
}














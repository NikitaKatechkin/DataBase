#ifndef TESTFIELD_H_INCLUDED
#define TESTFIELD_H_INCLUDED

#include "FileEditor.h"

namespace prototype_functionality
{
    enum ServiceLines
    {
        DATABASE_NAME_LINE = 0,
        DATABASE_FIELDS_LINE,
        DATABASE_KEY_SIGNS_LINE
    };

    std::string safeInputString(const std::string& l_invitation);

    void rclean(std::string& string_to_clean, const char& character_to_clean);
    void lclean(std::string& string_to_clean, const char& character_to_clean);

    bool safeInputBool(const std::string& l_invitation);

    bool createDataBase();

    bool addFieldToDataBase(const std::string& data_base_file_name);

    bool checkDataBaseKeyLineValidity(const std::string& data_base_file_name);

    std::vector<int> findString(const std::string& stringIn, const std::string& stringFor);

    bool newFieldAddCheck(const std::string& data_base_file_name, const std::string& l_add_condidate);
}

namespace DBcreateNS
{
    std::vector<int> getPosOfOccurencies(const std::string& object, const std::string& feature_delimiter);
    std::vector<std::string> getVecOfFeatures(const std::string& object, const std::vector<int>& delimiter_indexes);
}

namespace NiceIdeas
{
    bool getFeature(unsigned int feature_num, const std::string& object, const std::vector<int>& delimiter_indexes, std::string& feature);

    bool DBsearchV1();
}

#endif // TESTFIELD_H_INCLUDED

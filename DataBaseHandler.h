#ifndef DATABASEHANDLER_H_INCLUDED
#define DATABASEHANDLER_H_INCLUDED

#include <algorithm>
#include <sstream>

#include "DataBaseFeatureHandler.h"
#include "CustomIO.h"

/*namespace DataBaseHandler
{
    enum ServiceLines
    {
        DATABASE_NAME_LINE = 0,
        DATABASE_FIELDS_LINE,
        DATABASE_KEY_SIGNS_LINE
    };

    void rclean(std::string& string_to_clean, const char& character_to_clean);
    void lclean(std::string& string_to_clean, const char& character_to_clean);
    std::string safeInputString(const std::string& l_invitation);

    bool safeInputBool(const std::string& l_invitation);

    bool addFieldToDataBase(const std::string& data_base_file_name);

    bool createDataBase();
    bool deletingDataBase();

    bool openingReadDataBase(std::ifstream& l_database_read_file_stream);
    bool openRewriteDataBase(std::ofstream& l_database_write_file_stream);
    bool openWriteFileDataBase(std::ofstream& l_database_write_file_stream);

    bool openingReadDataBaseFileNameAcknowledge(std::ifstream& l_database_read_file_stream, std::string& result_file_name);
    bool openRewriteDataBaseFileNameAcknowledge(std::ofstream& l_database_write_file_stream, std::string& result_file_name);
    bool openWriteFileDataBaseFileNameAcknowledge(std::ofstream& l_database_write_file_stream, std::string& result_file_name);

    bool saveDataBase(std::ifstream& l_database_file_read_stream);
    bool saveDataBase(const std::string& l_database_file_path, std::ofstream& l_database_file_write_stream);

    bool clearDataBase();
}

namespace DataBaseHandlerPrototypeFunctionality
{
    bool retrievingRecordsFromLine(std::vector<std::string>& record_list, std::string& data_base_file_name, unsigned int line_number);
    bool dividingKeyNonkeyFeatures(std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list, std::string& data_base_file_name);
    bool creatingSearchFeaturesOrderVector(std::vector<unsigned int>& search_features_order_indexes_list, std::vector<std::string>& key_features_list,
                                           std::vector<std::string>& non_key_features_list, std::vector<std::string>& features_list);
    void gettingSearchingValuesForSearchingFeatures(std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                                    std::vector<std::string>& features_list);
    void searchingForFeaturesValues(std::vector<int>& founded_record_list, std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                    std::string& data_base_file_name);
    std::vector<int> searchObjectsDataBaseV2();
    bool searchObjectsDataBaseV2Acknowledge(std::vector<int>& founded_record_index_list, std::ifstream& database_read_stream, std::string& data_base_file_name,
                                            std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                            std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                            std::vector<std::string>& features_list);

    std::vector<int> searchObjectsDataBase();
}*/

namespace CleanDBHandler
{
    ///
    ///START OF PORTING DATA_BASE_HANDLER NAMESPACE FUNCTIONALITY
    ///

    enum ServiceLines
    {
        DATABASE_NAME_LINE = 0,
        DATABASE_FIELDS_LINE,
        DATABASE_KEY_SIGNS_LINE
    };

    //SERVICE FUNCTIONS FOR FILE HANDLER API PART WRAPPER
    bool isStringDataBaseFileName(const std::string& file_name, const std::string& extension);

    //FILE HANDLER API PART WRAPPER
    bool openingReadDataBaseFileNameAcknowledge(std::ifstream& data_base_read_file_stream, std::string& result_file_name);
    bool openRewriteDataBaseFileNameAcknowledge(std::ofstream& data_base_write_file_stream, std::string& result_file_name);
    bool openWriteFileDataBaseFileNameAcknowledge(std::ofstream& data_base_write_file_stream, std::string& result_file_name);

    //SERVICE FUNCTIONS FOR CREAT_DATA_BASE FUNCTION
    bool addFieldToDataBase(const std::string& data_base_file_name);

    //CREAT_DATA_BASE PART
    bool createDataBase(std::string& data_base_file_name);

    //DELETING/CLEARING DATA BASE PART
    bool deletingDataBase(std::string& data_base_file_name);
    bool clearDataBase(std::string& data_base_file_name);

    //SAVE FUNCTIONS PART
    bool saveDataBase(std::ifstream& data_base_file_read_stream);
    bool saveDataBase(const std::string& data_base_file_path, std::ofstream& data_base_file_write_stream);

    ///
    ///END OF PORTING DATA_BASE_HANDLER NAMESPACE FUNCTIONALITY
    ///

    ///
    ///START OF PORTING SEARCH NAMESPACE FUNCTIONALITY
    ///

    //INDEPENDENT PART OF SERVICE FUNCTIONS FOR ALL VERSIONS OF SEARCH FUNCTIONALITY
    bool creatingSearchFeaturesOrderVector(std::vector<unsigned int>& search_features_order_indexes_list, std::vector<std::string>& key_features_list,
                                           std::vector<std::string>& non_key_features_list, std::vector<std::string>& features_list);
    void gettingSearchingValuesForSearchingFeatures(std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                                    std::vector<std::string>& features_list);
    void searchingForFeaturesValues(std::vector<int>& founded_record_list, std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                    std::string& data_base_file_name);
    bool retrievingRecordsFromLine(std::vector<std::string>& record_list, std::string& data_base_file_name, unsigned int line_number);

    //DEPENDENT PART OF SERVICE FUNCTIONS FOR ALL VERSIONS OF SEARCH FUNCTIONALITY

    ///FUNCTIONS DEPEND ON RETRIEVING_RECORDS_FROM_LINE FUNCTION
    bool dividingKeyNonkeyFeatures(std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list, std::string& data_base_file_name);

    //VERSIONS OF SEARCH FUNCTIONALITY
    std::vector<int> searchObjectsDataBaseV2();
    bool searchObjectsDataBaseV2Acknowledge(std::vector<int>& founded_record_index_list, std::ifstream& database_read_stream, std::string& data_base_file_name,
                                            std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                            std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                            std::vector<std::string>& features_list);

    //INDEPENDENT VERSION OF SEARCH FUNCTIONALITY
    std::vector<int> searchObjectsDataBase();

    ///
    ///END OF PORTING SEARCH NAMESPACE FUNCTIONALITY
    ///
}

namespace DataBaseHandler
{
    bool addObjectDataBaseV2Acknowledge(std::vector<int>& founded_record_index_list, std::ifstream& database_read_stream, std::string& data_base_file_name,
                                            std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                            std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                            std::vector<std::string>& features_list);
    bool deleteObjectDataBaseV2Acknowledge(std::vector<int>& founded_record_index_list, std::ifstream& database_read_stream, std::string& data_base_file_name,
                                            std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                            std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                            std::vector<std::string>& features_list);

    enum ServiceLines
    {
        DATABASE_NAME_LINE = 0,
        DATABASE_FIELDS_LINE,
        DATABASE_KEY_SIGNS_LINE
    };

    bool isStringDataBaseFileName(const std::string& file_name, const std::string& extension);

    bool getFeaturesFromRecord(std::string& data_base_file_name, unsigned int line_number, std::vector<std::string>& features_list);

    void getCandidatesIndexesList(std::vector<std::string>& features_list, std::vector<unsigned int>& candidates_indexes_list, const std::string& candidate_approval_question);

    bool comparePairOfFeaturesList(std::vector<std::string>& first_features_list, std::vector<std::string>& second_features_list);

    bool searchRecordsDataBase(std::string& data_base_file_name, std::vector<unsigned int>& found_records_indexes);

    bool getMaskedFeatureList(std::vector<std::string>& features_list, std::vector<std::string>& mask, const std::string& key_sign, std::vector<unsigned int>& masked_features_indexes_list);

    bool addRecordsDataBase(std::string& data_base_file_name);

    bool deleteRecordsDataBase(std::string& data_base_file_name);

    bool editRecordsDataBase(std::string& data_base_file_name);
}


#endif // DATABASEHANDLER_H_INCLUDED

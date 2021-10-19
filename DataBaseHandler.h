#ifndef DATABASEHANDLER_H_INCLUDED
#define DATABASEHANDLER_H_INCLUDED

#include <algorithm>
#include <sstream>

#include "DataBaseFeatureHandler.h"
#include "CustomIO.h"

namespace DataBaseHandler
{
    enum ServiceLines
    {
        DATABASE_NAME_LINE = 0,
        DATABASE_FIELDS_LINE,
        DATABASE_KEY_SIGNS_LINE
    };

    ///START FILE HANDLER API WRAPPER PART
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
    ///END FILE HANDLER API WRAPPER PART

    ///START DATABASE HANDLER PART
    //SERVICE FUNCTIONALITY PART OF DATABASE HANDLER
    bool getFeaturesFromRecord(std::string& data_base_file_name, unsigned int line_number, std::vector<std::string>& features_list);

    void getCandidatesIndexesList(std::vector<std::string>& features_list, std::vector<unsigned int>& candidates_indexes_list, const std::string& candidate_approval_question);

    bool comparePairOfFeaturesList(std::vector<std::string>& first_features_list, std::vector<std::string>& second_features_list);

    bool getMaskedFeatureList(std::vector<std::string>& features_list, std::vector<std::string>& mask, const std::string& key_sign, std::vector<unsigned int>& masked_features_indexes_list);

    //MAIN FUNCTIONALITY PART OF DATABASE HANDLER
    bool searchRecordsDataBase(std::string& data_base_file_name, std::vector<unsigned int>& found_records_indexes);

    bool addRecordsDataBase(std::string& data_base_file_name);

    bool deleteRecordsDataBase(std::string& data_base_file_name);

    bool editRecordsDataBase(std::string& data_base_file_name);
    ///END DATABASE HANDLER PART

    ///START LEGACY PART
    //INDEPENDENT PART OF SERVICE FUNCTIONS FOR ALL VERSIONS OF SEARCH FUNCTIONALITY
    bool creatingSearchFeaturesOrderVector(std::vector<unsigned int>& search_features_order_indexes_list, std::vector<std::string>& key_features_list,
                                           std::vector<std::string>& non_key_features_list, std::vector<std::string>& features_list);
    void gettingSearchingValuesForSearchingFeatures(std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                                    std::vector<std::string>& features_list);
    void searchingForFeaturesValues(std::vector<int>& founded_record_list, std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                    std::string& data_base_file_name);
    bool retrievingRecordsFromLine(std::vector<std::string>& record_list, std::string& data_base_file_name, unsigned int line_number);

    //DEPENDENT PART OF SERVICE FUNCTIONS FOR ALL VERSIONS OF SEARCH FUNCTIONALITY
    //FUNCTIONS DEPEND ON RETRIEVING_RECORDS_FROM_LINE FUNCTION
    bool dividingKeyNonkeyFeatures(std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list, std::string& data_base_file_name);

    //MAIN FUNCTIONALITY OF LEGACY PART
    bool addObjectDataBaseV2Acknowledge(std::vector<int>& founded_record_index_list, std::ifstream& database_read_stream, std::string& data_base_file_name,
                                            std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                            std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                            std::vector<std::string>& features_list);
    bool deleteObjectDataBaseV2Acknowledge(std::vector<int>& founded_record_index_list, std::ifstream& database_read_stream, std::string& data_base_file_name,
                                            std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                            std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                            std::vector<std::string>& features_list);
    bool searchObjectsDataBaseV2Acknowledge(std::vector<int>& founded_record_index_list, std::ifstream& database_read_stream, std::string& data_base_file_name,
                                            std::vector<std::string>& key_features_list, std::vector<std::string>& non_key_features_list,
                                            std::vector<std::string>& search_features_values_list, std::vector<unsigned int>& search_features_order_indexes_list,
                                            std::vector<std::string>& features_list);
    ///END LEGACY PART
}

#endif // DATABASEHANDLER_H_INCLUDED

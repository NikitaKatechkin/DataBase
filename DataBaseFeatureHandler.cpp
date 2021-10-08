#include "DataBaseFeatureHandler.h"

bool DataBaseFeatureHandler::getPosOfOccurencies(const std::string& object, const std::string& feature_delimiter,
                                                 std::vector<int>& occurencies_index_vector)
{
    std::size_t search_index = object.find(feature_delimiter);
    while (search_index != std::string::npos)
    {
        occurencies_index_vector.push_back(int(search_index));
        search_index = object.find(feature_delimiter, search_index + feature_delimiter.size());
    }

    return true/*!(occurencies_index_vector.empty())*/;
}

bool DataBaseFeatureHandler::getFeature(unsigned int feature_num, const std::string& object,
                                        const std::vector<int>& delimiter_indexes, std::string& feature)
{
    bool CORRECT_FEATURE_INDEX_FLAG = (int(feature_num) < int(delimiter_indexes.size()));
    if (!CORRECT_FEATURE_INDEX_FLAG) { return CORRECT_FEATURE_INDEX_FLAG; }

    int start = (feature_num == 0) ? feature_num - 1 : delimiter_indexes[feature_num - 1];
    feature = object.substr(start + 1, delimiter_indexes[feature_num] - start - 1);

    return CORRECT_FEATURE_INDEX_FLAG;
}

bool DataBaseFeatureHandler::getVecOfFeatures(const std::string& object, const std::vector<int>& delimiter_indexes,
                                              std::vector<std::string>& features_vector)
{
    bool EXISTANCE_OF_FEATURE_FLAG = !(delimiter_indexes.empty());

    if (!EXISTANCE_OF_FEATURE_FLAG) { return EXISTANCE_OF_FEATURE_FLAG; }

    std::string tmp_feature = "";
    bool SUCCESS_GET_FEATURE_FLAG = true;
    for (int i = 0; i < int(delimiter_indexes.size()); i++)
    {
        SUCCESS_GET_FEATURE_FLAG = DataBaseFeatureHandler::getFeature(i, object, delimiter_indexes, tmp_feature);
        if (!SUCCESS_GET_FEATURE_FLAG) { break; }
        features_vector.push_back(tmp_feature);
    }

    if(!SUCCESS_GET_FEATURE_FLAG) { return SUCCESS_GET_FEATURE_FLAG; }

    return !(features_vector.empty());
}

bool DataBaseFeatureHandler::independentGetFeature(unsigned int feature_num, const std::string& object,
                                          const std::string& feature_delimiter, std::string& feature)
{
    std::vector<int> delimiter_indexes;
    bool SUCCESS_DELIMITER_EXTRACTION_FLAG = getPosOfOccurencies(object, feature_delimiter, delimiter_indexes);
    if (!SUCCESS_DELIMITER_EXTRACTION_FLAG) { return SUCCESS_DELIMITER_EXTRACTION_FLAG; }

    bool CORRECT_FEATURE_INDEX_FLAG = (int(feature_num) < int(delimiter_indexes.size()));
    if (!CORRECT_FEATURE_INDEX_FLAG) { return CORRECT_FEATURE_INDEX_FLAG; }

    int start = (feature_num == 0) ? feature_num - 1 : delimiter_indexes[feature_num - 1];
    feature = object.substr(start + 1, delimiter_indexes[feature_num] - start - 1);

    return CORRECT_FEATURE_INDEX_FLAG;
}

bool DataBaseFeatureHandler::independentGetVecOfFeatures(const std::string& object, const std::string& feature_delimiter,
                                                         std::vector<std::string>& features_vector)
{
    std::vector<int> delimiter_indexes;
    bool SUCCESS_DELIMITER_EXTRACTION_FLAG = getPosOfOccurencies(object, feature_delimiter, delimiter_indexes);
    if (!SUCCESS_DELIMITER_EXTRACTION_FLAG) { return SUCCESS_DELIMITER_EXTRACTION_FLAG; }

    std::string tmp_feature = "";
    bool SUCCESS_GET_FEATURE_FLAG = true;
    for (int i = 0; i < int(delimiter_indexes.size()); i++)
    {
        SUCCESS_GET_FEATURE_FLAG = DataBaseFeatureHandler::getFeature(i, object, delimiter_indexes, tmp_feature);
        if (!SUCCESS_GET_FEATURE_FLAG) { break; }
        features_vector.push_back(tmp_feature);
    }

    if(!SUCCESS_GET_FEATURE_FLAG) { return SUCCESS_GET_FEATURE_FLAG; }

    return !(features_vector.empty());
}

bool DataBaseFeatureHandler::mergeVecOfFeaturesToStr(std::vector<std::string>& features_vector,
                                                            const std::string& feature_delimiter, std::string& object)
{
    if (!features_vector.empty())
    {
        object = "";
        for (auto iter = features_vector.begin(); iter != features_vector.end(); iter++)
        {
            object += ((*iter) + feature_delimiter);
        }
    }

    return true;
}

bool DataBaseFeatureHandler::insertFeature(std::string& object, const std::string& feature_delimiter,
                                           const std::string& feature, unsigned int insertion_index)
{
    std::vector<std::string> tmp_features;
    independentGetVecOfFeatures(object, feature_delimiter, tmp_features);

    tmp_features.insert(tmp_features.begin() + insertion_index, feature);
    mergeVecOfFeaturesToStr(tmp_features, feature_delimiter, object);

    return true;
}

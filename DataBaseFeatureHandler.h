#ifndef DATABASEFEATUREHANDLER_H_INCLUDED
#define DATABASEFEATUREHANDLER_H_INCLUDED

#include "FileEditor.h"
#include "FileHandler.h"

namespace DataBaseFeatureHandler
{
    bool getPosOfOccurencies(const std::string& object, const std::string& feature_delimiter, std::vector<int>& occurencies_index_vector);

    bool getFeature(unsigned int feature_num, const std::string& object, const std::vector<int>& delimiter_indexes, std::string& feature);
    bool getVecOfFeatures(const std::string& object, const std::vector<int>& delimiter_indexes, std::vector<std::string>& features_vector);

    bool independentGetFeature(unsigned int feature_num, const std::string& object, const std::string& feature_delimiter, std::string& feature);
    bool independentGetVecOfFeatures(const std::string& object, const std::string& feature_delimiter, std::vector<std::string>& features_vector);

    bool mergeVecOfFeaturesToStr(std::vector<std::string>& features_vector,
                                                            const std::string& feature_delimiter, std::string& object);
    bool insertFeature(std::string& object, const std::string& feature_delimiter, const std::string& feature, unsigned int insertion_index);
}


#endif // DATABASEFEATUREHANDLER_H_INCLUDED

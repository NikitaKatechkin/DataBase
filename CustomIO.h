#ifndef CUSTOMIO_H_INCLUDED
#define CUSTOMIO_H_INCLUDED

#include <iostream>
#include <string>

namespace CustomIO
{
    //SERVICE FUCNTIONS FOR SAFE_INPUT_STRING FUNCTIONS
    void rclean(std::string& string_to_clean, const char& character_to_clean);
    void lclean(std::string& string_to_clean, const char& character_to_clean);

    //SAFE_INPUT FUNCTIONS
    std::string safeInputString(const std::string& l_invitation);
    bool safeInputBool(const std::string& l_invitation);
}

#endif // CUSTOMIO_H_INCLUDED

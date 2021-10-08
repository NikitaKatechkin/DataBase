#include "CustomIO.h"

void CustomIO::rclean(std::string& string_to_clean, const char& character_to_clean)
{
    while(string_to_clean[0] == character_to_clean)
    {
        string_to_clean.erase(0, 1);
    }
}

void CustomIO::lclean(std::string& string_to_clean, const char& character_to_clean)
{
    while(string_to_clean[(string_to_clean.size() - 1)] == character_to_clean)
    {
        string_to_clean.erase((string_to_clean.size() - 1), 1);
    }
}

std::string CustomIO::safeInputString(const std::string& l_invitation)
{
    std::string output = "";

    std::cout << l_invitation << " >> ";
    std::cin >> output;
    CustomIO::rclean(output, ' ');
    CustomIO::lclean(output, ' ');

    return output;
}

bool CustomIO::safeInputBool(const std::string& l_invitation)
{
    std::string output = CustomIO::safeInputString(l_invitation);
    while (!((output == "1") || (output == "0")))
    {
        std::cout << "Input error. Please try again (press 1 or 0)!!!" << std::endl;
        output = CustomIO::safeInputString(l_invitation);
    }

    return (output=="1");
}

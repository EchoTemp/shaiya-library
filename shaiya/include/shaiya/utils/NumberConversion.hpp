#pragma once
#include <string>

namespace shaiya
{
    /**
     * Performs a checked string-to-integer conversion.
     * @param str       The input string.
     * @param number    The converted integer.
     * @return          If the conversion was successful.
     */
    bool stoi(const std::string& str, int& number)
    {
        try
        {
            number = std::stoi(str);
            return true;
        }
        catch (const std::exception& e)
        {
            return false;
        }
    }
}
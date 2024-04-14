/**
 * @file trimBegin.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <string>
#include <vector>

namespace parseop {
    std::string trimBegin(const std::string &input, const std::vector<char> &charsToTrim) {
        if (input.empty())
            return input;
        std::size_t firstValidPos = input.find_first_not_of(
            std::string{charsToTrim.begin(), charsToTrim.end()}.c_str()
        );
        if (firstValidPos == std::string::npos)
            return "";
        return input.substr(firstValidPos);
    }

    std::string trimBegin(const std::string &input, const std::string &charsToTrim) {
        return trimBegin(input, std::vector<char>(charsToTrim.begin(), charsToTrim.end()));
    }

    std::string trimBegin(const std::string &input, const std::vector<std::string> &stringsToTrim) {
            std::string result = input;
            for (const std::string &trimString : stringsToTrim) {
                while (result.substr(0, trimString.length()) == trimString) {
                    result.erase(0, trimString.length());
                }
            }
            return result;
    }

    std::string trimBegin(const std::string &input, const char &charToTrim) {
        return trimBegin(input, std::vector<char>{charToTrim});
    }
} // namespace parseop


/**
 * @file trimEnd.cpp
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
    std::string trimEnd(const std::string &input, const std::vector<char> &charsToTrim) {
        if (input.empty())
            return input;
        std::size_t lastValidPos = input.find_last_not_of(
            std::string{charsToTrim.begin(), charsToTrim.end()}.c_str(),
            input.size()
        );
        if (lastValidPos == std::string::npos)
            return "";
        return input.substr(0, lastValidPos + 1);
    }

    std::string trimEnd(const std::string &input, const std::string &charsToTrim) {
        return trimEnd(input, std::vector<char>(charsToTrim.begin(), charsToTrim.end()));
    }

    std::string trimEnd(const std::string &input, const std::vector<std::string> &stringsToTrim) {
        std::string result = input;
        for (const std::string &trimString : stringsToTrim) {
            while (result.length() >= trimString.length() && result.substr(result.length() - trimString.length()) == trimString) {
                result.erase(result.length() - trimString.length());
            }
        }
        return result;
    }

    std::string trimEnd(const std::string &input, const char &charToTrim) {
        return trimEnd(input, std::vector<char>{charToTrim});
    }
} // namespace parseop


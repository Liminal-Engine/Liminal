/**
 * @file trim.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "parseop.hpp"

#include <string>
#include <vector>

namespace parseop {
    std::string trim(const std::string &input, const std::vector<char> &charsToTrim) {
        return trimEnd( trimBegin(input, charsToTrim), charsToTrim );
    }

    std::string trim(const std::string &input, const std::string &charsToTrim) {
        return trim(input, std::vector<char>(charsToTrim.begin(), charsToTrim.end()));
    }

    std::string trim(const std::string &input, const std::vector<std::string> &stringsToTrim) {
        return trimEnd( trimBegin(input, stringsToTrim), stringsToTrim );
    }

    std::string trim(const std::string &input, const char &charToTrim) {
        return trim(input, std::vector<char>{charToTrim});
    }
} // namespace parseop


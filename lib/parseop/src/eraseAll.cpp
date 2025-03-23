/**
 * @file eraseAll.cpp
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
#include <algorithm>

namespace parseop {
    std::string eraseAll(const std::string &input, const std::vector<std::string> &subStrs) {
        std::string _inputCpy = input;
        std::vector<std::string> _subStrsCpy = subStrs;
        
        std::sort(_subStrsCpy.begin(), _subStrsCpy.end(),
        [](const std::string& a, const std::string& b) {
            return a.length() > b.length();
        });

        // Erase substrings from the input string
        for (const std::string &subStr : _subStrsCpy) {
            if (subStr != "") {
                size_t pos;
                while ((pos = _inputCpy.find(subStr)) != std::string::npos) {
                    _inputCpy.erase(pos, subStr.length());
                }
            }
        }
        return _inputCpy;
    }

    std::string eraseAll(const std::string &input, const std::string &substr) {
        return eraseAll(input, std::vector{substr});
    }
} // namespace parseop


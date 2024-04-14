/**
 * @file isOnlyChar.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <string>
#include <algorithm>

namespace parseop {
    bool isOnlyChar(const std::string &str, const char &c) {
        if (str.empty()) return false;
        return std::all_of(str.begin(), str.end(), [&c](char ch) { return ch == c; });
    }
} // namespace parseop

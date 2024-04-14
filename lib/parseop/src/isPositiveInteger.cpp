/**
 * @file isPositiveInteger.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <string>

namespace parseop {
    bool isPositiveInteger(const std::string &str) {
        return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
    }
} // namespace parseop

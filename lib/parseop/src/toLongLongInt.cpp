/**
 * @file toLongLongInt.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-19
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "parseop.hpp"

#include <string>
#include <cstdint>

namespace parseop {
    long long int toLongLongInt(const std::string &str) {
        if (isOnlyChar(str, '0')) return (long long int)0;
        return (long long int)std::stoll(str);
    }
} // namespace parseop


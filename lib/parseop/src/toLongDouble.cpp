/**
 * @file toLongDouble.cpp
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

namespace parseop {
    long double toLongDouble(const std::string &str) {
        if (isOnlyChar(str, '0')) return (long double)0;

        return std::stold(str);
    }
} // namespace parseop

/**
 * @file toIntMax.cpp
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
#include <cstdint>

namespace parseop {
    intmax_t toIntMax(const std::string &str) {
        if (isOnlyChar(str, '0')) return (intmax_t)0;
        return (intmax_t)std::stol(str);
    }
} // namespace parseop


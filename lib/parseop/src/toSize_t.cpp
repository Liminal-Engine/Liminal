/**
 * @file toSize_t.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "parseop.hpp"

#include <cstddef>
#include <string>

namespace parseop {
    std::size_t toSize_t(const std::string &str) {
        if (isOnlyChar(str, '0')) return (std::size_t)0;

        return std::stoul(str);
    }
} // namespace parseop


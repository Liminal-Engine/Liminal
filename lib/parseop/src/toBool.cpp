/**
 * @file toBool.cpp
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
    bool toBool(
        const std::string &str,
        const bool &include_nb
    ) {
        if (!isBool(str, include_nb)) return false;
        if (include_nb) {
            if (isOnlyChar(str, '0')) return false;
            if (isPositiveInteger(str)) return true;
        }
        if (str == "false") return false;
        if (str == "true") return true;
        return false;
    }
} // namespace parseop


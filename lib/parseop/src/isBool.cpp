/**
 * @file isBool.cpp
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
    bool isBool(const std::string &str, const bool &include_nb) {
        if (str.empty()) {
            return false;
        }
        if (include_nb) {
            return str == "false" || str == "true" || isPositiveInteger(str);
        } else {
            return str == "false" || str == "true";
        }
    }
} // namespace parseop


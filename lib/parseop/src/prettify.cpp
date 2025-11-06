/**
 * @file prettify.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-06
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include <vector>
#include <string>
#include <sstream>

namespace parseop {
    std::string prettify(const std::vector<std::string> &input, const std::string &bulletPoint) {
        std::stringstream ss;
        for (const std::string &element : input) {
            ss << bulletPoint << " " << element << "\n";
        }
        return ss.str();
    }
    
} // namespace parseop

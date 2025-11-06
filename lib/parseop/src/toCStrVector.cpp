/**
 * @file toConstCStrVector.cpp
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
#include <algorithm>

namespace parseop {
    std::vector<const char *> toCStrVector(const std::vector<std::string> &input) {
        std::vector<const char *> res(input.size());
        std::transform(input.begin(), input.end(), res.begin(), [](const std::string &element) { return element.c_str(); });
        
        return res;
    }
} // namespace parseop

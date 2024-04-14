/**
 * @file endsWith.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-12
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <string>
#include <algorithm>

namespace parseop {
    bool endsWith(const std::string &input, const std::string &target) {
        if (input.size() < target.size()) return false;
        return std::equal(target.rbegin(), target.rend(), input.rbegin());
    }
} // namespace parseop

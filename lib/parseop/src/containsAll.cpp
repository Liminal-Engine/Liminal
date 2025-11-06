/**
 * @file containsAll.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-06
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include <string>
#include <vector>
#include <algorithm>

namespace parseop {
    bool containsAll(const std::vector<std::string> &superset, const std::vector<std::string> &subset) {
        return std::all_of(
            subset.begin(),
            subset.end(),
            [&](const std::string &subElement) {
                return std::find(superset.begin(), superset.end(), subElement) != superset.end();
            }
        );
    }
} // namespace parseop

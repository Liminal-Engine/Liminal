/**
 * @file getNOccurences.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <cstddef>
#include <string>
#include <algorithm>

namespace parseop {    
    std::size_t getNOccurences(const std::string &str, const char &c) {
        return std::count(str.begin(), str.end(), c);
    }

    std::size_t getNOccurences(const std::string &str, const std::string &occurence) {
        if (occurence == "") return str == "" ? 1 : 0;
        std::size_t res{0};
        std::size_t pos{0};

        while ( (pos = str.find(occurence, pos)) != std::string::npos) {
            ++res;
            pos += occurence.length();
        }
        return res;
    }
} // namespace parseop

/**
 * @file includes.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <string>
#include <vector>

namespace parseop {
    bool includes(const std::string &str, const char &c) {
        return str.find(c) != std::string::npos;
    }

    bool includes(const std::string &input, const std::vector<char> &chars) {
        for (const char &c: chars) {
            if (includes(input, c)) return true;
        }
        return false;
    }


    bool includes(const std::string &str, const std::string &subStr) {
        return str.find(subStr) != std::string::npos;
    }

    bool includes(const std::string &input, const std::vector<std::string> &strs) {
        for (const std::string &str: strs) {
            if (includes(input, str)) return true;
        }
        return false;
    }

} // namespace parseop


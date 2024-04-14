/**
 * @file join.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

namespace parseop {
    std::string join(const std::vector<std::string> &input, const std::string &separator) {
        if (input.empty()) return "";
        if (separator.empty()) {
            std::string res{};
            for (const std::string &elem : input) res += elem;
            return res;
        }
        std::ostringstream oss;
        std::copy(input.begin(), input.end() - 1, std::ostream_iterator<std::string>(oss, separator.c_str()));
        oss << input.back(); // Add last elem
        return oss.str();
    }

    std::string join(const std::vector<std::string> &input, const char &separator) {
        return join(input, std::string(1, separator));
    }
} // namespace parseop

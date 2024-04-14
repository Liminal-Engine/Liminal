/**
 * @file lastIndexOf.cpp
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

namespace parseop {
    std::size_t lastIndexOf(const std::string &str, const char &c) {
        return str.rfind(c);
    }
} // namespace parseop


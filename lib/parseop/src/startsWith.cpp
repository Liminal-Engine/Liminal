/**
 * @file startsWith.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-12
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <string>

namespace parseop {
    bool startsWith(const std::string &input, const std::string &target) {
        return input.rfind(target, 0) == 0;
    }
} // namespace parseop

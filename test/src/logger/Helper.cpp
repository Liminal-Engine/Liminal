/**
 * @file Helper.cpp 
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-11
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "test/logger/Helper.hpp"
            
namespace test {
    namespace logger {
        
        std::regex Helper::getMessageRegexp(const std::string &levelStr, const std::string &message) {
            // FIXME : here, WARNING must be a param as well
            return std::regex{R"(^.*\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}Z.\d{3}\s{2}\[)" + levelStr + R"(\]\s{1,5}>\s)" + message + R"(\n$)"};
        }
    } // namespace logger
} // namespace test
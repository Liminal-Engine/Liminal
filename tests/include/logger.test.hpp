/**
 * @file logger.test.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-06
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef LIMINAL_TESTS_LOGGER_TEST_HPP_
#define LIMINAL_TESTS_LOGGER_TEST_HPP_

#include <regex>

namespace logger_test {

    std::regex getMessageRegex(const std::string &levelStr, const std::string &message) {
        // FIXME : here, WARNING must be a param as well
        return std::regex{R"(^.*\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}Z.\d{3}\s{2}\[)" + levelStr + R"(\]\s{1,5}>\s)" + message + R"(\n$)"};
    }
    
} // namespace logger_test


#endif // LIMINAL_TESTS_LOGGER_TEST_HPP_


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

#ifndef LIMINAL_TEST_LOGGER_HELPER_HPP_
#define LIMINAL_TEST_LOGGER_HELPER_HPP_

#include <regex>

namespace test {
    namespace logger {
        
        class Helper {
            public:
        
            static std::regex getMessageRegexp(const std::string &levelStr, const std::string &message);
        };
    } // namespace logger
    
} // namespace test


#endif // LIMINAL_TEST_LOGGER_HELPER_HPP_


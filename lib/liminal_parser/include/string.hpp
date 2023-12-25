/**
 * @file string.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-25
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_PARSER_STRING_HPP_
#define LIMINAL_LIB_LIMINAL_PARSER_STRING_HPP_

#include <string>
#include <cstdint>

namespace liminal_parser {
    namespace string {

        
        bool isBool(const std::string &str, const bool &include_nb = false);
    
        bool toBool(
            const std::string &str,
            const bool &include_nb = false,
            const bool &throw_error = false
        );


        inline bool isOnlyChar(const std::string &str, const char &c);
        inline bool isNonNegativeInteger(const std::string &str);
        intmax_t toIntMax(const std::string &str, const bool &throw_error = false);
        
        std::size_t getOccurences(const std::string &str, const char &c);
        std::size_t getOccurences(const std::string &str, const std::string &occurence);
        std::size_t lastIndexOf(const std::string &str, const char &c, const bool &throwError = false);

    } // namespace string
} // namespace liminal_parser




#endif // LIMINAL_LIB_LIMINAL_PARSER_STRING_HPP_
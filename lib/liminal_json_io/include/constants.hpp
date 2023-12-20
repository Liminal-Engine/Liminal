/**
 * @file constants.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-20
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO_CONSTANTS_HPP
#define LIMINAL_LIB_LIMINAL_JSON_IO_CONSTANTS_HPP

#include <cstddef>

namespace liminal_json_io {
    namespace constants {

        constexpr char JSON_FILE_EXTENSION[]    =   "json";
        constexpr char JSON_COMMA               =   ',';
        constexpr char JSON_COLON               =   ':';
        constexpr char JSON_LEFT_BRACKET        =   '[';
        constexpr char JSON_RIGHT_BRACKET       =   ']';
        constexpr char JSON_LEFT_BRACE          =   '{';
        constexpr char JSON_RIGHT_BRACE         =   '}';
        constexpr char JSON_QUOTE               =   '\"'; //TODO : does JSON accecpt also single quotes '\'' ?
        constexpr char JSON_WHITE_SPACE[]       =   {' ', '\t', '\b', '\n', '\r'};
        constexpr char JSON_TOKENS[]            =   {
                                                        JSON_COMMA,
                                                        JSON_COLON,
                                                        JSON_LEFT_BRACKET,
                                                        JSON_RIGHT_BRACKET,
                                                        JSON_LEFT_BRACE, 
                                                        JSON_RIGHT_BRACE
                                                    };
        constexpr char JSON_TRUE[]              =   "true";
        constexpr char JSON_FALSE[]             =   "false";
        constexpr char JSON_NULL[]              =   "null";
        constexpr std::size_t JSON_TRUE_LEN     =   sizeof(JSON_TRUE);
        constexpr std::size_t JSON_FALSE_LEN    =   sizeof(JSON_FALSE);
        constexpr std::size_t JSON_NULL_LEN     =   sizeof(JSON_NULL);
        constexpr char JSON_NUM_CHARS[]         =   {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', 'e', '.'};
        //TODO : '-' in first num char only ?
        
    } // namespace constants
} // namespace liminal_json_io

#endif // LIMINAL_LIB_LIMINAL_JSON_IO_CONSTANTS_HPP
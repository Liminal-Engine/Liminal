/**
 * @file _syntax.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__SYNTAX_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__SYNTAX_HPP_

namespace liminal_json_io {
    namespace _private  {
        namespace _syntax {

            constexpr   char            _FILE_EXTENSION_S[]     =   "json";
            constexpr   char            _COMMA_C                =   ',';
            constexpr   char            _COLON_C                =   ':';
            constexpr   char            _LEFT_BRACKET_C         =   '[';
            constexpr   char            _RIGHT_BRACKET_C        =   ']';
            constexpr   char            _LEFT_BRACE_C           =   '{';
            constexpr   char            _RIGHT_BRACE_C          =   '}';
            constexpr   char            _QUOTE_C                =   '\"';
            constexpr   char            _WHITE_SPACES_C_A[]     =   {
                                                                        ' ',
                                                                        '\t',
                                                                        '\b',
                                                                        '\n',
                                                                        '\r'
                                                                    };
            constexpr   char            _FORMAT_TOKENS_C_A[]    =   {
                                                                        _COMMA_C,
                                                                        _COLON_C,
                                                                        _LEFT_BRACKET_C,
                                                                        _RIGHT_BRACKET_C,
                                                                        _LEFT_BRACE_C,
                                                                        _RIGHT_BRACE_C             
                                                                    };
            constexpr   char            _TRUE_S[]               =   "true";
            constexpr   char            _FALSE_S[]              =   "false";
            constexpr   char            _NULL_S[]               =   "null";
            constexpr   std::size_t     _TRUE_LEN_SIZE_T        =   sizeof(_TRUE_S) - 1;
            constexpr   std::size_t     _FALSE_LEN_SIZE_T       =   sizeof(_FALSE_S) - 1;
            constexpr   std::size_t     _NULL_LEN_SIZE_T        =   sizeof(_NULL_S) - 1;
            constexpr   char            _NUM_CHARS_C_A[]        =   {
                                                                        '0',
                                                                        '1',
                                                                        '2',
                                                                        '3',
                                                                        '4',
                                                                        '5',
                                                                        '6',
                                                                        '7',
                                                                        '8',
                                                                        '9',
                                                                        '-',
                                                                        'e',
                                                                        '.'
                                                                    };
        } // namespace _syntax
    } // namespace _private
} // namespace liminal_json_io

#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__SYNTAX_HPP_

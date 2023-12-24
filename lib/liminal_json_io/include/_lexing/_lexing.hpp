/**
 * @file _lexing.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__LEXING__LEXING_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__LEXING__LEXING_HPP_

#include <string>
#include <vector>

namespace liminal_json_io {
    namespace _lexing {

        typedef std::string _token_t;
        typedef std::vector<_token_t> _tokens_t;

        _tokens_t _processLexing(const std::string &json_as_string);
        
    } // namespace _lexing
} // namespace liminal_json_io

#endif // LIMINAL_LIB_LIMINAL_JSON_IO__LEXING__LEXING_HPP_

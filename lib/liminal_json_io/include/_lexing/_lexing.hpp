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

#include "_lexing/_Token.hpp"

#include <string>
#include <vector>
#include <memory>

namespace liminal_json_io {
    namespace _lexing {

        typedef std::string untyped_token_t;
        typedef std::vector<std::shared_ptr<_lexing::_Token>> _tokens_t;

        struct _LexingIndex {
            std::size_t nChar = 0;
            std::size_t nLine = 0;
        };

        _tokens_t _processLexing(const std::string &json_as_string);
        
    } // namespace _lexing
} // namespace liminal_json_io

#endif // LIMINAL_LIB_LIMINAL_JSON_IO__LEXING__LEXING_HPP_

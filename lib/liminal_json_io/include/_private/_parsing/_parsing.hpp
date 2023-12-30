/**
 * @file _parsing.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-27
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__PARSING__PARSING_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__PARSING__PARSING_HPP_

#include "_private/_lexing/_types.hpp"
#include "types.hpp"

#include <utility>

namespace liminal_json_io {
    namespace _private {
        namespace _parsing {

            /*
            Each of these functions will share the same original _Tokens_t send
            to _processParsing and will modify it upon successive recursive calls
            */

           using parsingRes_t = std::pair<_lexing::_types::_Token_s, _lexing::_types::_Tokens_t>;
           using arrayParsingRes_t = std::pair<types::Array_t, _lexing::_types::_Tokens_t>;
           using objectParsingRes_t = std::pair<types::Object_t, _lexing::_types::_Tokens_t>;

            types::JsonValue _processParsing(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index);
            
            types::JsonValue __parseObject(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index);
            types::JsonValue __parseArray(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index);
            
        } // namespace _parsing
    } // namespace _private
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__PARSING__PARSING_HPP_
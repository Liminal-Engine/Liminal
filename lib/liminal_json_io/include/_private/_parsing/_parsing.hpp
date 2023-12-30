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
#include "_private/_JsonValue.hpp"

namespace liminal_json_io {
    namespace _private {
        namespace _parsing {

            /*
            Each of these functions will share the same original _Tokens_t send
            to _processParsing and will modify it upon successive recursive calls
            */
            _JsonValue _processParsing(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index);
            _JsonValue __parseObject(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index);
            _JsonValue __parseArray(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index);
            
        } // namespace _parsing
    } // namespace _private
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__PARSING__PARSING_HPP_
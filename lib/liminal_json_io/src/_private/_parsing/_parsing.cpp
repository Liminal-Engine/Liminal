/**
 * @file _parsing.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-27
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_private/_parsing/_parsing.hpp"
#include "_private/_parsing/_types.hpp"
#include "_private/_syntax.hpp"

#include "liminal_string_extras/string.hpp"

#include <stdexcept>
#include <iostream>

namespace liminal_json_io {
    namespace _private {
        namespace _parsing {

            _JsonValue _processParsing(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index) {
                if (currentToken.isEqual(_syntax::_LEFT_BRACE_C)) {
                    return __parseObject(currentToken, tokens, index);
                } else if (currentToken.isEqual(_syntax::_LEFT_BRACKET_C)) {
                    return __parseArray(currentToken, tokens, index);
                }
                return _JsonValue(currentToken);
            }

            _JsonValue __parseObject(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index) {
                _types::_Object_t object{};

                currentToken = tokens.at(++index);
                if (currentToken.type != _lexing::_types::_TokenTypes_e_c::KEY) {
                    throw std::runtime_error("Key was expected. Got " + currentToken.getTypeAsStr() + "value = " + currentToken.strValue);
                }
                while (currentToken.isEqual(_syntax::_RIGHT_BRACE_C) == false) {
                    _types::_Key_t key{currentToken.strValue}; // TODO: check if token is indeed a key. same in __parseArray()
                    if ( (currentToken = tokens.at(++index)).isEqual(_syntax::_COLON_C) == false ) {
                        throw std::runtime_error("Error. Expected colon after key in JSON. Got :" + currentToken.strValue);
                    }
                    currentToken = tokens.at(++index); //Advance to the actual value
                    _JsonValue newJsonValue = _processParsing(currentToken, tokens, index);
                    object.insert({key, std::make_shared<_JsonValue>(newJsonValue)});
                    if ( (currentToken = tokens.at(++index)).isEqual(_syntax::_COMMA_C) ) {
                        currentToken = tokens.at(++index); //If on a comma, go to following token
                    }
                }
                return _JsonValue(object);
            }

            _JsonValue __parseArray(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index) {
                _types::_Array_t array{};

                currentToken = tokens.at(++index);
                while (currentToken.isEqual(_syntax::_RIGHT_BRACKET_C) == false) {
                    _JsonValue newJsonValue = _processParsing(currentToken, tokens, index);
                    array.push_back(std::make_shared<_JsonValue>(newJsonValue));
                    if ( (currentToken = tokens.at(++index)).isEqual(_syntax::_COMMA_C) ) {
                        currentToken = tokens.at(++index); //If on a comma, go to following token
                    }
                }
                return _JsonValue(array);
            }


        } // namespace _parsing
    } // namespace _private
} // namespace liminal_json_io

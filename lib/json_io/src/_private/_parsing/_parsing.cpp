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
#include "_private/_error/_Errors.hpp"

#include "parser/string.hpp"

#include <stdexcept>
#include <iostream>

namespace json_io {
    namespace _private {
        namespace _parsing {

            _JsonValue _processParsing(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index) {
                if (currentToken == _syntax::_LEFT_BRACE_C)
                    return __parseObject(currentToken, tokens, index);
                else if (currentToken == _syntax::_LEFT_BRACKET_C)
                    return __parseArray(currentToken, tokens, index);
                else if (index == 0)
                    THROW(_private::_error::_Parsing, "Missing brace or bracket around token : %s", currentToken.getValueAsStr().c_str());
                return _JsonValue(currentToken);
            }

            _JsonValue __parseObject(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index) {
                _types::_Object_t object{};

                currentToken = tokens.at(++index);
                if (currentToken.getType() != _lexing::_types::_TokenTypes_e_c::KEY && currentToken.getValueAsStr() != std::string{_syntax::_RIGHT_BRACE_C} )
                    THROW(_private::_error::_Parsing, "Key was expected. Got %s with value : %s", currentToken.getTypeAsStr().c_str(), currentToken.getValueAsStr().c_str());
                while (currentToken != _syntax::_RIGHT_BRACE_C) {
                    if (currentToken.getType() != _lexing::_types::_TokenTypes_e_c::KEY)
                        THROW(_private::_error::_Parsing, "Error. Expected key. Got : %s", currentToken.getValueAsStr());
                    _types::_Key_t key{currentToken.getValueAsStr()};
                    if ( (currentToken = tokens.at(++index)) != _syntax::_COLON_C )
                        THROW(_private::_error::_Parsing, "Error. Expected colon after key in JSON. Got : %s", currentToken.getValueAsStr().c_str());
                    currentToken = tokens.at(++index); //Advance to the actual value
                    _JsonValue newJsonValue = _processParsing(currentToken, tokens, index);
                    object.insert({key, std::make_shared<_JsonValue>(newJsonValue)});
                    if (index == tokens.size() - 1)
                        THROW(_private::_error::_Parsing, "Missing closing brace in object around token: %s", tokens.at(index).getValueAsStr().c_str());
                    if ( (currentToken = tokens.at(++index)) == _syntax::_COMMA_C ) {
                        currentToken = tokens.at(++index); //If on a comma, go to following token
                    }
                }
                return _JsonValue(object);
            }

            _JsonValue __parseArray(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index) {
                _types::_Array_t array{};

                currentToken = tokens.at(++index);
                while (currentToken != _syntax::_RIGHT_BRACKET_C) {
                    _JsonValue newJsonValue = _processParsing(currentToken, tokens, index);
                    array.push_back(std::make_shared<_JsonValue>(newJsonValue));
                    if (index == tokens.size() - 1)
                        THROW(_private::_error::_Parsing, "Missing closing bracket in object around token: %s", tokens.at(index).getValueAsStr().c_str());
                    if ( (currentToken = tokens.at(++index)) == _syntax::_COMMA_C ) {
                        currentToken = tokens.at(++index); //If on a comma, go to following token
                    } else if (currentToken != _syntax::_RIGHT_BRACKET_C) // else, if not end of the array, throw error because missing comma
                        THROW(_private::_error::_Parsing, "Error, missing comma in array. Got %s", currentToken.getValueAsStr().c_str());
                }
                return _JsonValue(array);
            }


        } // namespace _parsing
    } // namespace _private
} // namespace json_io

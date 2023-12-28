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
#include "_private/_syntax.hpp"

#include <stdexcept>

#include <iostream>

namespace liminal_json_io {
    namespace _private {
        namespace _parsing {

            types::JsonValue _processParsing(_lexing::_types::_Token_s &currentToken, _lexing::_types::_Tokens_t &tokens, std::size_t &index) {
                if (currentToken.isEqual(_syntax::_LEFT_BRACE_C)) {
                    types::Object_t object{};

                    currentToken = tokens.at(++index);
                    if (currentToken.type != _lexing::_types::_TokenTypes_e_c::STRING) {
                        throw std::runtime_error("Key is expected to be a string. Got " + currentToken.getTypeAsStr() + "value = " + currentToken.strValue);
                    }
                    while (currentToken.isEqual(_syntax::_RIGHT_BRACE_C) == false) {
                        types::Key_t key{currentToken.strValue};
                        if ( (currentToken = tokens.at(++index)).isEqual(_syntax::_COLON_C) == false ) {
                            throw std::runtime_error("Error. Expected colon after key in JSON. Got :" + currentToken.strValue);
                        }
                        currentToken = tokens.at(++index); //Advance to the actual value
                        types::JsonValue newJsonValue = _processParsing(currentToken, tokens, index);
                        object.insert({key, std::make_shared<types::JsonValue>(newJsonValue)});
                        if ( (currentToken = tokens.at(++index)).isEqual(_syntax::_COMMA_C) ) {
                            currentToken = tokens.at(++index); //If on a comma, go to following token
                        }
                    }
                    return types::JsonValue(object);
                } else if (currentToken.isEqual(_syntax::_LEFT_BRACKET_C)) {
                    types::Array_t array{};

                    currentToken = tokens.at(++index);
                    while (currentToken.isEqual(_syntax::_RIGHT_BRACKET_C) == false) {
                        types::JsonValue newJsonValue = _processParsing(currentToken, tokens, index);
                        array.push_back(std::make_shared<types::JsonValue>(newJsonValue));
                        if ( (currentToken = tokens.at(++index)).isEqual(_syntax::_COMMA_C) ) {
                            currentToken = tokens.at(++index); //If on a comma, go to following token
                        }
                    }
                    return types::JsonValue(array);
                } else {
                    return types::JsonValue(currentToken);
                }
            }

            arrayParsingRes_t __parseArray(_lexing::_types::_Tokens_t &tokens) {
                // types::Array_t jsonArray{};
                // _lexing::_types::_Token_s currentToken = tokens.at(0);
                // if (currentToken.isEqual(_syntax::_RIGHT_BRACKET_C)) {
                //     return arrayParsingRes_t(jsonArray, _lexing::_types::_Tokens_t(tokens.begin() + 1, tokens.end()));                    
                // }
                // while (true) {
                    
                //     parsingRes_t newRes = _processParsing(tokens);
                //     tokens = newRes.second;
                //     // jsonArray.push_back(std::make_shared(types::JsonValue(newRes.first)));

                //     currentToken = tokens.at(0);
                //     if (currentToken.isEqual(_syntax::_RIGHT_BRACKET_C)) {
                //         return arrayParsingRes_t(jsonArray, _lexing::_types::_Tokens_t(tokens.begin() + 1, tokens.end()));                    
                //     } else {
                //         tokens.erase(tokens.begin());
                //     }
                // }
                // throw std::runtime_error("Expected end-of-array bracket");
            }

            objectParsingRes_t __parseObject(_lexing::_types::_Tokens_t &tokens) {
                // types::Object_t jsonObject{};
                // _lexing::_types::_Token_s currentToken = tokens.at(0);
                
                // if (currentToken.isEqual(_syntax::_RIGHT_BRACE_C)) {
                //     return objectParsingRes_t(jsonObject, _lexing::_types::_Tokens_t(tokens.begin() + 1, tokens.end()));
                // }
                // while (true) {
                //     _lexing::_types::_Token_s jsonKeyToken = tokens.at(0);
                //     if (jsonKeyToken.type == _lexing::_types::_TokenTypes_e_c::STRING) {
                //         tokens.erase(tokens.begin());
                //     } else  {
                //         throw std::runtime_error("Expected key string, got : " + jsonKeyToken.strValue);
                //     }
                //     if (tokens.at(0).isEqual(_syntax::_COLON_C) == false) {
                //         throw std::runtime_error("Expected colon after key in object. Got : " + tokens.at(0).strValue);
                //     }
                //     _lexing::_types::_Tokens_t tmpTokens(tokens.begin() + 1, tokens.end());
                //     parsingRes_t newRes = _processParsing(tmpTokens);
                //     tokens = newRes.second;
                //     _lexing::_types::_Token_s newToken = newRes.first;
                //     // jsonObject.emplace(jsonKeyToken.strValue, std::make_shared(types::JsonValue(newToken)));

                //     currentToken = tokens.at(0);
                //     if (currentToken.isEqual(_syntax::_RIGHT_BRACE_C)) {
                //         return objectParsingRes_t(jsonObject, _lexing::_types::_Tokens_t(tokens.begin() + 1, tokens.end()));
                //     } else if (currentToken.isEqual(_syntax::_COMMA_C) == false) {
                //         throw std::runtime_error("Expected comma after pair in object. Got : " + currentToken.strValue);
                //     }
                //     tokens.erase(tokens.begin());
                // }
                // throw std::runtime_error("Expected end-of-object bracket");
            }

        } // namespace _parsing
    } // namespace _private
} // namespace liminal_json_io

/**
 * parsingRes_t _processParsing(_lexing::_types::_Tokens_t &tokens, const bool &isRoot) {
                const _lexing::_types::_Token_s currentToken = tokens.at(0);

                
                if (isRoot and currentToken.strValue != std::string{_syntax::_LEFT_BRACE_C}) {
                    throw std::runtime_error("Root must be an object");
                }
                _lexing::_types::_Tokens_t newTokens(tokens.begin() + 1, tokens.end());
                if (currentToken.isEqual(_syntax::_LEFT_BRACKET_C)) {
                    // return __parseArray(newTokens); // TODO : add converters
                    arrayParsingRes_t arrayRes = __parseArray(newTokens);
                    std::cout << "------------" << std::endl;
                    for (const types::JsonValue &value : arrayRes.first) {
                        std::cout << "(arrayRes) | value = " << value._token.getValueAsStr() << " | type = " << value._token.getTypeAsStr() << std::endl;
                    }
                    std::cout << "------------" << std::endl;
                } else if (currentToken.isEqual(_syntax::_LEFT_BRACE_C)) {
                    // return __parseObject(newTokens); // TODO : add converters
                    objectParsingRes_t objectRes = __parseObject(newTokens);
                    std::cout << "------------" << std::endl;
                    for (const auto &keyValuePair : objectRes.first) {
                        std::cout << "(objectRes) | [key|value] = [" << keyValuePair.first << "|" << keyValuePair.second._token.getValueAsStr() << "] | type = " << keyValuePair.second._token.getTypeAsStr() << std::endl;
                    }
                    std::cout << "------------" << std::endl;
                }
                return parsingRes_t(currentToken, newTokens);
            }
 * 
 */
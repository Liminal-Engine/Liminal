/**
 * @file _process.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_private/_lexing/_lexing.hpp"
#include "_private/_syntax.hpp"
#include "_private/_error/_Errors.hpp"

#include "fs/InFile.hpp"
#include "fs/Status.hpp"

#include "parser/string.hpp"

#include <iostream>
#include <algorithm>

namespace json_io {
    namespace _private  {
        namespace _lexing {

                _types::_Tokens_t _processLexing(const fs::Path &path) {
                    _types::_Indices jsonIndices = __convertFileToIndicesContent(path);
                    std::optional<std::string> tmpValue{};
                    _types::_Tokens_t res{};
                    
                    while (jsonIndices.size()) {
                        if ( (tmpValue = __tryLexingString(jsonIndices)).has_value() ) {
                            res.push_back(_types::_Token_s{parser::string::trim(tmpValue.value(), '\"'), _types::_TokenTypes_e_c::STRING });
                            jsonIndices = _types::_Indices(jsonIndices.begin() + tmpValue.value().length(), jsonIndices.end());

                            continue;
                        } else if ( (tmpValue = __tryLexingNumber(jsonIndices)).has_value() ) {
                            res.push_back(_types::_Token_s{
                                tmpValue.value(),
                                parser::string::contains(tmpValue.value(), '.') ? _types::_TokenTypes_e_c::FLOAT_NUM : _types::_TokenTypes_e_c::INT_NUM
                            });
                            jsonIndices = _types::_Indices(jsonIndices.begin() + tmpValue.value().length(), jsonIndices.end());
                            continue;
                        } else if ( (tmpValue = __tryLexingBool(jsonIndices)).has_value() ) {
                            res.push_back(_types::_Token_s{tmpValue.value(), _types::_TokenTypes_e_c::BOOL});
                            jsonIndices = _types::_Indices(jsonIndices.begin() + tmpValue.value().length(), jsonIndices.end());
                            continue;
                        } else if ( (tmpValue = __tryLexingNull(jsonIndices)).has_value() ) {
                            res.push_back(_types::_Token_s{tmpValue.value(), _types::_TokenTypes_e_c::NULL_});
                            jsonIndices = _types::_Indices(jsonIndices.begin() + tmpValue.value().length(), jsonIndices.end());
                            continue;
                        }
                        // Reset tmp optional value
                        tmpValue = std::optional<std::string>{};
                        char currentChar = jsonIndices.at(0).getValue();
                        if (std::find( std::begin(_syntax::_WHITE_SPACES_C_A), std::end(_syntax::_WHITE_SPACES_C_A), currentChar ) != std::end(_syntax::_WHITE_SPACES_C_A)) {
                            jsonIndices.erase(jsonIndices.begin());
                        } else if (std::find( std::begin(_syntax::_FORMAT_TOKENS_C_A), std::end(_syntax::_FORMAT_TOKENS_C_A), currentChar ) != std::end(_syntax::_FORMAT_TOKENS_C_A)) {
                            res.push_back(_types::_Token_s{std::string{currentChar}, _types::_TokenTypes_e_c::SYNTAX});
                            if (res.back() == _syntax::_COLON_C and res.size() >= 2 and res.at(res.size() - 2).getType() == _types::_TokenTypes_e_c::STRING) { //If current token is ":" and last token is a string. Last token is transform to a KEY
                                if (res.at(res.size() - 3).getValueAsStr() != "{" && res.at(res.size() - 3).getValueAsStr() != ",")
                                    THROW(_private::_error::_Parsing, "Error : missing comma approximately at %s", jsonIndices.at(0).getPosDescription().c_str());
                                res.at(res.size() - 2).setType(_types::_TokenTypes_e_c::KEY);
                            }
                            jsonIndices.erase(jsonIndices.begin());
                        } else
                            THROW(_private::_error::_Parsing, "Unexpected character, got : %s at position : %s", std::string{currentChar}.c_str(), jsonIndices.at(0).getPosDescription().c_str());
                    }
                    return res;
                }

                std::optional<std::string> __tryLexingString(_types::_Indices jsonIndices) {
                    std::optional<std::string> res{};
                    bool escaped = false;
                    
                    if (jsonIndices.at(0).getValue() == _syntax::_QUOTE_C) {
                        __updateOptionalString(res, jsonIndices.at(0).getValue()); //if start with a quote, it's a string                    
                        jsonIndices.erase(jsonIndices.begin());
                        for (const _types::_Index &index : jsonIndices) {
                            if (escaped == false && index.getValue() == _syntax::_QUOTE_C) { // if end of string, but quote is not escaped
                                __updateOptionalString(res,index.getValue());
                                break;
                            } 
                            __updateOptionalString(res, index.getValue());

                            escaped = index.getValue() == '\\';
                        }
                    }
                    return res;
                }

                std::optional<std::string> __tryLexingNumber(const _types::_Indices &jsonIndices) {
                    std::optional<std::string> res{};

                    for (const _types::_Index &index : jsonIndices) {
                        if (std::find(std::begin(_syntax::_NUM_CHARS_C_A), std::end(_syntax::_NUM_CHARS_C_A), index.getValue()) != std::end(_syntax::_NUM_CHARS_C_A)) {
                            __updateOptionalString(res, index.getValue());
                        } else {
                            break;
                        }
                    }
                    return res;
                }
                
                std::optional<std::string> __tryLexingBool(const _types::_Indices &jsonIndices) {
                    std::optional<std::string> res{};
                    const std::string stringContent{__convertIndicesToString(jsonIndices)};
                    const std::size_t contentLen{stringContent.length()};

                    if (contentLen >= _syntax::_TRUE_LEN_SIZE_T and stringContent.substr(0, _syntax::_TRUE_LEN_SIZE_T) == std::string{_syntax::_TRUE_S}) {
                        __updateOptionalString(res, "true");
                    } else if (contentLen >= _syntax::_FALSE_LEN_SIZE_T and stringContent.substr(0, _syntax::_FALSE_LEN_SIZE_T) == std::string{_syntax::_FALSE_S}) {
                        __updateOptionalString(res, "false");
                    }
                    return res;

                }


                std::optional<std::string> __tryLexingNull(const _types::_Indices &jsonIndices) {
                    std::optional<std::string> res{};
                    const std::string stringContent = __convertIndicesToString(jsonIndices);

                    if (stringContent.length() >= _syntax::_NULL_LEN_SIZE_T and stringContent.substr(0, _syntax::_NULL_LEN_SIZE_T) == std::string{_syntax::_NULL_S}) {
                        __updateOptionalString(res, "null");
                    }
                    return res;

                }

                _types::_Indices __convertFileToIndicesContent(const fs::Path &path) {
                    _types::_Indices res{};
                    std::size_t tmpLine{1};
                    std::size_t tmpLineOffset{0};
                    std::string stringFileContent{};

                    fs::InFile jsonFile(path);
                    char cwd[1024];
                    getcwd(cwd, sizeof(cwd));
                    if (jsonFile.open() != fs::Status::OK)
                        THROW(_private::_error::_File, "Failed to open JSON file : %s", path.toStr().c_str());
                    if (jsonFile.read() != fs::Status::OK)
                        THROW(_private::_error::_File, "Failed to read JSON file : %s", path.toStr().c_str());
                    if (jsonFile.close() != fs::Status::OK)
                        THROW(_private::_error::_File, "Failed to close JSON file : %s", path.toStr().c_str());
                    stringFileContent = jsonFile.get_content();
                    for (const char &c : stringFileContent) {
                        tmpLineOffset++;
                        if (c == '\n') {
                            tmpLine++;
                            tmpLineOffset = 0;
                        }
                        res.push_back(_types::_Index{c, tmpLine, tmpLineOffset});
                    }
                    return res;
                }

                void __updateOptionalString(std::optional<std::string> &optionalString, const char &c) {
                    if (optionalString.has_value()) {
                        *optionalString += c;
                    } else {
                        optionalString.emplace(std::string{c});
                    }
                }

                void __updateOptionalString(std::optional<std::string> &optionalString, const std::string &value) {
                    optionalString.emplace(value);
                }

                std::string __convertIndicesToString(const _types::_Indices &indices) {
                    std::string res(indices.size(), '\0');

                    std::transform(indices.begin(), indices.end(), res.begin(), [](const _types::_Index &index) {
                        return index.getValue();
                    });
                    return res;
                }

        } // namespace _lexing
    } // namespace _private
} // namespace json_io

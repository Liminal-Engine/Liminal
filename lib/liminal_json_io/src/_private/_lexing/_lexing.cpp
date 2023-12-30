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

#include "InFile.hpp"
#include "string.hpp"

#include <iostream>
#include <algorithm>

namespace liminal_json_io {
    namespace _private  {
        namespace _lexing {

                _types::_Tokens_t _processLexing(const std::string &path) {
                    _types::_Indices jsonIndices = __convertFileToIndicesContent(path);
                    std::optional<std::string> tmpValue{};
                    _types::_Tokens_t res{};
                    
                    while (jsonIndices.size()) {
                        if ( (tmpValue = __tryLexingString(jsonIndices)).has_value() ) {
                            res.push_back(_types::_Token_s{.strValue = liminal_parser::string::trim(tmpValue.value(), '\"'), .type = _types::_TokenTypes_e_c::STRING });
                            jsonIndices = _types::_Indices(jsonIndices.begin() + tmpValue.value().length(), jsonIndices.end());

                            continue;
                        } else if ( (tmpValue = __tryLexingNumber(jsonIndices)).has_value() ) {
                            res.push_back(_types::_Token_s{
                                .strValue = tmpValue.value(),
                                .type = liminal_parser::string::contains(tmpValue.value(), '.') ? _types::_TokenTypes_e_c::FLOAT_NUM : _types::_TokenTypes_e_c::INT_NUM
                            });
                            jsonIndices = _types::_Indices(jsonIndices.begin() + tmpValue.value().length(), jsonIndices.end());
                            continue;
                        } else if ( (tmpValue = __tryLexingBool(jsonIndices)).has_value() ) {
                            res.push_back(_types::_Token_s{.strValue = tmpValue.value(), .type = _types::_TokenTypes_e_c::BOOL});
                            jsonIndices = _types::_Indices(jsonIndices.begin() + tmpValue.value().length(), jsonIndices.end());
                            continue;
                        } else if ( (tmpValue = __tryLexingNull(jsonIndices)).has_value() ) {
                            res.push_back(_types::_Token_s{.strValue = tmpValue.value(), .type = _types::_TokenTypes_e_c::NULL_});
                            jsonIndices = _types::_Indices(jsonIndices.begin() + tmpValue.value().length(), jsonIndices.end());
                            continue;
                        }
                        // Reset tmp optional value
                        tmpValue = std::optional<std::string>{};
                        char currentChar = jsonIndices.at(0).value;
                        if (std::find( std::begin(_syntax::_WHITE_SPACES_C_A), std::end(_syntax::_WHITE_SPACES_C_A), currentChar ) != std::end(_syntax::_WHITE_SPACES_C_A)) {
                            jsonIndices.erase(jsonIndices.begin());
                        } else if (std::find( std::begin(_syntax::_FORMAT_TOKENS_C_A), std::end(_syntax::_FORMAT_TOKENS_C_A), currentChar ) != std::end(_syntax::_FORMAT_TOKENS_C_A)) {
                            res.push_back(_types::_Token_s{.strValue = std::string{currentChar}, .type = _types::_TokenTypes_e_c::SYNTAX});
                            if (res.back().isEqual(_syntax::_COLON_C) and res.size() >= 2 and res.at(res.size() - 2).type == _types::_TokenTypes_e_c::STRING) { //If current token is ":" and last token is a string. Last token is transform to a KEY
                                res.at(res.size() - 2).type = _types::_TokenTypes_e_c::KEY;
                            }
                            jsonIndices.erase(jsonIndices.begin());
                        } else {
                            throw std::runtime_error("Unexpected character, got : " + std::string{currentChar} + "at position : " + jsonIndices.at(0).getPosDescription());
                        }
                    }
                    return res;
                }

                std::optional<std::string> __tryLexingString(_types::_Indices jsonIndices) {
                    std::optional<std::string> res{};
                    
                    if (jsonIndices.at(0).value == _syntax::_QUOTE_C) {
                        __updateOptionalString(res, jsonIndices.at(0).value); //if start with a quote, it's a string                    
                        jsonIndices.erase(jsonIndices.begin());
                        for (const _types::_Index &index : jsonIndices) {
                            if (index.value == _syntax::_QUOTE_C) {
                                __updateOptionalString(res,index.value); //if start with a quote, it's a string                    
                                break;
                            } // if end of string
                            __updateOptionalString(res, index.value);
                        }
                    }
                    return res;
                }

                std::optional<std::string> __tryLexingNumber(const _types::_Indices &jsonIndices) {
                    std::optional<std::string> res{};

                    for (const _types::_Index &index : jsonIndices) {
                        if (std::find(std::begin(_syntax::_NUM_CHARS_C_A), std::end(_syntax::_NUM_CHARS_C_A), index.value) != std::end(_syntax::_NUM_CHARS_C_A)) {
                            __updateOptionalString(res, index.value);
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

                _types::_Indices __convertFileToIndicesContent(const std::string &path) {
                    std::string extension{""};
                    _types::_Indices res{};
                    std::size_t tmpLine{1};
                    std::size_t tmpLineOffset{0};
                    std::string stringFileContent{};

                    if (liminal_fs::path::get_file_extension(extension, path) != liminal_fs::Status::OK) {
                        throw std::runtime_error("Failed to load JSON file : " + path);
                    }
                    if (extension != std::string(std::string(".") + std::string(_syntax::_FILE_EXTENSION_S))) {
                        throw std::runtime_error("Error : file is not a JSON");
                    }
                    liminal_fs::InFile jsonFile(path);
                    if (jsonFile.open() != liminal_fs::Status::OK) {
                        throw std::runtime_error("Failed to open JSON file : " + path);
                    }
                    if (jsonFile.read() != liminal_fs::Status::OK) {
                        throw std::runtime_error("Failed to read JSON file : " + path);
                    }
                    if (jsonFile.close() != liminal_fs::Status::OK) {
                        throw std::runtime_error("Failed to close JSON file : " + path);
                    }
                    stringFileContent = jsonFile.get_content();
                    for (const char &c : stringFileContent) {
                        tmpLineOffset++;
                        if (c == '\n') {
                            tmpLine++;
                            tmpLineOffset = 0;
                        }
                        res.push_back(_types::_Index{.value = c, .line = tmpLine, .lineOffset = tmpLineOffset});
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
                        return index.value;
                    });
                    return res;
                }

        } // namespace _lexing
    } // namespace _private
} // namespace liminal_json_io

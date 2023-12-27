/**
 * @file _process.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__LEXING__PROCESS_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__LEXING__PROCESS_HPP_

#include "_private/_lexing/_types.hpp"

#include <optional>

namespace liminal_json_io {
    namespace _private  {
        namespace _lexing {

                /**This is the only function you should be using here*/
                _types::_Tokens_t _processLexing(const std::string &path);

                std::optional<std::string> __tryLexingString(_types::_Indices jsonIndices);
                std::optional<std::string> __tryLexingNumber(const _types::_Indices &jsonIndices);
                std::optional<std::string> __tryLexingBool(const _types::_Indices &jsonIndices);
                std::optional<std::string> __tryLexingNull(const _types::_Indices &jsonIndices);

                _types::_Indices __convertFileToIndicesContent(const std::string &path);

                std::string __convertIndicesToString(const _types::_Indices &indices);

                void __updateOptionalString(std::optional<std::string> &optionalString, const char &c);
                void __updateOptionalString(std::optional<std::string> &optionalString, const std::string &value);
        } // namespace _lexing
    } // namespace _private
} // namespace liminal_json_io

#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__LEXING__PROCESS_HPP_

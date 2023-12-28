/**
 * @file _types.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__LEXING__TYPES_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__LEXING__TYPES_HPP_

#include <string>
#include <vector>


namespace liminal_json_io {
    namespace _private  {
        namespace _lexing {
            namespace _types {

                enum class _TokenTypes_e_c {
                    STRING,
                    INT_NUM,
                    FLOAT_NUM,
                    NULL_,
                    BOOL,
                    SYNTAX
                };

                struct _Token_s {//TODO: private and public members
                    std::string strValue;
                    _TokenTypes_e_c type;
                    bool isEqual(const char &value) const;//TODO: rewrite '==' operator instead
                    bool isEqual(const char value[]) const;
                    bool isEqual(const std::string &value) const;
                    std::string getTypeAsStr(void) const;
                    std::string getValueAsStr(void) const;
                };

                using _Tokens_t = std::vector<_Token_s>;

                struct _Index {//TODO: private and public members
                    char value = 0;
                    std::size_t line = 1;
                    std::size_t lineOffset = 0;
                    const std::string getPosDescription(void) const;
                };

                using _Indices = std::vector<_Index>;

            } // namespace _types
        } // namespace _lexing
    } // namespace _private
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__LEXING__TYPES_HPP_
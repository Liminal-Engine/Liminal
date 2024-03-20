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
                    KEY,
                    STRING,
                    INT_NUM,
                    FLOAT_NUM,
                    NULL_,
                    BOOL,
                    SYNTAX
                };

                struct _Token_s {
                    public:
                        _Token_s(const std::string &strValue, const _TokenTypes_e_c &type);

                        bool operator==(const char &value) const;
                        bool operator==(const char value[]) const;
                        bool operator==(const std::string &value) const;

                        std::string getTypeAsStr(void) const;
                        std::string getValueAsStr(void) const;
                        _TokenTypes_e_c getType(void) const;
                        void setType(const _TokenTypes_e_c &type);
                    private:
                        std::string _strValue;
                        _TokenTypes_e_c _type;
                };

                using _Tokens_t = std::vector<_Token_s>;

                struct _Index {
                    public:
                        _Index(const char &value, const std::size_t &line, const std::size_t &lineOffset);

                        char getValue(void) const;
                        const std::string getPosDescription(void) const;
                    private:
                        char _value = 0;
                        std::size_t _line = 1;
                        std::size_t _lineOffset = 0;
                };

                using _Indices = std::vector<_Index>;

            } // namespace _types
        } // namespace _lexing
    } // namespace _private
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__LEXING__TYPES_HPP_
/**
 * @file _Token.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-24
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__LEXING__TOKEN_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__LEXING__TOKEN_HPP_

#include "constants.hpp"

#include <typeinfo>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <memory>

namespace liminal_json_io {
    namespace _lexing {

        typedef char jsonToken_t;
        inline bool __isAValidJSONToken(const char &value) {
            return std::find(
                std::begin(constants::JSON_TOKENS),
                std::end(constants::JSON_TOKENS),
                value
            ) != std::end(constants::JSON_TOKENS);
        }
        typedef std::string nullToken_t;

        class _Token {
            public:
                virtual ~_Token() = default;
                virtual inline std::string getType(void) const = 0;
        };

        template <typename _TokenType>
        class _T_Token : public _Token {
            public:
                _T_Token(const _TokenType &value) :
                _value{value}
                {

                }

                // Getters :
                virtual inline std::string getType(void) const {
                    return typeid(_TokenType).name();
                }

                virtual inline _TokenType getValue(void) const {
                    return this->_value;
                }

            protected:
                _TokenType _value;

        };

        class _StringToken : public _T_Token<std::string > {
            public:
                using _T_Token<std::string>::_T_Token;
        };
        class _IntegerNumberToken : public _T_Token<intmax_t> {
            public:
                using _T_Token<intmax_t>::_T_Token;
        };
        class _FloatingPointNumberToken : public _T_Token<long double> {
            public:
                using _T_Token<long double>::_T_Token;
        };
        class _BoolToken : public _T_Token<bool> {
            public:
                using _T_Token<bool>::_T_Token;
        };
        class _NullToken : public _T_Token<nullToken_t> {
            public:
                _NullToken(const nullToken_t &value) :
                _T_Token<nullToken_t>(value) {
                    if (value != constants::JSON_NULL) {
                        throw std::invalid_argument("Invalid NULL Token found, aborting, got : " + nullToken_t{value});
                    }
                }
        };
        class _JSONToken : public _T_Token<jsonToken_t> {
            public:
                _JSONToken(const jsonToken_t &value) :
                _T_Token<jsonToken_t>(value) {
                    if (!__isAValidJSONToken(value)) {
                        throw std::invalid_argument("Invalid JSON Token found, aborting. Got : " + std::string{value} );
                    }
                }
        };

        inline std::unique_ptr<_Token> _createToken(const std::string &value) { return std::make_unique<_StringToken>(value); }
        inline std::unique_ptr<_Token> _createToken(const intmax_t &value) { return std::make_unique<_IntegerNumberToken>(value); }
        inline std::unique_ptr<_Token> _createToken(const long double &value) { return std::make_unique<_FloatingPointNumberToken>(value); }
        inline std::unique_ptr<_Token> _createToken(const bool &value) { return std::make_unique<_BoolToken>(value); }
        inline std::unique_ptr<_Token> _createToken(void) { return std::make_unique<_NullToken>(constants::JSON_NULL); };
        inline std::unique_ptr<_Token> _createToken(const jsonToken_t &value) { return std::make_unique<_JSONToken>(value); };
    } // namespace _lexing
} // liminal_json_io

#endif // LIMINAL_LIB_LIMINAL_JSON_IO__LEXING__TOKEN_HPP_
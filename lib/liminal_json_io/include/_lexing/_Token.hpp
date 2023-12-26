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
#include "types.hpp"

#include <typeinfo>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <memory>
#include <variant>

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
                virtual inline types::type_t getType(void) const = 0;
                // virtual std::variant<std::string, intmax_t, long double, bool, nullToken_t, jsonToken_t> getValue(void) const = 0;

        };

        template <typename _TokenType>
        class _T_Token : public _Token {
            public:
                _T_Token(const _TokenType &value) :
                _value{value}
                {

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

                inline types::type_t getType(void) const { return types::STRING; };
        };
        class _IntegerNumberToken : public _T_Token<intmax_t> {
            public:
                using _T_Token<intmax_t>::_T_Token;

                inline types::type_t getType(void) const { return types::INTEGER; };

        };
        class _FloatingPointNumberToken : public _T_Token<long double> {
            public:
                using _T_Token<long double>::_T_Token;

                inline types::type_t getType(void) const { return types::FLOAT; };
        };
        class _BoolToken : public _T_Token<bool> {
            public:
                using _T_Token<bool>::_T_Token;
                
                inline types::type_t getType(void) const { return types::BOOL; };
        };
        class _NullToken : public _T_Token<nullToken_t> {
            public:
                _NullToken(const nullToken_t &value) :
                _T_Token<nullToken_t>(value) {
                    if (value != constants::JSON_NULL) {
                        throw std::invalid_argument("Invalid NULL Token found, aborting, got : " + nullToken_t{value});
                    }
                }

                inline types::type_t getType(void) const { return types::NULL_; };

        };
        class _JSONToken : public _T_Token<jsonToken_t> {
            public:
                _JSONToken(const jsonToken_t &value) :
                _T_Token<jsonToken_t>(value) {
                    if (!__isAValidJSONToken(value)) {
                        throw std::invalid_argument("Invalid JSON Token found, aborting. Got : " + std::string{value} );
                    }
                }

                inline types::type_t getType(void) const { return types::TOKEN; };
        };

        inline std::shared_ptr<_Token> _createToken(const std::string &value) { return std::make_unique<_StringToken>(value); }
        inline std::shared_ptr<_Token> _createToken(const intmax_t &value) { return std::make_unique<_IntegerNumberToken>(value); }
        inline std::shared_ptr<_Token> _createToken(const long double &value) { return std::make_unique<_FloatingPointNumberToken>(value); }
        inline std::shared_ptr<_Token> _createToken(const bool &value) { return std::make_unique<_BoolToken>(value); }
        inline std::shared_ptr<_Token> _createToken(void) { return std::make_unique<_NullToken>(constants::JSON_NULL); };
        inline std::shared_ptr<_Token> _createToken(const jsonToken_t &value) { return std::make_unique<_JSONToken>(value); };


        inline std::shared_ptr<_StringToken> getStringToken(const std::shared_ptr<_Token> &token) {
            if (token->getType() == types::STRING) return std::dynamic_pointer_cast<_StringToken>(token);
            throw std::runtime_error("Failed to cast to String Token. Got Token with type : " + token->getType());
        };
        inline std::shared_ptr<_IntegerNumberToken> getIntegerNumberToken(const std::shared_ptr<_Token> &token) {
            if (token->getType() == types::INTEGER) return std::dynamic_pointer_cast<_IntegerNumberToken>(token);
            throw std::runtime_error("Failed to cast to Integer Number Token. Got Token with type : " + token->getType());
        };
        inline std::shared_ptr<_FloatingPointNumberToken> getFloatingPointNumberToken(const std::shared_ptr<_Token> &token) {
            if (token->getType() == types::FLOAT) return std::dynamic_pointer_cast<_FloatingPointNumberToken>(token);
            throw std::runtime_error("Failed to cast to Floating Point Number Token. Got Token with type : " + token->getType());
        };
        inline std::shared_ptr<_BoolToken> getBoolToken(const std::shared_ptr<_Token> &token) {
            if (token->getType() == types::BOOL) return std::dynamic_pointer_cast<_BoolToken>(token);
            throw std::runtime_error("Failed to cast to Bool Token. Got Token with type : " + token->getType());
        };
        inline std::shared_ptr<_NullToken> getNullToken(const std::shared_ptr<_Token> &token) {
            if (token->getType() == types::NULL_) return std::dynamic_pointer_cast<_NullToken>(token);
            throw std::runtime_error("Failed to cast to Null Token. Got Token with type : " + token->getType());
        };
        inline std::shared_ptr<_JSONToken> getJSONToken(const std::shared_ptr<_Token> &token) {
            if (token->getType() == types::TOKEN) return std::dynamic_pointer_cast<_JSONToken>(token);
            throw std::runtime_error("Failed to cast to JSON Token. Got Token with type : " + token->getType());
        };


    } // namespace _lexing
} // liminal_json_io

#endif // LIMINAL_LIB_LIMINAL_JSON_IO__LEXING__TOKEN_HPP_
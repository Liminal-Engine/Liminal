#include "_lexing/_lexing.hpp"
#include "constants.hpp"

#include "string.hpp"

#include <optional>
#include <stdexcept>
#include <algorithm>
#include <string_view>
#include <string>
namespace liminal_json_io {
    namespace _lexing {        

        template<std::size_t EXPR_LEN>
        static inline bool __is_in_json_const_expr(const char &c, const char (&arr)[EXPR_LEN]) {
            return std::find(arr, arr + EXPR_LEN, c) != arr + EXPR_LEN;
        }

        static void __update_optional_token(std::optional<untyped_token_t> &token, const char &value) {
            if (token.has_value()) {
                *token += value;
            } else {
                token.emplace(untyped_token_t{value});
            }
        }

        static void __update_optional_token(std::optional<untyped_token_t> &token, const untyped_token_t &value) {
            token.emplace(value);
        }

        static std::optional<untyped_token_t> __tryLexingString(const std::string &content) {
            std::string _tmp_content = content;
            std::optional<untyped_token_t> res;

            if (_tmp_content.at(0) == constants::JSON_QUOTE) {
                _tmp_content = _tmp_content.substr(1);
            } else {
                return res;
            }
            for (const char &c : _tmp_content) {
                if (c == constants::JSON_QUOTE) { // If end of string
                    return res;
                } else {
                    __update_optional_token(res, c);
                }
            }
            return res;
        }

        static std::optional<untyped_token_t> __tryLexingNumber(const std::string &content) {
            std::optional<untyped_token_t> res;

            for (const char &c : content) {
                if (__is_in_json_const_expr(c, constants::JSON_NUM_CHARS)) {
                    __update_optional_token(res, c);
                } else {
                    break;
                }
            }
            return res;
        }

        static std::optional<untyped_token_t> __tryLexingBool(const std::string &content) {
            std::optional<untyped_token_t> res;

            std::size_t content_len = content.length();
            if (content_len >= constants::JSON_TRUE_LEN && content.substr(0, constants::JSON_TRUE_LEN - 1) == "true") {
                __update_optional_token(res, "true");
            } else if (content_len >= constants::JSON_FALSE_LEN && content.substr(0, constants::JSON_FALSE_LEN - 1) == "false" ) {
                __update_optional_token(res, "false");
            }
            return res;
        }

        static std::optional<untyped_token_t> __tryLexingNull(const std::string &content) {
            std::optional<untyped_token_t> res;

            if (content.length() >= constants::JSON_NULL_LEN && content.substr(0, constants::JSON_NULL_LEN - 1) == "null") {
                __update_optional_token(res, "null");
            }
            return res;
        }

        static void __updateIndex(
            _LexingIndex &index,
            std::optional<untyped_token_t> newToken
        ) {
            std::size_t addLine{0};
    
            addLine = liminal_parser::string::getOccurences(newToken.value(), '\n');
            index.nLine += addLine;
            if (addLine > 0) {
                index.nChar = newToken.value().length() - liminal_parser::string::lastIndexOf(newToken.value(), '\n');
            } else {
                index.nChar += newToken.value().length();
            }
        }

        _tokens_t _processLexing(const std::string &json_as_string) {
            std::string _json_content = json_as_string;
            _tokens_t res;
            std::optional<untyped_token_t> tmp_token{};
            _LexingIndex index{};
            char currentC = 0;
        
            while (_json_content.length() > 0) {
                if ( (tmp_token = __tryLexingString(_json_content) ).has_value() ) {
                    res.push_back(_createToken(tmp_token.value()));
                    __updateIndex(index, tmp_token);
                    _json_content = _json_content.substr(tmp_token.value().length() + 2); // + 2 for both commas
                    continue;
                } else if ( (tmp_token = __tryLexingNumber(_json_content)).has_value() ) {
                    res.push_back( 
                        _createToken(
                            liminal_parser::string::contains(tmp_token.value(), '.') ?
                            liminal_parser::string::toLongDouble(tmp_token.value()) :
                            liminal_parser::string::toIntMax(tmp_token.value())
                        ));
                    __updateIndex(index, tmp_token);
                    _json_content = _json_content.substr(tmp_token.value().length());
                    continue;
                } else if ( (tmp_token = __tryLexingBool(_json_content)).has_value() ) {
                    res.push_back( _createToken( liminal_parser::string::toBool(tmp_token.value()) ) );
                    __updateIndex(index, tmp_token);
                    _json_content = _json_content.substr(tmp_token.value().length());
                    continue;
                } else if ( (tmp_token = __tryLexingNull(_json_content)).has_value() ) {
                    res.push_back(_createToken());
                    __updateIndex(index, tmp_token);
                    _json_content = _json_content.substr(tmp_token.value().length());
                    continue;
                }
                // Reset token if not found
                tmp_token = std::optional<untyped_token_t>();
                // Otherwise:
                // 1. Check for whitespace, else check if it's a known token, otherwise, throw error
                currentC = _json_content.at(0);
                if (__is_in_json_const_expr(currentC, constants::JSON_WHITE_SPACES) ) {
                    if (currentC == '\n') {
                        index.nLine++;
                        index.nChar = 0;
                    }
                    _json_content = _json_content.substr(1); // Ignore and increment string
                } else if (__is_in_json_const_expr(currentC, constants::JSON_TOKENS)) {
                    index.nChar++;
                    res.push_back( _createToken(currentC) );
                    _json_content = _json_content.substr(1);
                } else {
                    throw std::runtime_error("Unexpected character : " + std::string{currentC} + "line : ");
                }
            }
            return res;
        }

    } // namespace _lexing
} // namespace liminal_json_io

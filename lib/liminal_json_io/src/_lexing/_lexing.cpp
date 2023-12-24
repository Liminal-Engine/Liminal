#include "_lexing/_lexing.hpp"
#include "constants.hpp"

#include <optional>
#include <stdexcept>
#include <algorithm>

namespace liminal_json_io {
    namespace _lexing {

        static void __update_optional_token(std::optional<_token_t> &token, const char &value) {
            if (token.has_value()) {
                *token += value;
            } else {
                token.emplace(_token_t{value});
            }
        }

        static void __update_optional_token(std::optional<_token_t> &token, const std::string &value) {
            token.emplace(value);
        }

        static std::optional<_token_t> __tryLexingString(const std::string &content) {
            std::string _tmp_content = content;
            std::optional<_token_t> res;

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

        static std::optional<_token_t> __tryLexingNumber(const std::string &content) {
            std::optional<_token_t> res;

            for (const char &c : content) {
                if (
                    std::find(
                        std::begin(constants::JSON_NUM_CHARS),
                        std::end(constants::JSON_NUM_CHARS),
                        c
                    ) != std::end(constants::JSON_NUM_CHARS)
                ) {
                    __update_optional_token(res, c);
                } else {
                    break;
                }
            }
            return res;
        }

        static std::optional<_token_t> __tryLexingBool(const std::string &content) {
            std::optional<_token_t> res;

            std::size_t content_len = content.length();
            if (content_len >= constants::JSON_TRUE_LEN && content.substr(0, constants::JSON_TRUE_LEN - 1) == "true") {
                __update_optional_token(res, "true");
            } else if (content_len >= constants::JSON_FALSE_LEN && content.substr(0, constants::JSON_FALSE_LEN - 1) == "false" ) {
                __update_optional_token(res, "false");
            }
            return res;
        }

        static std::optional<_token_t> __tryLexingNull(const std::string &content) {
            std::optional<_token_t> res;

            if (content.length() >= constants::JSON_NULL_LEN && content.substr(0, constants::JSON_NULL_LEN - 1) == "null") {
                __update_optional_token(res, "null");
            }
            return res;
        }

        _tokens_t _processLexing(const std::string &json_as_string) {
            std::string _json_content = json_as_string;
            _tokens_t res;
            std::optional<_token_t> tmp_token;
        
            while (_json_content.length() > 0) {
                if ( (tmp_token = __tryLexingString(_json_content) ).has_value() ) {
                    res.push_back(tmp_token.value());
                    _json_content = _json_content.substr(tmp_token.value().length() + 2); // + 2 for both commas
                    continue;
                } else if ( (tmp_token = __tryLexingNumber(_json_content)).has_value() ) {
                    res.push_back(tmp_token.value());
                    _json_content = _json_content.substr(tmp_token.value().length());
                    continue;
                } else if ( (tmp_token = __tryLexingBool(_json_content)).has_value() ) {
                    res.push_back(tmp_token.value());
                    _json_content = _json_content.substr(tmp_token.value().length());
                    continue;
                } else if ( (tmp_token = __tryLexingNull(_json_content)).has_value() ) {
                    res.push_back(tmp_token.value());
                    _json_content = _json_content.substr(tmp_token.value().length());
                    continue;
                }

                // Otherwise:
                // 1. Check for whitespace
                if (
                    std::find(
                        std::begin(constants::JSON_WHITE_SPACE),
                        std::end(constants::JSON_WHITE_SPACE),
                        _json_content.at(0)
                    ) != std::end(constants::JSON_WHITE_SPACE)
                ) {
                    _json_content = _json_content.substr(1); // Ignore and increment string
                } else if (
                    std::find(
                        std::begin(constants::JSON_TOKENS),
                        std::end(constants::JSON_TOKENS),
                        _json_content.at(0)
                    ) != std::end(constants::JSON_TOKENS)
                ) {
                    res.push_back( _token_t{_json_content.at(0)}  );
                    _json_content = _json_content.substr(1);
                } else {
                    throw std::runtime_error("Unexpected character : " + std::string{_json_content.at(0)});
                }
            }
            return res;
        }

    } // namespace _lexing
} // namespace liminal_json_io

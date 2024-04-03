/**
 * @file string.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-25
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "string.hpp"

#include <stdexcept>
#include <cerrno>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <string>
#include <numeric>
#include <sstream>

namespace parser {
    namespace string {

        bool isPositiveInteger(const std::string &str) {
            return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
        }
        
        bool isBool(const std::string &str, const bool &include_nb) {
            if (str.empty()) {
                return false;
            }
            if (include_nb) {
                return str == "false" || str == "true" || isPositiveInteger(str);
            } else {
                return str == "false" || str == "true";
            }
        }

        bool toBool(
            const std::string &str,
            const bool &include_nb
        ) {
            if (!isBool(str, include_nb)) return false;
            if (include_nb) {
                if (isOnlyChar(str, '0')) return false;
                if (isPositiveInteger(str)) return true;
            }
            if (str == "false") return false;
            if (str == "true") return true;
            return false;
        }

        bool contains(const std::string &str, const char &c) {
            return str.find(c) != std::string::npos;
        }

        bool contains(const std::string &str, const std::string &subStr) {
            return str.find(subStr) != std::string::npos;
        }

        bool isOnlyChar(const std::string &str, const char &c) {
            return std::all_of(str.begin(), str.end(), [&c](char ch) { return ch == c; });
        }

        intmax_t toIntMax(const std::string &str) {
            if (isOnlyChar(str, '0')) return (intmax_t)0;
            return (intmax_t)std::stol(str);
        }

        long double toLongDouble(const std::string &str) {
            if (isOnlyChar(str, '0')) return (long double)0;

            return std::stold(str);
        }

        std::size_t toSize_t(const std::string &str) {
            if (isOnlyChar(str, '0')) return (std::size_t)0;

            return std::stoul(str);
        }

        std::size_t getNOccurences(const std::string &str, const char &c) {
            return std::count(str.begin(), str.end(), c);
        }

        std::size_t getNOccurences(const std::string &str, const std::string &occurence) {
            if (occurence == "") return str == "" ? 1 : 0;
            std::size_t res{0};
            std::size_t pos{0};

            while ( (pos = str.find(occurence, pos)) != std::string::npos) {
                ++res;
                pos += occurence.length();
            }
            return res;
        }

        std::size_t lastIndexOf(const std::string &str, const char &c) {
            return str.rfind(c);
        }


        /**
         * @brief 
         * 
         * @warning DELIMITERS ARE GIVEN BY ORDER OF IMPORTANCE // TODO : document this
         * @param input 
         * @param delimiters 
         * @param includeDelimiter 
         * @return std::vector<std::string> 
         */
        // TODO : tokenize ne convient toujours pas,
        // il ne faut pas qu'il fasse de priorisation sur les separators mais qu'il les traite tous à égalité
        
        std::vector<std::string> tokenize(
            const std::string &input,
            const std::vector<std::string> &delimiters,
            const bool &includeDelimiter
        ) {
            std::size_t currentPos{0};
            std::vector<std::string> res{};
            std::string nextToken{};
            using delim_t = std::pair<std::string, std::size_t>;
            auto delimIsEmpty = [](const delim_t &delim) -> bool { return delim.first.empty() && delim.second == std::string::npos; };
            auto initDelim = [](void) -> delim_t { return delim_t{"", std::string::npos}; };
            delim_t nextDelim = initDelim();
            auto getNextDelim = [&initDelim, &delimIsEmpty, &currentPos, &input, &delimiters]() -> delim_t {
                delim_t res = initDelim();
                std::size_t tmp{std::string::npos};

                for (const std::string &delim : delimiters) {
                    tmp = input.find(delim, currentPos);
                    if (tmp != std::string::npos && (delimIsEmpty(res) || tmp < res.second)) {
                        res.first = delim;
                        res.second = tmp;
                    }
                }
                return res;
            };
            auto produceNextToken = [&input, &currentPos, &nextDelim]() -> std::string { return input.substr(currentPos, nextDelim.second - currentPos); };

            while (currentPos < input.size()) {
                if (delimIsEmpty(nextDelim = getNextDelim())) break;
                nextToken = produceNextToken();
                if (!nextToken.empty()) res.push_back(nextToken);
                if (includeDelimiter) res.push_back(nextDelim.first);
                currentPos = nextDelim.second + nextDelim.first.size();
            }
            if (currentPos < input.size() || input.empty()) res.push_back(input.substr(currentPos, input.size() - currentPos)); // add last token
            return res;
        }

        std::vector<std::string> tokenize(
            const std::string &input,
            const std::string &delimiter,
            const bool &includeDelimiter
        ) {
            return tokenize(input, std::vector<std::string>{delimiter}, includeDelimiter);
        }

        std::vector<std::string> tokenize(
            const std::string &input,
            const char &delimiter,
            const bool &includeDelimiter
        ) {
            return tokenize(input, std::vector<std::string>{std::string{delimiter}}, includeDelimiter);
        }

        std::string eraseAll(const std::string &input, const std::vector<std::string> &subStrs) {
            std::string _inputCpy = input;
            std::vector<std::string> _subStrsCpy = subStrs;
            
            std::sort(_subStrsCpy.begin(), _subStrsCpy.end(),
            [](const std::string& a, const std::string& b) {
                return a.length() > b.length();
            });

            // Erase substrings from the input string
            for (const std::string &subStr : _subStrsCpy) {
                if (subStr != "") {
                    size_t pos;
                    while ((pos = _inputCpy.find(subStr)) != std::string::npos) {
                        _inputCpy.erase(pos, subStr.length());
                    }
                }
            }
            return _inputCpy;
        }

        std::string eraseAll(const std::string &input, const std::string &substr) {
            return eraseAll(input, std::vector{substr});
        }

        std::string trimBegin(const std::string &input, const std::vector<char> &charsToTrim) {
            if (input.empty())
                return input;
            std::size_t firstValidPos = input.find_first_not_of(
                std::string{charsToTrim.begin(), charsToTrim.end()}.c_str()
            );
            if (firstValidPos == std::string::npos)
                return "";
            return input.substr(firstValidPos);
        }

        std::string trimBegin(const std::string &input, const std::string &charsToTrim) {
            return trimBegin(input, std::vector<char>(charsToTrim.begin(), charsToTrim.end()));
        }

        std::string trimBegin(const std::string &input, const std::vector<std::string> &stringsToTrim) {
                std::string result = input;
                for (const std::string &trimString : stringsToTrim) {
                    while (result.substr(0, trimString.length()) == trimString) {
                        result.erase(0, trimString.length());
                    }
                }
                return result;
        }

        std::string trimBegin(const std::string &input, const char &charToTrim) {
            return trimBegin(input, std::vector<char>{charToTrim});
        }

        std::string trimEnd(const std::string &input, const std::vector<char> &charsToTrim) {
            if (input.empty())
                return input;
            std::size_t lastValidPos = input.find_last_not_of(
                std::string{charsToTrim.begin(), charsToTrim.end()}.c_str(),
                input.size()
            );
            if (lastValidPos == std::string::npos)
                return "";
            return input.substr(0, lastValidPos + 1);
        }

        std::string trimEnd(const std::string &input, const std::string &charsToTrim) {
            return trimEnd(input, std::vector<char>(charsToTrim.begin(), charsToTrim.end()));
        }

        std::string trimEnd(const std::string &input, const std::vector<std::string> &stringsToTrim) {
            std::string result = input;
            for (const std::string &trimString : stringsToTrim) {
                while (result.length() >= trimString.length() && result.substr(result.length() - trimString.length()) == trimString) {
                    result.erase(result.length() - trimString.length());
                }
            }
            return result;
        }

        std::string trimEnd(const std::string &input, const char &charToTrim) {
            return trimEnd(input, std::vector<char>{charToTrim});
        }

        std::string trim(const std::string &input, const std::vector<char> &charsToTrim) {
            return trimEnd( trimBegin(input, charsToTrim), charsToTrim );
        }

        std::string trim(const std::string &input, const std::string &charsToTrim) {
            return trim(input, std::vector<char>(charsToTrim.begin(), charsToTrim.end()));
        }

        std::string trim(const std::string &input, const std::vector<std::string> &stringsToTrim) {
            return trimEnd( trimBegin(input, stringsToTrim), stringsToTrim );
        }

        std::string trim(const std::string &input, const char &charToTrim) {
            return trim(input, std::vector<char>{charToTrim});
        }
    
        std::string join(const std::vector<std::string> &input, const std::string &separator) {
            if (input.empty()) return "";
            if (separator.empty()) {
                std::string res{};
                for (const std::string &elem : input) res += elem;
                return res;
            }
            std::ostringstream oss;
            std::copy(input.begin(), input.end() - 1, std::ostream_iterator<std::string>(oss, separator.c_str()));
            oss << input.back(); // Add last elem
            return oss.str();
        }

        std::string join(const std::vector<std::string> &input, const char &separator) {
            return join(input, std::string(1, separator));
        }

    } // namespace string
} // namespace parser




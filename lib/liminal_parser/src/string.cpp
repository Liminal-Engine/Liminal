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
namespace liminal_parser {
    namespace string {

        bool isNonNegativeInteger(const std::string &str) {
            return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
        }
        
        bool isBool(const std::string &str, const bool &include_nb) {
            if (str.empty()) {
                return false;
            }
            if (include_nb) {
                return str == "false" || str == "true" || isNonNegativeInteger(str);
            } else {
                return str == "false" || str == "true";
            }
        }

        bool toBool(
            const std::string &str,
            const bool &include_nb,
            const bool &throw_error
        ) {
            if (!isBool(str, include_nb)) {
                throw std::runtime_error("String cannot be converted to bool. Received : " + str);
            }
            if (include_nb) {
                if (isOnlyChar(str, '0')) return false;
                if (isNonNegativeInteger(str)) return true;
                if (throw_error) throw std::runtime_error("Error in toBool");
            }
            if (str == "false") return false;
            if (str == "true") return true;
            if (throw_error) throw std::runtime_error("Error in toBool");
            return false;
        }

        bool contains(const std::string &str, const char &c) {
            return str.find(c) != std::string::npos;
        }

        bool contains(const std::string &str, const std::string &subStr) {
            return str.find(subStr) != std::string::npos;
        }

        inline bool isOnlyChar(const std::string &str, const char &c) {
            return std::all_of(str.begin(), str.end(), [&c](char ch) { return ch == c; });
        }

        intmax_t toIntMax(const std::string &str, const bool &throw_error) {
            if (isOnlyChar(str, '0')) return (intmax_t)0;

            if (throw_error) {
                try {
                    return (intmax_t)std::stol(str);
                } catch (std::invalid_argument const& ex)
                {
                    std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
                    throw std::runtime_error("");
                }
                catch (std::out_of_range const& ex)
                {
                    std::size_t pos{};

                    std::cout << "std::out_of_range::what(): " << ex.what() << '\n';
                    const long long ll{std::stoll(str, &pos)};
                    std::cout << "std::stoll(" << std::quoted(str) << "): " << ll
                            << "; pos: " << pos << '\n';
                    throw std::runtime_error("");
                }
            }
            return (intmax_t)std::stol(str);
        }

        long double toLongDouble(const std::string &str, const bool &throwError) {
            if (isOnlyChar(str, '0')) return (long double)0;

            if (throwError) {
                try {
                    return std::stold(str);
                } catch (std::invalid_argument const& ex) {
                    std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
                    throw std::runtime_error("");
                } catch (std::out_of_range const& ex) {
                    std::cout << "std::out_of_range::what(): " << ex.what() << '\n';
                    throw std::runtime_error("");
                }
            }
            return std::stold(str);
        }

        std::size_t toSize_t(const std::string &str, const bool &throwError) {
            if (isOnlyChar(str, '0')) return (std::size_t)0;

            if (throwError) {
                try {
                    return std::stoul(str);
                } catch (std::invalid_argument const& ex) {
                    std::cout << "std::invalid_argument::what(): " << ex.what() << '\n';
                    throw std::runtime_error("");
                } catch (std::out_of_range const& ex) {
                    std::cout << "std::out_of_range::what(): " << ex.what() << '\n';
                    throw std::runtime_error("");
                }
            }
            return std::stoul(str);
        }

        std::size_t getOccurences(const std::string &str, const char &c) {
            return std::count(str.begin(), str.end(), c);
        }

        std::size_t getOccurences(const std::string &str, const std::string &occurence) {
            std::size_t res{0};
            std::size_t pos{0};

            while ( (pos = str.find(occurence, pos)) != std::string::npos) {
                ++res;
                pos += occurence.length();
            }
            return res;
        }

        std::size_t lastIndexOf(const std::string &str, const char &c, const bool &throwError) {
            if (throwError) {
                std::size_t res = str.rfind(c);

                if (res == std::string::npos) {
                    throw std::runtime_error("Failed to find the given character in string in lastIndexOf");
                }
                return res;
            }
            return str.rfind(c);
        }




    std::vector<std::string> tokenize(
        const std::string &input,
        const std::vector<std::string> &delimiters,
        const bool &includeDelimiter
    ) {
        std::vector<std::string> res;
        size_t startPos = 0;
        size_t foundPos;
        std::string tmpStr{};

        while (startPos < input.length()) {
            foundPos = std::string::npos;
            // Find the next occurrence of any delimiter
            for (const auto &delimiter : delimiters) {
                size_t pos = input.find(delimiter, startPos);
                if (pos != std::string::npos && (foundPos == std::string::npos || pos < foundPos)) {
                    foundPos = pos;
                }
            }
            // If no delimiter is found, break out of the loop
            if (foundPos == std::string::npos) {
                break;
            }
            // Extract the token and add it to the vector
            if ((tmpStr = input.substr(startPos, foundPos - startPos)).empty() == false) {
                res.push_back(tmpStr);
            }
            if (includeDelimiter) {
                res.push_back(input.substr(foundPos, 1)); // Include the delimiter
            }
            startPos = foundPos + 1; // Move to the next character after the delimiter
        }
        // Add the last token if there is any remaining text
        if (startPos < input.length()) {
            res.push_back(input.substr(startPos));
        }
        return res;
    }

        std::vector<std::string> tokenize(
            const std::string &input,
            const std::string &delimiter,
            const bool &includeDelimiter
        ) {
            return tokenize(input, std::vector<std::string>{delimiter}, includeDelimiter);
        }

        std::vector<std::string> tokensize(
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
                size_t pos;
                while ((pos = _inputCpy.find(subStr)) != std::string::npos) {
                    _inputCpy.erase(pos, subStr.length());
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
            std::size_t firstValidPos = input.find_first_not_of(charsToTrim.data(), 0);
            if (firstValidPos == std::string::npos)
                return "";
            return input.substr(firstValidPos);
        }

        std::string trimBegin(const std::string &input, const std::string &charsToTrim) {
            return trimBegin(input, std::vector<char>(charsToTrim.begin(), charsToTrim.end()));
        }

        std::string trimBegin(const std::string &input, const std::vector<std::string> &stringsToTrim) {
            return trimBegin(input, std::accumulate(stringsToTrim.begin(), stringsToTrim.end(), std::string()));
        }

        std::string trimBegin(const std::string &input, const char &charToTrim) {
            return trimBegin(input, std::vector<char>{charToTrim});
        }

        std::string trimEnd(const std::string &input, const std::vector<char> &charsToTrim) {
            if (input.empty())
                return input;
            std::size_t lastValidPos = input.find_last_not_of(charsToTrim.data(), input.size());
            if (lastValidPos == std::string::npos)
                return "";
            return input.substr(0, lastValidPos + 1);
        }

        std::string trimEnd(const std::string &input, const std::string &charsToTrim) {
            return trimEnd(input, std::vector<char>(charsToTrim.begin(), charsToTrim.end()));
        }

        std::string trimEnd(const std::string &input, const std::vector<std::string> &stringsToTrim) {
            return trimEnd(input, std::accumulate(stringsToTrim.begin(), stringsToTrim.end(), std::string()));
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
            return trim(input, std::accumulate(stringsToTrim.begin(), stringsToTrim.end(), std::string()));
        }

        std::string trim(const std::string &input, const char &charToTrim) {
            return trim(input, std::vector<char>{charToTrim});
        }
    
    } // namespace string
} // namespace liminal_parser




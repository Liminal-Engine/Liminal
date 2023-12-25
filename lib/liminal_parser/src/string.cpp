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
    
    } // namespace string
} // namespace liminal_parser




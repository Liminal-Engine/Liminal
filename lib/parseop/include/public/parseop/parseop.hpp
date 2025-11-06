/**
 * @file string.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-25
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef _LIMINAL_LIB_PARSEOP_HPP_
#define _LIMINAL_LIB_PARSEOP_HPP_

#include <string>
#include <cstdint>
#include <vector>

namespace parseop {

    bool isPositiveInteger(const std::string &str);
    
    bool isBool(const std::string &str, const bool &include_nb = false);

    bool toBool(
        const std::string &str,
        const bool &include_nb = false
    );

    bool includes(const std::string &input, const char &c);
    bool includes(const std::string &input, const std::vector<char> &chars);
    bool includes(const std::string &input, const std::string &subStr);
    bool includes(const std::string &input, const std::vector<std::string> &strs);

    bool isOnlyChar(const std::string &str, const char &c);
    bool isPositiveInteger(const std::string &str);
    long int toLongInt(const std::string &str);
    long long int toLongLongInt(const std::string &str);

    long double toLongDouble(const std::string &str);
    std::size_t toSize_t(const std::string &str);

    std::size_t getNOccurences(const std::string &str, const char &c);
    std::size_t getNOccurences(const std::string &str, const std::string &occurence);
    std::size_t lastIndexOf(const std::string &str, const char &c);
    
    std::vector<std::string> tokenize(
        const std::string &input,
        const std::vector<std::string> &delimiters,
        const bool &includeDelimiters = false
    );
    std::vector<std::string> tokenize(
        const std::string &input,
        const std::string &delimiter,
        const bool &includeDelimiters = false
    );
    std::vector<std::string> tokenize(
        const std::string &input,
        const char &delimiter,
        const bool &includeDelimiter = false
    );  

    std::string eraseAll(const std::string &input, const std::vector<std::string> &subStrs);
    std::string eraseAll(const std::string &input, const std::string &substr);

    std::string trimBegin(const std::string &input, const std::vector<char> &charsToTrim = std::vector<char> {' '});
    std::string trimBegin(const std::string &input, const std::string &charsToTrim = std::string{" "});
    std::string trimBegin(const std::string &input, const std::vector<std::string> &stringsToTrim = std::vector<std::string>{" "});
    std::string trimBegin(const std::string &input, const char &charToTrim = ' ');

    std::string trimEnd(const std::string &input, const std::vector<char> &charsToTrim = std::vector<char> {' '});
    std::string trimEnd(const std::string &input, const std::string &charsToTrim = std::string{" "});
    std::string trimEnd(const std::string &input, const std::vector<std::string> &stringsToTrim = std::vector<std::string>{" "});
    std::string trimEnd(const std::string &input, const char &charToTrim = ' ');

    std::string trim(const std::string &input, const std::vector<char> &charsToTrim = std::vector<char> {' '});
    std::string trim(const std::string &input, const std::string &charsToTrim = std::string{" "});
    std::string trim(const std::string &input, const std::vector<std::string> &stringsToTrim = std::vector<std::string>{" "});
    std::string trim(const std::string &input, const char &charToTrim = ' ');

    std::string join(const std::vector<std::string> &input, const std::string &separator = "");
    std::string join(const std::vector<std::string> &input, const char &separator);

    bool startsWith(const std::string &input, const std::string &target);
    bool endsWith(const std::string &input, const std::string &target);

    std::string replace(const std::string &input, const std::string &target, const std::string &replacement, const std::size_t &nOccurence = 0);
    std::string replace(const std::string &input, const std::vector<std::string> &targets, const std::string &replacement, const std::size_t &nOccurence = 0);

    bool containsAll(const std::vector<std::string> &superset, const std::vector<std::string> &subset);

    std::string prettify(const std::vector<std::string> &input, const std::string &bulletPoint = "-");

    std::vector<const char *> toCStrVector(const std::vector<std::string> &input);
} // namespace parseop


#endif // _LIMINAL_LIB_PARSEOP_HPP_
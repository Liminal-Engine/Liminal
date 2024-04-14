/**
 * @file tokenize.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <vector>
#include <string>

namespace parseop {
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
} // namespace parseop

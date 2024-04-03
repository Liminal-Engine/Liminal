#include <string>
#include <vector>
#include <iostream>
#include <utility>
// std::vector<std::string> tokenize(
//     const std::string &input,
//     const std::vector<std::string> &delimiters,
//     const bool &includeDelimiter
// ) {
//     std::size_t delimFoundPos{std::string::npos};
//     std::size_t currentPos{0};
//     std::vector<std::string> res{};
//     std::string tmpToken{};

//     for (std::size_t delimI = 0; delimI < delimiters.size(); delimI++) {
//         std::string delimiter{delimiters.at(delimI)};
//         if ( (delimFoundPos = input.find(delimiters.at(delimI), currentPos)) != std::string::npos ) { // if delimiter is found :
//             if (delimFoundPos > currentPos) {
//                 res.push_back(input.substr(currentPos, delimFoundPos - currentPos));
//             }
//             if (includeDelimiter) res.push_back(delimiter);
//             currentPos = delimFoundPos + delimiters.at(delimI).size();
//             delimI = -1; // reset delimiter list
//         }
//     }
//     if (currentPos < input.size()) {
//         res.push_back(input.substr(currentPos));
//     }
//     return res;
// }

// fonction lambda qui trouve le premier prochain delimiter parmis tous les delimiteurs
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


void show(const std::vector<std::string> &vec) {
    if (vec.empty()) std::cout << "vec is empty" << std::endl;
    else {
        for (std::size_t i = 0; i < vec.size(); i++) {
            std::cout << i << " -> " << vec.at(i) << std::endl;
        }
    }
}

int main() {
    std::string input{"/home/user/documents"};
    std::vector<std::string> delimiters{"/", "o"};
    show(
        tokenize(
            input,
            delimiters,
            true
        )
    );

    // std::cout << "-----------------------------------------" << std::endl;
    // show(
    //     tokenizeOriginal(
    //         input,
    //         delimiters,
    //         true
    //     )
    // );
}
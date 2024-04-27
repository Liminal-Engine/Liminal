/**
 * @file replaceAll.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-19
 * 
 * @copyright Copyright (c) 2024
 * 
*/


#include <string>
#include <vector>

namespace parseop {

    std::string replace(
        const std::string &input,
        const std::string &target,
        const std::string &replacement,
        const std::size_t &nOccurence
    ) {
        std::string res = input;
        std::size_t pos = 0;
        std::size_t occurence = 0;

        while ( (pos = res.find(target, pos)) != std::string::npos ) {
            res.replace(pos, target.length(), replacement);
            pos += replacement.length();
            if (nOccurence > 0 && ++occurence >= nOccurence) return res;
        }
        return res;
    }

    std::string replace(
        const std::string &input,
        const std::vector<std::string> &targets,
        const std::string &replacement,
        const std::size_t &nOccurence
    ) {
        std::string res = input;
        std::size_t pos = 0;
        std::size_t occurence = 0;

        for (const std::string &target : targets) {
            while ( (pos = res.find(target, pos)) != std::string::npos ) {
                res.replace(pos, target.length(), replacement);
                pos += replacement.length();
                if (nOccurence > 0 && ++occurence >= nOccurence) return res;
            }
        }
        return res;
    }

} // namespace parseop



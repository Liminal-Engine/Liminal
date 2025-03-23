/**
 * @file Helper.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "test/jsonio/Array/Helper.hpp"

#include <jsonio/InJson.hpp>

#include <stdexcept>
#include <iostream>

namespace test {
    namespace jsonio {
        namespace Array {

            std::vector<::jsonio::types::Array_t> Helper::create(
                const ::fs::Path &path,
                const std::string &jsonPath,
                const std::array<std::string, 3> &separators
            ) {
                ::jsonio::InJson inJson;
                inJson.parse(path);
                std::vector<::jsonio::types::Array_t> res{};
                
                res.push_back(inJson.get<::jsonio::types::Array_t>(jsonPath, separators).value());
                ::jsonio::types::Array_t fromCopyConstructor(res.at(0));
                ::jsonio::types::Array_t fromEqualOperator = fromCopyConstructor;
                res.push_back(fromCopyConstructor);
                res.push_back(fromEqualOperator);
                return res;
            }
        } // namespace Array
    } // namespace jsonio
} // namespace test
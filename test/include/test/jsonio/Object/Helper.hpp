/**
 * @file Helper.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-09
 * 
 * @copyright Copyright (c) 2024
* 
*/

#ifndef LIMINAL_TEST_JSONIO_OBJECT_HELPER_HPP_
#define LIMINAL_TEST_JSONIO_OBJECT_HELPER_HPP_

#include <jsonio/types.hpp>
#include <jsonio/InJson.hpp>

#include <fs/Path.hpp>

#include <vector>
#include <string>


namespace test {
    namespace jsonio {
        namespace Object {
            class Helper {
                public:

                static std::vector<::jsonio::types::Object_t> create(
                    const ::fs::Path &path,
                    const std::string &jsonPath,
                    const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS
                );

            };
        } // namespace Object
    } // namespace jsonio
} // namespace test

#endif // LIMINAL_TEST_JSONIO_OBJECT_HELPER_HPP_


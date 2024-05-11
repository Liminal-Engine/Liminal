/**
 * @file Helper.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef LIMINAL_TEST_FS_INFILE_HELPER_HPP_
#define LIMINAL_TEST_FS_INFILE_HELPER_HPP_

#include <fs/Path.hpp>

#include <string>

namespace test {
    namespace fs {
        namespace InFile {
            class Helper {
                public:

                static const std::string JSON_INVALID_ARRAY_WRONG_FORMAT;
                static const std::string JSON_INVALID_BOOL_INCOMPLETE;
                static const std::string JSON_VALID_BASIC;
                static const std::string JSON_VALID_EDGE_CASES;
                static const std::string JSON_VALID_LARGE;
                static const std::string JSON_VALID_NESTED;
                static const std::string SPECIAL_CHARS;
                static const std::string HIDDEN;

                static std::string getCPPStyledContent(const ::fs::Path &path);
                
            };
        } // namespace InFile
    } // namespace fs
} // namespace test

#endif // LIMINAL_TEST_FS_INFILE_HELPER_HPP_

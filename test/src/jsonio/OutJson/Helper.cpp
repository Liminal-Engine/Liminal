/**
 * @file Helper.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "test/jsonio/OutJson/Helper.hpp"
#include "test/Helper.hpp"

#include <fstream>
#include <filesystem>
#include <iterator>
#include <string>

namespace test {
    namespace jsonio {
        namespace OutJson {
            std::string Helper::removeQuotes(const std::string &str) {
                std::string res = str;
                res.erase(std::remove(res.begin(), res.end(), '\"'), res.end());
                return res;
            }

            ::fs::Path Helper::generateTmpOutputPath(void) { 
                return ::fs::Path("../../test/assets//tmp_json/" + ::test::Helper::generateUID() + ".json");
            }

            bool Helper::filesAreEqual(const ::fs::Path & path1, const ::fs::Path &path2) {
                std::ifstream f1(path1.asStr(), std::ifstream::binary | std::ifstream::ate);
                std::ifstream f2(path2.asStr(), std::ifstream::binary | std::ifstream::ate);
            
                if (f1.fail() || f2.fail()) {
                    return false; // File problem
                }
            
                if (f1.tellg() != f2.tellg()) {
                    return false; // Different sizes
                }
            
                // Seek back to beginning and use std::equal to compare contents
                f1.seekg(0, std::ifstream::beg);
                f2.seekg(0, std::ifstream::beg);
                return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                                  std::istreambuf_iterator<char>(),
                                  std::istreambuf_iterator<char>(f2.rdbuf()));
            }

        } // OutJson
    } // namespace jsonio
} // namespace test

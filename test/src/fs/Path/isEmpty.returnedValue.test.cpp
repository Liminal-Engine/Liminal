/**
 * @file isEmpty.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-06
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <fs/Path.hpp>

#include "test/fs/Path/Helper.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <tuple>
#include <string>
#include <utility>
#include <optional>
#include <filesystem>

namespace test {
    namespace fs {
        namespace Path {
            using FSPathIsEmptyParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                bool // expected returned result
            >;
            class FSPathIsEmpty : public ::testing::TestWithParam<FSPathIsEmptyParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathIsEmpty(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathIsEmpty, ReturnGivenStatus) {
                std::size_t expectedIsEmpty = std::get<1>(GetParam());

                for (::fs::Path &instance : _instances)
                    EXPECT_EQ(instance.isEmpty(), expectedIsEmpty);
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingStatusOk,
                FSPathIsEmpty,
                testing::Values(
                    std::make_tuple("../../tests/assets", false),
                    std::make_tuple(std::nullopt, true),
                    std::make_tuple("/tmp", false),
                    std::make_tuple("/aaa/bbb", false),
                    std::make_tuple("/tmp_oojopjop99---/bbb", false),
                    std::make_tuple("/tmp/complex-dir-name", false),
                    std::make_tuple("/path/to/directory", false),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", false),
                    std::make_tuple("/path/to/directory", false),
                    std::make_tuple("./var/log", false),
                    std::make_tuple("./../usr/share", false),
                    std::make_tuple("../lib/modules", false),
                    std::make_tuple("srv/http", false),
                    std::make_tuple("/usr/\x10/local/bin", false),
                    std::make_tuple("/usr/" + std::string(1000, 'a') + "/bin", false),
                    std::make_tuple("\\usr\\local\\bin\\.\\..\\lib", false),
                    std::make_tuple("/usr/local/bin\\file", false),
                    std::make_tuple("/usr/local/漢字/文件.txt", false),
                    std::make_tuple("/usr/local/My Documents/My File.txt", false),
                    std::make_tuple("//////", false),
                    std::make_tuple("........", false),
                    std::make_tuple("////usr/local/bin", false),
                    std::make_tuple("/usr/local/bin/////", false),
                    std::make_tuple("////usr/local/bin/////", false),
                    std::make_tuple("", true),
                    std::make_tuple("../../tests/assets/fs/.hidden", false),
                    std::make_tuple("./I/DO/no/exists", false),
                    std::make_tuple("/path/to/non_empty_file.txt", false),
                    std::make_tuple("/path/to/non_empty_dir", false),
                    std::make_tuple("/path/to/non_empty_dir/", false),
                    std::make_tuple("./", false),
                    std::make_tuple(".", false),
                    std::make_tuple("..", false),
                    std::make_tuple(".3/", false)

                    
                )
            );
        }
    }
}
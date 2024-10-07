/**
 * @file getNEntry.test.cpp
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
            using FSPathGetNEntryParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                std::size_t //  expected return status
            >;
            class FSPathGetNEntry : public ::testing::TestWithParam<FSPathGetNEntryParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathGetNEntry(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathGetNEntry, ReturnGivenStatus) {
                std::size_t expectedNEntry = std::get<1>(GetParam());

                for (::fs::Path &instance : _instances)
                    EXPECT_EQ(instance.getNEntry(), expectedNEntry);
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingStatusOk,
                FSPathGetNEntry,
                testing::Values(
                    std::make_tuple("../../tests/assets", 4),
                    std::make_tuple(std::nullopt, 0),
                    std::make_tuple("/tmp_fs", 1),
                    std::make_tuple("/aaa/bbb", 2),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", 2),
                    std::make_tuple("/tmp_fs/complex-dir-name", 2),
                    std::make_tuple("/path/to/directory", 3),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", 10),
                    std::make_tuple("/path/to/directory", 3),
                    std::make_tuple("./var/log", 3),
                    std::make_tuple("./../usr/share", 4),
                    std::make_tuple("../lib/modules", 3),
                    std::make_tuple("srv/http", 2),
                    std::make_tuple("/usr/\x10/local/bin", 4),
                    std::make_tuple("/usr/" + std::string(1000, 'a') + "/bin", 3),
                    std::make_tuple("\\usr\\local\\bin\\.\\..\\lib", 1),
                    std::make_tuple("/usr/local/bin\\file", 3),
                    std::make_tuple("/usr/local/漢字/文件.txt", 4),
                    std::make_tuple("/usr/local/My Documents/My File.txt", 4),
                    std::make_tuple("//////", 1),
                    std::make_tuple("........", 1),
                    std::make_tuple("////usr/local/bin", 3),
                    std::make_tuple("/usr/local/bin/////", 3),
                    std::make_tuple("////usr/local/bin/////", 3),
                    std::make_tuple("", 0)

                    
                )
            );
        }
    }
}
/**
 * @file getResolution.test.cpp
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
            using FSPathGetResolutionParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                ::fs::Path::Resolution // expected returned result
            >;
            class FSPathGetResolution : public ::testing::TestWithParam<FSPathGetResolutionParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathGetResolution(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathGetResolution, ReturnGivenStatus) {
                ::fs::Path::Resolution expectedResolution = std::get<1>(GetParam());

                for (::fs::Path &instance : _instances)
                    EXPECT_EQ(instance.getResolution(), expectedResolution);
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingStatusOk,
                FSPathGetResolution,
                testing::Values(
                    std::make_tuple("../../tests/assets", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple(std::nullopt, ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("/tmp_fs", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/aaa/bbb", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/tmp_fs/complex-dir-name", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/path/to/directory", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/path/to/directory", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("./var/log", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("./../usr/share", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("../lib/modules", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("srv/http", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("/usr/\x10/local/bin", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/usr/" + std::string(1000, 'a') + "/bin", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("\\usr\\local\\bin\\.\\..\\lib", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("/usr/local/bin\\file", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/usr/local/漢字/文件.txt", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/usr/local/My Documents/My File.txt", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("//////", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("........", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("////usr/local/bin", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/usr/local/bin/////", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("////usr/local/bin/////", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("../../tests/assets/fs/.hidden", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("./I/DO/no/exists", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("/path/to/non_empty_file.txt", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/path/to/non_empty_dir", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/path/to/non_empty_dir/", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("./", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple(".", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("..", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple(".3/", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("../../tests/assets/fs/.hidden", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("../../tests/assets/fs/.hidden", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("./I/DO/no/exists", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("/path/to/non_empty_file.txt", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/a/b/c/d/e/f/g/h", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("..////.//a/b/c/d/e/f/g/h", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("..////.//a/b/c/d/e/f/g/h", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("/", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("..", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("../..", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("/rootfile.txt", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/path/with spaces/file.txt", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/path/with!@#$%^&*()_+special/file.txt", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/path/with/trailing/slashes////", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("/path/with\\mixed/separators", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("//path//with//consecutive//slashes", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple(".", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("..", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("...", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("....", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("././././.", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("./. . /./ . ", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("TEST123", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("KODEROZP", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("/path/with/very/long/name/that/exceeds/system/limits", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("./path/with!@#$%^&*()_+special/characters", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("./path/with spaces", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("./.", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("../.", ::fs::Path::Resolution::RELATIVE),
                    std::make_tuple("//", ::fs::Path::Resolution::ABSOLUTE),
                    std::make_tuple("//.", ::fs::Path::Resolution::ABSOLUTE)
                )
            );
        }
    }
}
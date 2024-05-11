/**
 * @file toRelative.newPath.test.cpp
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
            using FSPathToRelativeNewPathParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                ::fs::Path // expected new path
            >;
            class FSPathToRelativeNewPath : public ::testing::TestWithParam<FSPathToRelativeNewPathParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathToRelativeNewPath(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathToRelativeNewPath, ReturnGivenStatus) {
                ::fs::Path expectedNewPath = std::get<1>(GetParam());


                for (::fs::Path &instance : _instances) {
                    instance.toRelative();
                    EXPECT_EQ(instance, expectedNewPath);
                }
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenVariousPath,
                FSPathToRelativeNewPath,
                testing::Values(
                    std::make_tuple(std::filesystem::current_path().string() + "/bin", ::fs::Path("./bin")),
                    std::make_tuple(std::filesystem::current_path().string() + "/bin", ::fs::Path("bin")),
                    std::make_tuple(std::filesystem::current_path().string() + "/./bin", ::fs::Path("./bin")),
                    std::make_tuple(std::filesystem::current_path().string() + "/./bin", ::fs::Path("bin")),
                    std::make_tuple(std::filesystem::current_path().string() + "/////.//a/b/c/d/e/f/g/h", ::fs::Path(".//a/b/c/d/e/f/g/h")),
                    std::make_tuple(std::filesystem::current_path().string() + "/////.//a/b/c/d/e/f/g/h", ::fs::Path("a/b/c/d/e/f/g/h")),
                    std::make_tuple(std::filesystem::current_path().string() + "/./////.//a/b/c/d/e/f/g/h", ::fs::Path(".//a/b/c/d/e/f/g/h")),
                    std::make_tuple(std::filesystem::current_path().string() + "/./////.//a/b/c/d/e/f/g/h", ::fs::Path("a/b/c/d/e/f/g/h")),
                    std::make_tuple(std::filesystem::current_path().string(), ::fs::Path(".")),
                    std::make_tuple(std::filesystem::current_path().string(), ::fs::Path("./")),
                    std::make_tuple(std::filesystem::current_path().string() + "/../../.test123/789.abc", ::fs::Path("./../../.test123/789.abc")),
                    std::make_tuple(std::filesystem::current_path().string() + "/../../.test123/789.abc", ::fs::Path("../../.test123/789.abc")),
                    std::make_tuple("/home/matteo/Projects/Liminal/tests/assets/fs", ::fs::Path("../../tests/assets/fs/")),
                    std::make_tuple(Helper::createCleanedStrPath(std::filesystem::current_path().string() + "/../../tests/assets/fs/"), ::fs::Path("../../tests/assets/fs/")),
                    std::make_tuple(Helper::createCleanedStrPath(std::filesystem::current_path().string() + "/../aaa/b b.j/-n--$h/."), ::fs::Path("../aaa/b b.j/-n--$h/.")),
                    std::make_tuple(std::filesystem::current_path().string() + "//bin", ::fs::Path("./bin")),
                    std::make_tuple(std::filesystem::current_path().string() + "/././bin", ::fs::Path("./bin")),
                    std::make_tuple(std::filesystem::current_path().string() + "/../../bin", ::fs::Path("../../bin")),
                    std::make_tuple(std::filesystem::current_path().string() + "/bin$#@", ::fs::Path("./bin$#@")),
                    std::make_tuple(std::filesystem::current_path().string() + "/bin folder", ::fs::Path("./bin folder")),
                    std::make_tuple(std::filesystem::current_path().string() + "/bin📁", ::fs::Path("./bin📁")),
                    std::make_tuple(std::filesystem::current_path().string() + "/../", ::fs::Path("..")),
                    std::make_tuple("", ::fs::Path()),
                    std::make_tuple(std::nullopt, ::fs::Path())
                )
            );
        }
    }
}
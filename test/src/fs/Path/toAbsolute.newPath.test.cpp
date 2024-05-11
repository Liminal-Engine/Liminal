/**
 * @file toAbsolute.newPath.test.cpp
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
            using FSPathToAbsoluteNewPathParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                ::fs::Path // expected new path
            >;
            class FSPathToAbsoluteNewPath : public ::testing::TestWithParam<FSPathToAbsoluteNewPathParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathToAbsoluteNewPath(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathToAbsoluteNewPath, ReturnGivenStatus) {
                ::fs::Path expectedNewPath = std::get<1>(GetParam());

                for (::fs::Path &instance : _instances) {
                    instance.toAbsolute();
                    EXPECT_EQ(instance, expectedNewPath);
                }
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenVariousPath,
                FSPathToAbsoluteNewPath,
                testing::Values(
                    std::make_tuple("", ::fs::Path()),
                    std::make_tuple(std::nullopt, ::fs::Path()),
                    std::make_tuple("./bin", ::fs::Path(std::filesystem::current_path().string() + std::string("/./bin"))),
                    std::make_tuple("../../tests/assets/fs/.hidden", ::fs::Path(std::filesystem::current_path().string() + std::string("/../../tests/assets/fs/.hidden"))),
                    std::make_tuple("./IDontExists", ::fs::Path(std::filesystem::current_path().string() + std::string("/./IDontExists"))),
                    std::make_tuple("./../../tests/assets/fs/.hidden", ::fs::Path(std::filesystem::current_path().string() + std::string("/./../../tests/assets/fs/.hidden"))),
                    std::make_tuple("./I/DO/no/exists", ::fs::Path(std::filesystem::current_path().string() + std::string("/./I/DO/no/exists"))),
                    std::make_tuple("/path/to/non_empty_file.txt", ::fs::Path(std::string("/////path/to///non_empty_file.txt"))),
                    std::make_tuple("/a/b/c/d/e/f/g/h", ::fs::Path(std::string("/a/b/c/d/e/f/g/h"))),
                    std::make_tuple("..////.//a/b/c/d/e/f/g/h", ::fs::Path(std::filesystem::current_path().string() + std::string("/..////.//a/b/c/d/e/f/g/h"))),
                    std::make_tuple("..////.//a/b/c/d/e/f/g/h", ::fs::Path(std::filesystem::current_path().string() + std::string("/..////.//a/b/c/d/e/f/g/h"))),
                    std::make_tuple("", ::fs::Path(std::string(""))),
                    std::make_tuple("./", ::fs::Path(std::filesystem::current_path().string() + std::string("/./"))),
                    std::make_tuple("..", ::fs::Path(std::filesystem::current_path().string() + std::string("/.."))),
                    std::make_tuple("../..", ::fs::Path(std::filesystem::current_path().string() + std::string("/../.."))),
                    std::make_tuple("../.", ::fs::Path(std::filesystem::current_path().string() + std::string("/../."))),
                    std::make_tuple("/rootfile.tx", ::fs::Path(std::string("/rootfile.tx"))),
                    std::make_tuple("/path/with spaces/file.txt", ::fs::Path(std::string("/path/with spaces/file.txt"))),
                    std::make_tuple("/path/with!@#$%^&*()_+special/file.txt", ::fs::Path(std::string("/path/with!@#$%^&*()_+special/file.txt"))),
                    std::make_tuple("/path/with/trailing/slashes////", ::fs::Path(std::string("/path/with/trailing/slashes////"))),
                    std::make_tuple(".", ::fs::Path(std::filesystem::current_path().string() + std::string("/."))),
                    std::make_tuple("././././.", ::fs::Path(std::filesystem::current_path().string() + std::string("/././././."))),
                    std::make_tuple("TEST123", ::fs::Path(std::filesystem::current_path().string() + std::string("/TEST123"))),
                    std::make_tuple("KODEROZP", ::fs::Path(std::filesystem::current_path().string() + std::string("/KODEROZP"))),
                    std::make_tuple("path/with/very/long/name/that/exceeds/system/limits", ::fs::Path(std::filesystem::current_path().string() + std::string("/path/with/very/long/name/that/exceeds/system/limits"))),
                    std::make_tuple("./path/with!@#$%^&*()_+special/characters", ::fs::Path(std::filesystem::current_path().string() + std::string("/./path/with!@#$%^&*()_+special/characters"))),
                    std::make_tuple("../path/with!@#$%^&*()_+special/characters", ::fs::Path(std::filesystem::current_path().string() + std::string("/../path/with!@#$%^&*()_+special/characters"))),
                    std::make_tuple("./path/with spaces", ::fs::Path(std::filesystem::current_path().string() + std::string("/./path/with spaces"))),
                    std::make_tuple("/", ::fs::Path(std::string("/"))),
                    std::make_tuple("//", ::fs::Path(std::string("//")))
                )
            );
        }
    }
}
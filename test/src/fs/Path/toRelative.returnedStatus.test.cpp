/**
 * @file toRelative.returnedStatus.test.cpp
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
            using FSPathToRelativeReturnedStatusParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                ::fs::Status // expected returned status
            >;
            class FSPathToRelativeReturnedStatus : public ::testing::TestWithParam<FSPathToRelativeReturnedStatusParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathToRelativeReturnedStatus(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathToRelativeReturnedStatus, ReturnGivenStatus) {
                ::fs::Status expectedStatus = std::get<1>(GetParam());

                for (::fs::Path &instance : _instances)
                    EXPECT_EQ(instance.toRelative(), expectedStatus);
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingVariousStatus,
                FSPathToRelativeReturnedStatus,
                testing::Values(
                    std::make_tuple(std::filesystem::current_path().string() + "/bin", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/bin", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/./bin", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/./bin", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/////.//a/b/c/d/e/f/g/h", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/////.//a/b/c/d/e/f/g/h", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/./////.//a/b/c/d/e/f/g/h", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/./////.//a/b/c/d/e/f/g/h", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string(), ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string(), ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/../../.test123/789.abc", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/../../.test123/789.abc", ::fs::Status::OK),
                    std::make_tuple(Helper::createCleanedStrPath(std::filesystem::current_path().string() + "/../../tests/assets/fs/"), ::fs::Status::OK),
                    std::make_tuple(Helper::createCleanedStrPath(std::filesystem::current_path().string() + "/../aaa/b b.j/-n--$h/."), ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "//bin", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/././bin", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/../../bin", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/bin$#@", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/bin folder", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/bin📁", ::fs::Status::OK),
                    std::make_tuple(std::filesystem::current_path().string() + "/../", ::fs::Status::OK),
                    std::make_tuple("", ::fs::Status::E_PATH_EMPTY),
                    std::make_tuple(std::nullopt, ::fs::Status::E_PATH_EMPTY)
                )
            );
        }
    }
}
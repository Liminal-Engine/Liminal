/**
 * @file toAbsolute.returnedStatus.test.cpp
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
            using FSPathToAbsoluteReturnedStatusParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                ::fs::Status // expected returned status
            >;
            class FSPathToAbsoluteReturnedStatus : public ::testing::TestWithParam<FSPathToAbsoluteReturnedStatusParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathToAbsoluteReturnedStatus(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathToAbsoluteReturnedStatus, ReturnGivenStatus) {
                ::fs::Status expectedStatus = std::get<1>(GetParam());

                for (::fs::Path &instance : _instances)
                    EXPECT_EQ(instance.toAbsolute(), expectedStatus);
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingVariousStatus,
                FSPathToAbsoluteReturnedStatus,
                testing::Values(
                    std::make_tuple("", ::fs::Status::E_PATH_EMPTY),
                    std::make_tuple(std::nullopt, ::fs::Status::E_PATH_EMPTY),
                    std::make_tuple("./bin", ::fs::Status::OK),
                    std::make_tuple("../../tests/assets/fs/.hidden",  ::fs::Status::OK),
                    std::make_tuple("./IDontExists", ::fs::Status::OK),
                    std::make_tuple("./../../tests/assets/fs/.hidden", ::fs::Status::OK),
                    std::make_tuple("./I/DO/no/exists", ::fs::Status::OK),
                    std::make_tuple("/path/to/non_empty_file.txt", ::fs::Status::OK),
                    std::make_tuple("/a/b/c/d/e/f/g/h", ::fs::Status::OK),
                    std::make_tuple("..////.//a/b/c/d/e/f/g/h", ::fs::Status::OK),
                    std::make_tuple("..////.//a/b/c/d/e/f/g/h", ::fs::Status::OK),
                    std::make_tuple("./", ::fs::Status::OK),
                    std::make_tuple("..", ::fs::Status::OK),
                    std::make_tuple("../..", ::fs::Status::OK),
                    std::make_tuple("../.", ::fs::Status::OK),
                    std::make_tuple("/rootfile.tx", ::fs::Status::OK),
                    std::make_tuple("/path/with spaces/file.txt", ::fs::Status::OK),
                    std::make_tuple("/path/with!@#$%^&*()_+special/file.txt", ::fs::Status::OK),
                    std::make_tuple("/path/with/trailing/slashes////", ::fs::Status::OK),
                    std::make_tuple(".", ::fs::Status::OK),
                    std::make_tuple("././././.", ::fs::Status::OK),
                    std::make_tuple("TEST123", ::fs::Status::OK),
                    std::make_tuple("KODEROZP", ::fs::Status::OK),
                    std::make_tuple("path/with/very/long/name/that/exceeds/system/limits", ::fs::Status::OK),
                    std::make_tuple("./path/with!@#$%^&*()_+special/characters", ::fs::Status::OK),
                    std::make_tuple("../path/with!@#$%^&*()_+special/characters", ::fs::Status::OK),
                    std::make_tuple("./path/with spaces", ::fs::Status::OK),
                    std::make_tuple("/", ::fs::Status::OK),
                    std::make_tuple("//", ::fs::Status::OK)
                )
            );
        }
    }
}
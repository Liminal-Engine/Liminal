/**
 * @file pointsTo.test.cpp
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
            using FSPathPointsToParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                ::fs::Path, // Path to compare to
                bool // expected result
            >;
            class FSPathPointsTo : public ::testing::TestWithParam<FSPathPointsToParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathPointsTo(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathPointsTo, ReturnGivenStatus) {
                ::fs::Path pathToCompare = std::get<1>(GetParam());
                bool expectedResult = std::get<2>(GetParam());

                for (::fs::Path &instance : _instances) {                    
                    EXPECT_EQ(instance.pointsTo(pathToCompare), expectedResult);
                }
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingVariousStatus,
                FSPathPointsTo,
                testing::Values(
                    std::make_tuple(std::filesystem::current_path().string() + "/bin", ::fs::Path("./bin"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/../bin", ::fs::Path("../bin"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/../bin", ::fs::Path("../bin"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/-----/JRKK/../../kroijeojtk/rkoketo/keoprtk/../frt", ::fs::Path("-----/JRKK/../../kroijeojtk/rkoketo/keoprtk/../frt"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/-----/JRKK/../../kroijeojtk/rkoketo/keoprtk/../frt", ::fs::Path("-----/JRKK/../../kroijeojtk/rkoketo/keoprtk/../frt"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/nonexistent", ::fs::Path("./nonexistent"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/../nonexistent", ::fs::Path("../nonexistent"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/../../nonexistent", ::fs::Path("../../nonexistent"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/./././nonexistent", ::fs::Path("./nonexistent"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/./././bin", ::fs::Path("./bin"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/../../bin", ::fs::Path("../../bin"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/bin$#@", ::fs::Path("./bin$#@"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/bin folder", ::fs::Path("./bin folder"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/bin📁", ::fs::Path("./bin📁"), true),
                    std::make_tuple(std::filesystem::current_path().string() + "/../", ::fs::Path(".."), true),
                    std::make_tuple("/", ::fs::Path("/"), true),
                    std::make_tuple("/", ::fs::Path("/"), true),
                    std::make_tuple("/", ::fs::Path("/////"), true),
                    std::make_tuple("/", ::fs::Path("/////"), true),
                    std::make_tuple("", ::fs::Path(""), true),
                    std::make_tuple("/../", ::fs::Path(".."), false),
                    std::make_tuple("/../", ::fs::Path(".."), false),
                    std::make_tuple("nonexistent", ::fs::Path("./nonexistent"), true),
                    std::make_tuple("nonexistent", ::fs::Path("./nonexistent"), true),
                    std::make_tuple("/bin$#@", ::fs::Path("./bin$#@"), false),
                    std::make_tuple("/bin$#@", ::fs::Path("./bin$#@"), false),
                    std::make_tuple("/bin$#@", ::fs::Path("./other"), false)
                )
            );
        }
    }
}

/**
 *  TODO
 * test this PATHS on wndows : I thinkg those are special paths on windows
    std::make_tuple("CON", std::string("/CON")), fs::Status::OK),
    std::make_tuple("PRN", std::string("/PRN")), fs::Status::OK),
 * 
 */
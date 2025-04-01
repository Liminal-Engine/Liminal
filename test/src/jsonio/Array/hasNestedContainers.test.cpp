/**
 * @file hasNestedContainers.returnedValue.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "jsonio/InJson.hpp"
#include "jsonio/types.hpp"

#include "test/jsonio/Array/Helper.hpp"
#include "test/jsonio/Helper.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include <filesystem>
#include <optional>
#include <array>

namespace test {
    namespace jsonio {
        namespace Array {
            
            using JsonIOArrayHasNestedContainersParamType = std::tuple<
                fs::Path, // file path
                std::string, // json path
                std::optional<std::array<std::string, 3>>, // optional separators
                bool // expected result
            >;
            
            class JsonIOArrayHasNestedContainers : public ::testing::TestWithParam<JsonIOArrayHasNestedContainersParamType> {
                protected:
                    std::vector<::jsonio::types::Array_t> _instances;

                JsonIOArrayHasNestedContainers(void) : 
                _instances(
                    std::get<2>(GetParam()).has_value() ?
                    (
                        ::test::jsonio::Array::Helper::create(
                            std::get<0>(GetParam()),
                            std::get<1>(GetParam()),
                            std::get<2>(GetParam()).value()
                        )
                    ) :
                    (
                        ::test::jsonio::Array::Helper::create(
                            std::get<0>(GetParam()),
                            std::get<1>(GetParam())
                        )
                    )
                )
                {}

            };

            TEST_P(JsonIOArrayHasNestedContainers, ReturnsGivenValue) {
                bool expectedResult = std::get<3>(GetParam());

                for (const ::jsonio::types::Array_t &instance : _instances)
                    EXPECT_EQ(instance.hasNestedContainers(), expectedResult);
            }
            
            INSTANTIATE_TEST_SUITE_P(
                WhenGivenPathOfArrayContainingComplexValues,
                JsonIOArrayHasNestedContainers,
                testing::Values(
                    std::make_tuple(::test::jsonio::Helper::VALID__BASIC, "hobbies", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "78/40014", std::array<std::string, 3>{"/", "[", "]"}, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "78/an.other.[ke.y]", std::array<std::string, 3>{"/", "<", ">"}, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[0].friends", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[9].friends", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[14].friends", std::nullopt, true)
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenPathOfArrayNotContainingComplexValues,
                JsonIOArrayHasNestedContainers,
                testing::Values(
                    std::make_tuple(::test::jsonio::Helper::VALID__BASIC, "hobbies[4].secondNestedHobbies", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "78.40014", std::array<std::string, 3>{"/", "[", "]"}, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "78/40014[0]/yes", std::array<std::string, 3>{"/", "[", "]"}, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "interests", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[0].tags", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[9].tags", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[14].tags", std::nullopt, false)

                )
            );
        } // namespace Array
    } // namespace jsonio
} // namespace test

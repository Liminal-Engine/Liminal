/**
 * @file hasNestedContainers.returnedValue.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-09
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "jsonio/InJson.hpp"
#include "jsonio/types.hpp"

#include "test/jsonio/Object/Helper.hpp"
#include "test/jsonio/Helper.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include <filesystem>
#include <optional>

namespace test {
    namespace jsonio {
        namespace Object {
            
            using JsonIOObjectHasNestedContainersMethodParamType = std::tuple<
                fs::Path, // file path
                std::string, // json path
                std::optional<std::array<std::string, 3>>, // optional separators
                bool // expected result
            >;
            
            class JsonIOObjectHasNestedContainersMethod : public ::testing::TestWithParam<JsonIOObjectHasNestedContainersMethodParamType> {
                protected:
                    std::vector<::jsonio::types::Object_t> _instances;

                JsonIOObjectHasNestedContainersMethod(void) : 
                _instances(
                    std::get<2>(GetParam()).has_value() ?
                    (
                        ::test::jsonio::Object::Helper::create(
                            std::get<0>(GetParam()),
                            std::get<1>(GetParam()),
                            std::get<2>(GetParam()).value()
                        )
                    ) :
                    (
                        ::test::jsonio::Object::Helper::create(
                            std::get<0>(GetParam()),
                            std::get<1>(GetParam())
                        )
                    )
                )
                {}

            };

            TEST_P(JsonIOObjectHasNestedContainersMethod, ReturnsGivenValue) {
                bool expectedResult = std::get<3>(GetParam());

                for (const ::jsonio::types::Object_t &instance : _instances)
                    EXPECT_EQ(instance.hasNestedContainers(), expectedResult);
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenPathOfObjectContainingComplexValues,
                JsonIOObjectHasNestedContainersMethod,
                testing::Values(
                    std::make_tuple(::test::jsonio::Helper::VALID__BASIC, "address", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__BASIC, "hobbies[4]", std::nullopt, true),

                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "78", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "78.40014[0]", std::nullopt, true),

                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "nestedData", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9", std::nullopt, true),

                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[0]", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[14]", std::nullopt, true),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[9].friends[0]", std::nullopt, true)
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenPathOfObjectNotContainingComplexValues,
                JsonIOObjectHasNestedContainersMethod,
                testing::Values(
                    std::make_tuple(::test::jsonio::Helper::VALID__BASIC, "address.story", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__BASIC, "hobbies[3]", std::nullopt, false),

                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "-12345", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "78/an.other.[ke.y]<0>", std::array<std::string, 3>{"/", "<", ">"}, false),

                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "address", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "grades", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[0]", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[1]", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2]", std::nullopt, false),

                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[0].friends[0]", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[0].friends[1]", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[0].friends[2]", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[9].friends[0].specialFriend", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[9].friends[1]", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[9].friends[2]", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[13].friends[0]", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[13].friends[1]", std::nullopt, false),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[13].friends[2]", std::nullopt, false)
                )
            );

        } // namespace Object
    } // namespace jsonio
} // namespace test

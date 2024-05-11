/**
 * @file getLen.returnedValue.test.cpp
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

#include "test/jsonio/Array/Helper.hpp"
#include "test/jsonio/Helper.hpp"
#include "test/Helper.hpp"

#include <fs/Path.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include <filesystem>
#include <vector>

#include <iostream>

namespace test {
    namespace jsonio {
        namespace Array {

            using JsonIOArrayGetLenParam = std::tuple<
                ::fs::Path, //file path,
                std::string, // json path
                std::optional<std::vector<std::string>>, // optional separators
                std::size_t
            >;
            class JsonIOArrayGetLenMethod : public ::testing::TestWithParam<JsonIOArrayGetLenParam> {

                protected:
                    std::vector<::jsonio::types::Array_t> _instances;

                JsonIOArrayGetLenMethod(void) : 
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

            TEST_P(JsonIOArrayGetLenMethod, ReturnGivenLength) {
                for (const ::jsonio::types::Array_t &instance : _instances) {
                    // std::cout << "LEN=" << instance.getLen() << std::endl;
                    EXPECT_EQ(instance.getLen(), std::get<3>(GetParam()));
                }
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenPathOfArraysInValidJsonFiles,
                JsonIOArrayGetLenMethod,
                testing::Values(
                    std::make_tuple(::test::jsonio::Helper::VALID__BASIC, "hobbies", std::nullopt, 5),
                    std::make_tuple(::test::jsonio::Helper::VALID__BASIC, "hobbies[4].secondNestedHobbies", std::nullopt, 4),

                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "78.40014", std::vector<std::string>{"/", "[", "]"}, 0),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "78.40014", std::nullopt, 1),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "78.40014[0].yes", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, "78/an.other.[ke.y]", std::vector<std::string>{"/", "<", ">"}, 2),


                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[0].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[0].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[1].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[1].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[2].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[2].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[3].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[3].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[4].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[4].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[5].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[5].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[6].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[6].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[7].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[7].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[8].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[8].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[9].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[9].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[10].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[10].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[11].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[11].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[12].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[12].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[13].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[13].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[14].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[14].friends", std::nullopt, 3),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[15].tags", std::nullopt, 7),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, "[15].friends", std::nullopt, 3)
                )
            );
        } // namespace Array
    } // namespace jsonio
} // namespace test

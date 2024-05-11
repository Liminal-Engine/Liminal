/**
 * @file get.returnedValue.test.cpp
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include <filesystem>
#include <vector>

namespace test {
    namespace jsonio {
        namespace Array {
            
            class JsonIOArrayGetMethod : public ::testing::Test {
                private:
                    std::vector<::jsonio::types::Array_t> _instances;

                protected:
                    
                    JsonIOArrayGetMethod(void)
                    {}

                    void create(
                        const fs::Path &filePath,
                        const std::string &jsonPath = "",
                        const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS
                    ) {
                        this->_instances = ::test::jsonio::Array::Helper::create(filePath, jsonPath, separators);
                    }

                    template<typename T>
                    requires ::jsonio::is_in_variant_v<T, ::jsonio::types::SimpleTypes_t>
                    void test_eq(
                        const T &expected,
                        const std::size_t &index
                    ) {
                        if constexpr (std::is_same_v<T, ::jsonio::types::FloatNum_t>)
                            for (const ::jsonio::types::Array_t &instance : _instances)
                                EXPECT_NEAR(instance.get<T>(index).value(), expected, ::test::Helper::EXPECT_NEAR_ABSOLUTE_ERROR);
                        else
                            for (const ::jsonio::types::Array_t &instance : _instances)
                                EXPECT_EQ(instance.get<T>(index).value(), expected);
                    }

            };

            TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile1) {
                

                create(::test::jsonio::Helper::VALID__BASIC, "hobbies");
                test_eq<::jsonio::types::String_t>("reading", 0);
                test_eq<::jsonio::types::String_t>("gaming", 1);
                test_eq<::jsonio::types::String_t>("hiking", 2);
            }

            TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile2) {

                create(::test::jsonio::Helper::VALID__BASIC, "hobbies[4].secondNestedHobbies");
                test_eq<::jsonio::types::String_t>("un", 0);
                test_eq<::jsonio::types::String_t>("dos", 1);
                test_eq<::jsonio::types::IntNum_t>(3, 2);
                test_eq<::jsonio::types::Null_t>(nullptr, 3);
            };

            TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesEdgeCasesJsonFile1) {

                create(::test::jsonio::Helper::VALID__EDGE_CASES, "78/40014!0$/yes", std::vector<std::string>{"/", "!", "$"});
                test_eq<::jsonio::types::String_t>("no", 0);
                test_eq<::jsonio::types::String_t>("maybe", 1);
                test_eq<::jsonio::types::String_t>("this[is]a.[key]", 2);
            };


            TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesLargeJsonFile0) {

                create(::test::jsonio::Helper::VALID__LARGE, "[0].tags");
                test_eq<::jsonio::types::String_t>("tempor", 0);
                test_eq<::jsonio::types::String_t>("proident", 1);
                test_eq<::jsonio::types::String_t>("ut", 2);
                test_eq<::jsonio::types::String_t>("sint", 3);
                test_eq<::jsonio::types::String_t>("ad", 4);
                test_eq<::jsonio::types::String_t>("laboris", 5);
                test_eq<::jsonio::types::String_t>("ullamco", 6);
            };

            TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesLargeJsonFile1) {
                
                create(::test::jsonio::Helper::VALID__LARGE, "[6].tags");
                test_eq<::jsonio::types::String_t>("ullamco", 0);
                test_eq<::jsonio::types::String_t>("dolore", 1);
                test_eq<::jsonio::types::String_t>("officia", 2);
                test_eq<::jsonio::types::String_t>("sit", 3);
                test_eq<::jsonio::types::String_t>("deserunt", 4);
                test_eq<::jsonio::types::String_t>("exercitation", 5);
                test_eq<::jsonio::types::String_t>("deserunt", 6);
            };

            TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesLargeJsonFile2) {

                create(::test::jsonio::Helper::VALID__LARGE, "[9].tags");
                test_eq<::jsonio::types::String_t>("voluptate", 0);
                test_eq<::jsonio::types::String_t>("do", 1);
                test_eq<::jsonio::types::String_t>("incididunt", 2);
                test_eq<::jsonio::types::String_t>("commodo", 3);
                test_eq<::jsonio::types::String_t>("ea", 4);
                test_eq<::jsonio::types::String_t>("in", 5);
                test_eq<::jsonio::types::String_t>("labore", 6);
            };

            TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesLargeJsonFile3) {
                
                create(::test::jsonio::Helper::VALID__LARGE, "[15].tags");
                test_eq<::jsonio::types::String_t>("sit", 0);
                test_eq<::jsonio::types::String_t>("deserunt", 1);
                test_eq<::jsonio::types::String_t>("commodo", 2);
                test_eq<::jsonio::types::String_t>("esse", 3);
                test_eq<::jsonio::types::String_t>("aliquip", 4);
                test_eq<::jsonio::types::String_t>("labore", 5);
                test_eq<::jsonio::types::String_t>("deserunt", 6);
            };

            TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesNestedJsonFile1) {
                

                create(::test::jsonio::Helper::VALID__NESTED, "interests");
                test_eq<::jsonio::types::String_t>("reading", 0);
                test_eq<::jsonio::types::String_t>("traveling", 1);
                test_eq<::jsonio::types::String_t>("coding", 2);
            };

            TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesNestedJsonFile2) {
                
                create(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags");
                test_eq<::jsonio::types::String_t>("dolore", 0);
                test_eq<::jsonio::types::String_t>("do", 1);
                test_eq<::jsonio::types::String_t>("commodo", 2);
                test_eq<::jsonio::types::String_t>("consequat", 3);
                test_eq<::jsonio::types::String_t>("ut", 4);
                test_eq<::jsonio::types::String_t>("proident", 5);
                test_eq<::jsonio::types::String_t>("sint", 6);
            };
        } // namespace Array
    } // namespace jsonio
} // namespace test

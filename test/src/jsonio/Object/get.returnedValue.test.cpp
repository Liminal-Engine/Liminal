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

#include "test/jsonio/Object/Helper.hpp"
#include "test/jsonio/Helper.hpp"
#include "test/Helper.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include <filesystem>
#include <vector>

namespace test {
    namespace jsonio {
        namespace Object {
            
            class JsonIOObjectGetMethod : public ::testing::Test {
                private:
                    std::vector<::jsonio::types::Object_t> _instances;

                protected:
                    
                    JsonIOObjectGetMethod(void)
                    {}

                    void create(
                        const fs::Path &filePath,
                        const std::string &jsonPath = "",
                        const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS
                    ) {
                        this->_instances = ::test::jsonio::Object::Helper::create(filePath, jsonPath, separators);
                    }

                    template<typename T>
                    requires ::jsonio::is_in_variant_v<T, ::jsonio::types::SimpleTypes_t>
                    void test_eq(
                        const T &expected,
                        const std::string &jsonPath = ""
                    ) {
                        if constexpr (std::is_same_v<T, ::jsonio::types::FloatNum_t>)
                            for (const ::jsonio::types::Object_t &instance : _instances)
                                EXPECT_NEAR(instance.get<T>(jsonPath).value(), expected, ::test::Helper::EXPECT_NEAR_ABSOLUTE_ERROR);
                        else
                            for (const ::jsonio::types::Object_t &instance : _instances)
                                EXPECT_EQ(instance.get<T>(jsonPath).value(), expected);
                    }

            };

            TEST_F(JsonIOObjectGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile1) {
                create(::test::jsonio::Helper::VALID__BASIC, "address.story");
                test_eq<::jsonio::types::IntNum_t>(15, "left");
                test_eq<::jsonio::types::FloatNum_t>(678.5, "right");
            };

            TEST_F(JsonIOObjectGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile2) {
                create(::test::jsonio::Helper::VALID__BASIC, "address");
                test_eq<::jsonio::types::String_t>("123 Main St", "street");
                test_eq<::jsonio::types::String_t>("Anytown", "city");
                test_eq<::jsonio::types::String_t>("Anystate", "state");
                test_eq<::jsonio::types::IntNum_t>(12345, "postalCode");
                test_eq<::jsonio::types::FloatNum_t>(42.84, "anotherData");
            };

            TEST_F(JsonIOObjectGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile3) {
                create(::test::jsonio::Helper::VALID__BASIC, "hobbies[3]");
                test_eq<::jsonio::types::String_t>("no", "nestedHobby");
            };

            TEST_F(JsonIOObjectGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile4) {
                create(::test::jsonio::Helper::VALID__BASIC, "hobbies[4]");
                test_eq<::jsonio::types::Null_t>(nullptr, "nothingImportantHere");
            };

            TEST_F(JsonIOObjectGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile5) {
                create(::test::jsonio::Helper::VALID__BASIC, "");
                test_eq<::jsonio::types::String_t>("John Doe", "name");
                test_eq<::jsonio::types::IntNum_t>(30, "age");
                test_eq<::jsonio::types::Bool_t>(true, "isEmployed");
                test_eq<::jsonio::types::String_t>("yes", "happy");
            };

            TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithEdgeCasesJsonFile1) {
                create(::test::jsonio::Helper::VALID__EDGE_CASES, "");
                test_eq<::jsonio::types::String_t>("{'yes': 'no}", "/////////....//////?!?!?!!!![12e-89]");
            };

            TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithEdgeCasesJsonFile2) {
                create(::test::jsonio::Helper::VALID__EDGE_CASES, "78/an.other.[ke.y]<0>", std::vector<std::string>{"/", "<", ">"});
                test_eq<::jsonio::types::String_t>("no", "yes");
            };

            TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithEdgeCasesJsonFile3) {
                create(::test::jsonio::Helper::VALID__EDGE_CASES, "78/an.other.[ke.y]<1>", std::vector<std::string>{"/", "<", ">"});
                test_eq<::jsonio::types::Null_t>(nullptr, "no");
            };

            TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithLargeJsonFile1) {
                create(::test::jsonio::Helper::VALID__LARGE, "[0]");
                test_eq<::jsonio::types::String_t>("018a1a54-0e66-44b2-bf88-6349a4839645", "guid");
                test_eq<::jsonio::types::String_t>("2019-12-25T04:23:12 -01:00", "registered");
                test_eq<::jsonio::types::FloatNum_t>(-48.602054, "latitude");
                test_eq<::jsonio::types::String_t>("+1 (906) 540-3410", "phone");
                test_eq<::jsonio::types::String_t>("kirbynielsen@dragbot.com", "email");
                test_eq<::jsonio::types::String_t>("http://placehold.it/32x32", "picture");
                test_eq<::jsonio::types::String_t>("$2,399.08", "balance");
            };

            TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithLargeJsonFile2) {
                create(::test::jsonio::Helper::VALID__LARGE, "[9].friends[0]");
                test_eq<::jsonio::types::IntNum_t>(0, "id");
                test_eq<::jsonio::types::String_t>("Gomez Rowe", "name");
            };

            TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithLargeJsonFile3) {
                create(::test::jsonio::Helper::VALID__LARGE, "[9].friends[0].specialFriend");
                test_eq<::jsonio::types::String_t>("John", "firstsName");
                test_eq<::jsonio::types::String_t>("Doe", "secondName");
            };



            TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithNestedJsonFile1) {
                create(::test::jsonio::Helper::VALID__NESTED, "address");
                test_eq<::jsonio::types::String_t>("123 Main St", "street");
                test_eq<::jsonio::types::String_t>("Anytown", "city");
                test_eq<::jsonio::types::String_t>("USA", "country");
            };

            TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithNestedJsonFile2) {
                create(::test::jsonio::Helper::VALID__NESTED, "address");
                create(::test::jsonio::Helper::VALID__NESTED, "grades");
                test_eq<::jsonio::types::IntNum_t>(85, "math");
                test_eq<::jsonio::types::IntNum_t>(92, "english");
                test_eq<::jsonio::types::IntNum_t>(78, "history");
            };

            TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithNestedJsonFile3) {
                create(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8");
                test_eq<::jsonio::types::Bool_t>(true, "isNested");
            };

            TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithNestedJsonFile4) {
                create(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21");
                test_eq<::jsonio::types::String_t>("Random Value 1", "randomKey1");
                test_eq<::jsonio::types::IntNum_t>(42, "randomKey2");
                test_eq<::jsonio::types::Bool_t>(true, "randomKey3");
            };

            TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithNestedJsonFile5) {
                create(::test::jsonio::Helper::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9");
                test_eq<::jsonio::types::FloatNum_t>(155.61306, "longitude");
                test_eq<::jsonio::types::String_t>("Hello, Madelyn Gilliam! You have 8 unread messages.", "greeting");
                test_eq<::jsonio::types::String_t>("banana", "favoriteFruit");
            }

        } // namespace Object
    } // namespace jsonio
} // namespace test

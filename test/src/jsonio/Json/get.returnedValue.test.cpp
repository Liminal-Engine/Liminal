/**
 * @file get.returnedValue.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */ 



//**********
// Incudes required for Json internal calls TODO : remove this ?
#include "jsonio/include/_private/_lexing/_types.hpp"
#include "jsonio/include/_private/_lexing/_lexing.hpp"
//**********

#include "test/jsonio/Helper.hpp"
#include "test/Helper.hpp"

#include <jsonio/Json.hpp>
#include <jsonio/separators.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <type_traits>

namespace test {
    namespace jsonio {
        namespace Json {
            
            class JsonIOJsonGetMethodReturnedValue : public ::testing::Test {
                protected:
                    ::jsonio::Json __instance;
                
                public:
                    JsonIOJsonGetMethodReturnedValue(void) :
                    __instance(::jsonio::Json())
                    {}
    
                    template <typename T>
                    requires ::jsonio::is_in_variant_v<T, ::jsonio::types::Any_t>
                    void test_value_eq(const T &expected, const std::string &jsonPath, const std::array<std::string, 3> &separators = JSON_DEFAULT_SEPARATORS) {
                        if constexpr (std::is_same_v<T, ::jsonio::types::FloatNum_t>)
                            EXPECT_NEAR(this->__instance.get<::jsonio::types::FloatNum_t>(jsonPath, separators).value(), expected, ::test::Helper::EXPECT_NEAR_ABSOLUTE_ERROR);
                        else
                            EXPECT_EQ(this->__instance.get<T>(jsonPath, separators).value(), expected);
                    }
    
                    template <typename T>
                    requires ::jsonio::is_in_variant_v<T, ::jsonio::types::Any_t>
                    void test_has_value(const bool &expected, const std::string &jsonPath, const std::array<std::string, 3> &separators = JSON_DEFAULT_SEPARATORS) {
                        EXPECT_EQ(this->__instance.get<T>(jsonPath, separators).has_value(), expected);
                    }
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile1) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::Object_t>(true, "");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile2) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::String_t>(true, "name");
                test_value_eq<::jsonio::types::String_t>("John Doe", "name");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile3) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::IntNum_t>(true, "age");
                test_value_eq<::jsonio::types::IntNum_t>(30, "age");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile4) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::Bool_t>(true, "isEmployed");
                test_value_eq<::jsonio::types::Bool_t>(true, "isEmployed");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile5) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::Object_t>(true, "address");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile6) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::Object_t>(true, "address.story");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile7) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
            
                test_has_value<::jsonio::types::IntNum_t>(true, "address.story.left");
                test_value_eq<::jsonio::types::IntNum_t>(15, "address.story.left");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile8) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::FloatNum_t>(true, "address.story.right");
                test_value_eq<::jsonio::types::FloatNum_t>(678.5, "address.story.right");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile9) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::String_t>(true, "address.street");
                test_value_eq<::jsonio::types::String_t>("123 Main St", "address.street");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile10) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::String_t>(true, "address.city");
                test_value_eq<::jsonio::types::String_t>("Anytown", "address.city");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile11) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::String_t>(true, "address.state");
                test_value_eq<::jsonio::types::String_t>("Anystate", "address.state");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile12) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::IntNum_t>(true, "address.postalCode");
                test_value_eq<::jsonio::types::IntNum_t>(12345, "address.postalCode");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile13) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::FloatNum_t>(true, "address.anotherData");
                test_value_eq<::jsonio::types::FloatNum_t>(42.84, "address.anotherData");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile14) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::Array_t>(true, "hobbies");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile15) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::String_t>(true, "hobbies[0]");
                test_value_eq<::jsonio::types::String_t>("reading", "hobbies[0]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile16) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::String_t>(true, "hobbies[1]");
                test_value_eq<::jsonio::types::String_t>("gaming", "hobbies[1]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile17) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::String_t>(true, "hobbies[2]");
                test_value_eq<::jsonio::types::String_t>("hiking", "hobbies[2]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile18) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::Object_t>(true, "hobbies[3]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile19) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::String_t>(true, "hobbies[3].nestedHobby");
                test_value_eq<::jsonio::types::String_t>("no", "hobbies[3].nestedHobby");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile20) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::Object_t>(true, "hobbies[4]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile21) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::Array_t>(true, "hobbies[4].secondNestedHobbies");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile22) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::String_t>(true, "hobbies[4].secondNestedHobbies[0]");
                test_value_eq<::jsonio::types::String_t>("un", "hobbies[4].secondNestedHobbies[0]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile23) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::String_t>(true, "hobbies[4].secondNestedHobbies[1]");
                test_value_eq<::jsonio::types::String_t>("dos", "hobbies[4].secondNestedHobbies[1]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile24) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::IntNum_t>(true, "hobbies[4].secondNestedHobbies[2]");
                test_value_eq<::jsonio::types::IntNum_t>(3, "hobbies[4].secondNestedHobbies[2]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile25) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::Null_t>(true, "hobbies[4].secondNestedHobbies[3]");
                test_value_eq<::jsonio::types::Null_t>(nullptr, "hobbies[4].secondNestedHobbies[3]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile26) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::Null_t>(true, "hobbies[4].nothingImportantHere");
                test_value_eq<::jsonio::types::Null_t>(nullptr, "hobbies[4].nothingImportantHere");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenBasicJsonFile27) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::String_t>(true, "happy");
                test_value_eq<::jsonio::types::String_t>("yes", "happy");
            };
    
    
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile1) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::Object_t>(true, "");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile2) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                //TODO : create and test a liminal_string interpret escaped chars func
                test_has_value<::jsonio::types::String_t>(true, "isThisAnObjec\\tt?::\\n:::,  ");
                test_value_eq<::jsonio::types::String_t>("{\\\"I\\\": \\\"don't\\\",\\n\\t\\\"think\\\": false }", "isThisAnObjec\\tt?::\\n:::,  ");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile3) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::Object_t>(true, "-12345");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile4) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::Array_t>(true, "78.40014", std::array<std::string, 3>{"/", "[", "]"});
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile5) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::Object_t>(true, "78");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile6) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::Array_t>(true, "78.40014");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile7) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::Object_t>(true, "78.40014[0]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile8) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::Array_t>(true, "78.40014[0].yes");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile9) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::String_t>(true, "78.40014[0].yes[0]");
                test_value_eq<::jsonio::types::String_t>("no", "78.40014[0].yes[0]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile10) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::String_t>(true, "78.40014[0].yes[1]");
                test_value_eq<::jsonio::types::String_t>("maybe", "78.40014[0].yes[1]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile11) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::String_t>(true, "78.40014[0].yes[2]");
                test_value_eq<::jsonio::types::String_t>("this[is]a.[key]", "78.40014[0].yes[2]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile12) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::Array_t>(true, "78/an.other.[ke.y]", std::array<std::string, 3>{"/", "<", ">"});
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile13) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::String_t>(true, "78/an.other.[ke.y]<0>/yes", std::array<std::string, 3>{"/", "<", ">"});
                test_value_eq<::jsonio::types::String_t>("no", "78/an.other.[ke.y]<0>/yes", std::array<std::string, 3>{"/", "<", ">"});
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenEdgeCasesJsonFile14) {
                __instance.parse(::test::jsonio::Helper::VALID__EDGE_CASES);
    
                test_has_value<::jsonio::types::Null_t>(true, "78/an.other.[ke.y]<1>/no", std::array<std::string, 3>{"/", "<", ">"});
                test_value_eq<::jsonio::types::Null_t>(nullptr, "78/an.other.[ke.y]<1>/no", std::array<std::string, 3>{"/", "<", ">"});
            }
    
    
    
            /**
             * Here, we do one test for the whole file to test if getting successive values without re parsing the file has a side effetct,
             * saving test execution time at the same time since in the the large json file
             */ 
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenLargeJsonFile) {
                __instance.parse(::test::jsonio::Helper::VALID__LARGE);
    
                test_has_value<::jsonio::types::Array_t>(true, "");
    
                test_has_value<::jsonio::types::String_t>(true, "[0].balance");
                test_value_eq<::jsonio::types::String_t>("$2,399.08", "[0].balance");
    
                test_has_value<::jsonio::types::String_t>(true, "[1].about");
                test_value_eq<::jsonio::types::String_t>("Minim cupidatat dolor mollit proident enim qui dolore dolor id nisi. Id sunt excepteur nisi officia elit qui aliqua excepteur aliquip fugiat et do Lorem. Qui cupidatat commodo consectetur do laborum elit aute ipsum aliquip. Pariatur dolore commodo enim aute excepteur.\\r\\n", "[1].about");
    
                test_has_value<::jsonio::types::Object_t>(true, "[13]");
    
                test_has_value<::jsonio::types::String_t>(true, "[13].registered");
                test_value_eq<::jsonio::types::String_t>("2022-03-08T09:55:37 -01:00", "[13].registered");
    
                test_has_value<::jsonio::types::Object_t>(true, "[14]");
    
                test_has_value<::jsonio::types::FloatNum_t>(true, "[14].latitude");
                test_value_eq<::jsonio::types::FloatNum_t>(-76.371709, "[14].latitude");
    
                test_has_value<::jsonio::types::Array_t>(true, "[14].friends");
                
                test_has_value<::jsonio::types::Object_t>(true, "[14].friends[1]");
    
                test_has_value<::jsonio::types::IntNum_t>(true, "[14].friends[1].id");
                test_value_eq<::jsonio::types::IntNum_t>(1, "[14].friends[1].id");
            };
    
    
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenNestedJsonFile1) {
                __instance.parse(::test::jsonio::Helper::VALID__NESTED);
    
                test_has_value<::jsonio::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested");
                test_value_eq<::jsonio::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenNestedJsonFile2) {
                __instance.parse(::test::jsonio::Helper::VALID__NESTED);
    
                test_has_value<::jsonio::types::String_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1");
                test_value_eq<::jsonio::types::String_t>("Random Value 1", "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenNestedJsonFile3) {
                __instance.parse(::test::jsonio::Helper::VALID__NESTED);
    
                test_has_value<::jsonio::types::IntNum_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2");
                test_value_eq<::jsonio::types::IntNum_t>(42, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenNestedJsonFile4) {
                __instance.parse(::test::jsonio::Helper::VALID__NESTED);
    
                test_has_value<::jsonio::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3");
                test_value_eq<::jsonio::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenNestedJsonFile5) {
                __instance.parse(::test::jsonio::Helper::VALID__NESTED);
    
                test_has_value<::jsonio::types::String_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags[5]");
                test_value_eq<::jsonio::types::String_t>("proident", "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags[5]");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenNestedJsonFile6) {
                __instance.parse(::test::jsonio::Helper::VALID__NESTED);
    
                test_has_value<::jsonio::types::IntNum_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2].id");
                test_value_eq<::jsonio::types::IntNum_t>(2, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2].id");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenNestedJsonFile7) {
                __instance.parse(::test::jsonio::Helper::VALID__NESTED);
    
                test_has_value<::jsonio::types::String_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting");
                test_value_eq<::jsonio::types::String_t>("Hello, Madelyn Gilliam! You have 8 unread messages.", "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenNestedJsonFile8) {
                __instance.parse(::test::jsonio::Helper::VALID__NESTED);
    
                test_has_value<::jsonio::types::String_t>(true, "address.country");
                test_value_eq<::jsonio::types::String_t>("USA", "address.country");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenNestedJsonFile9) {
                __instance.parse(::test::jsonio::Helper::VALID__NESTED);
    
                test_has_value<::jsonio::types::String_t>(true, "phone");
                test_value_eq<::jsonio::types::String_t>("+1 123-456-7890", "phone");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenNestedJsonFile10) {
                __instance.parse(::test::jsonio::Helper::VALID__NESTED);
    
                test_has_value<::jsonio::types::IntNum_t>(true, "grades.english");
                test_value_eq<::jsonio::types::IntNum_t>(92, "grades.english");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenWrongRequestedTypeWithNestedJsonFile) {
                __instance.parse(::test::jsonio::Helper::VALID__NESTED);
    
                test_has_value<::jsonio::types::FloatNum_t>(false, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2");
                test_has_value<::jsonio::types::Null_t>(false, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting");
            };
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenWrongRequestedTypeWithLargeJsonFile) {
                __instance.parse(::test::jsonio::Helper::VALID__LARGE);
    
                test_has_value<::jsonio::types::IntNum_t>(false, "[14].latitude");
            };
    
    
            TEST_F(JsonIOJsonGetMethodReturnedValue, WhenGivenWrongRequestedTypeWithBasicJsonFile) {
                __instance.parse(::test::jsonio::Helper::VALID__BASIC);
    
                test_has_value<::jsonio::types::FloatNum_t>(false, "name");
            }
        } // namespace Json
    } // namespace jsonio
} // namespace test

/**
 * @file insert.newValue.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-20
 * 
 * @copyright Copyright (c) 2024
 * 
*/


// //**********
// // Incudes required for Json internal calls TODO : remove this ?
#include "jsonio/include/_private/_lexing/_types.hpp"
#include "jsonio/include/_private/_lexing/_lexing.hpp"
// //**********

#include "jsonio/Json.hpp"
#include "jsonio/is_in_variant_v.hpp"
#include "jsonio/types.hpp"

#include "test/jsonio/Helper.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <variant>
#include <tuple>
#include <type_traits>

#include <sysop/sysop.hpp>


namespace test {
    namespace jsonio {
        namespace Json {


                class JsonIOJsonInsertMethodNewValue: public ::testing::Test
                {
                    private:
                        ::jsonio::Json _instance;

                    protected:

                        void create(const std::string &filePath = "") { // if file path is empty, no file will be parsed
                            if ( !filePath.empty() ) {
                                if ( this->_instance.parse(::fs::Path(filePath)) != ::jsonio::Status::OK ) {
                                    FAIL() << "Failed to parse JSON";
                                }
                            }
                        };

                        template<typename T>
                        requires ::jsonio::is_in_variant_v<T, ::jsonio::types::Any_t>
                        void test_returned_value(
                            const std::string &jsonPath = "",
                            const T &value = nullptr,
                            const bool &erase = false,
                            const std::array<std::string, 3> &separators = JSON_DEFAULT_SEPARATORS
                        ) {
                            this->_instance.insert<T>(jsonPath, value, erase, separators);
                            std::optional<T> newValue(this->_instance.get<T>(jsonPath, separators));
                            if ( !newValue.has_value() ) FAIL() << "New value not found";
                            EXPECT_EQ(newValue.value(), value);
                        }
                };

#define _CREATE_RETURNED_VALUE_TEST(testName, fileName, jsonIOType, jsonPath, value, erase, separators) \
    TEST_F(JsonIOJsonInsertMethodNewValue, testName) { \
        create(::test::jsonio::Helper::fileName.asStr()); \
        test_returned_value<::jsonio::types::jsonIOType>(jsonPath, value, erase, separators); \
    }
            

            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile1, VALID__BASIC, IntNum_t, "name", 8, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile2, VALID__BASIC, String_t, "address.story.right", "yoyo", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile3, VALID__BASIC, Null_t, "address.state", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile4, VALID__BASIC, FloatNum_t, "hobbies[4].secondNestedHobbies", 0.23, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile5, VALID__BASIC, Bool_t, "hobbies[4].secondNestedHobbies[3]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile6, VALID__BASIC, FloatNum_t, "hobbies", 178.555556f, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile7, VALID__BASIC, FloatNum_t, "address", 457888720, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile8, VALID__BASIC, IntNum_t, "age", 25, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile9, VALID__BASIC, String_t, "address.city", "New York", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile10, VALID__BASIC, Bool_t, "isEmployed", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile11, VALID__BASIC, FloatNum_t, "address.story.left", 20.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile12, VALID__BASIC, Null_t, "address.anotherData", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile13, VALID__BASIC, String_t, "address.street", "456 Elm St", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile14, VALID__BASIC, IntNum_t, "address.postalCode", 54321, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile15, VALID__BASIC, Bool_t, "happy", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile16, VALID__BASIC, FloatNum_t, "address.story.right", 700.75, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile17, VALID__BASIC, String_t, "hobbies[0]", "swimming", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile18, VALID__BASIC, IntNum_t, "hobbies[4].secondNestedHobbies[2]", 4, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile19, VALID__BASIC, Bool_t, "hobbies[4].nothingImportantHere", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile20, VALID__BASIC, FloatNum_t, "address.anotherData", 50.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile21, VALID__BASIC, String_t, "hobbies[3].nestedHobby", "yes", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile22, VALID__BASIC, IntNum_t, "age", 35, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile23, VALID__BASIC, Bool_t, "isEmployed", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile24, VALID__BASIC, FloatNum_t, "address.story.left", 10.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile25, VALID__BASIC, String_t, "address.city", "Oldtown", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile26, VALID__BASIC, IntNum_t, "address.postalCode", 67890, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile27, VALID__BASIC, Bool_t, "happy", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile28, VALID__BASIC, FloatNum_t, "address.story.right", 800.25, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile29, VALID__BASIC, String_t, "hobbies[1]", "coding", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile30, VALID__BASIC, IntNum_t, "hobbies[4].secondNestedHobbies[2]", 5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile31, VALID__BASIC, Bool_t, "hobbies[4].nothingImportantHere", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile32, VALID__BASIC, FloatNum_t, "address.anotherData", 60.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile33, VALID__BASIC, String_t, "hobbies[3].nestedHobby", "maybe", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile34, VALID__BASIC, IntNum_t, "age", 40, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile35, VALID__BASIC, Bool_t, "isEmployed", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile36, VALID__BASIC, FloatNum_t, "address.story.left", 5.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile37, VALID__BASIC, String_t, "address.city", "Smalltown", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile38, VALID__BASIC, IntNum_t, "address.postalCode", 98765, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile39, VALID__BASIC, Bool_t, "happy", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile40, VALID__BASIC, FloatNum_t, "address.story.right", 900.75, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile41, VALID__BASIC, String_t, "name", "Jane Doe", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile42, VALID__BASIC, FloatNum_t, "age", 30.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile43, VALID__BASIC, IntNum_t, "isEmployed", 1, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile44, VALID__BASIC, String_t, "address", "New Address", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile45, VALID__BASIC, Bool_t, "address.story", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile46, VALID__BASIC, FloatNum_t, "address.story.left", 30.0, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile47, VALID__BASIC, IntNum_t, "address.story.right", 100, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile48, VALID__BASIC, String_t, "address.street", "789 Pine St", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile49, VALID__BASIC, FloatNum_t, "address.city", 123.45, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile50, VALID__BASIC, IntNum_t, "address.state", 50, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile51, VALID__BASIC, Bool_t, "address.postalCode", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile52, VALID__BASIC, String_t, "address.anotherData", "Data", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile53, VALID__BASIC, IntNum_t, "hobbies", 5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile54, VALID__BASIC, FloatNum_t, "hobbies[0]", 1.1, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile55, VALID__BASIC, Bool_t, "hobbies[1]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile56, VALID__BASIC, String_t, "hobbies[2]", "new hobby", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile57, VALID__BASIC, IntNum_t, "hobbies[3]", 10, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile58, VALID__BASIC, FloatNum_t, "hobbies[4]", 20.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile59, VALID__BASIC, String_t, "hobbies[4].secondNestedHobbies", "nested", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile60, VALID__BASIC, IntNum_t, "hobbies[4].nothingImportantHere", 0, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile61, VALID__BASIC, Bool_t, "happy", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile62, VALID__BASIC, FloatNum_t, "happy", 1.0, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile63, VALID__BASIC, IntNum_t, "happy", 1, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile64, VALID__BASIC, String_t, "address.story.left", "left", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile65, VALID__BASIC, Bool_t, "address.story.right", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile66, VALID__BASIC, FloatNum_t, "address.story", 123.45, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile67, VALID__BASIC, IntNum_t, "address", 12345, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile68, VALID__BASIC, String_t, "hobbies", "new hobbies", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile69, VALID__BASIC, Bool_t, "hobbies[4].secondNestedHobbies[2]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile70, VALID__BASIC, FloatNum_t, "hobbies[4].nothingImportantHere", 0.0, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile71, VALID__BASIC, IntNum_t, "address.story", 789545, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithBasicFile72, VALID__BASIC, Bool_t, "hobbies[3].nestedHobby", true, true, JSON_DEFAULT_SEPARATORS);

            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile1, VALID__EDGE_CASES, String_t, "isThisAnObjec\\tt?::\\n:::,  ", "new string", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile2, VALID__EDGE_CASES, IntNum_t, "isThisAnObjec\\tt?::\\n:::,  ", 12345, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile3, VALID__EDGE_CASES, Bool_t, "isThisAnObjec\\tt?::\\n:::,  ", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile4, VALID__EDGE_CASES, FloatNum_t, "isThisAnObjec\\tt?::\\n:::,  ", 123.45, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile5, VALID__EDGE_CASES, Null_t, "isThisAnObjec\\tt?::\\n:::,  ", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile6, VALID__EDGE_CASES, String_t, "-12345", "new object", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile7, VALID__EDGE_CASES, IntNum_t, "-12345", 67890, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile8, VALID__EDGE_CASES, Bool_t, "-12345", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile9, VALID__EDGE_CASES, FloatNum_t, "-12345", 456.78, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile10, VALID__EDGE_CASES, Null_t, "-12345", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile11, VALID__EDGE_CASES, String_t, "78.40014", "new array", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile12, VALID__EDGE_CASES, IntNum_t, "78.40014", 98765, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile13, VALID__EDGE_CASES, Bool_t, "78.40014", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile14, VALID__EDGE_CASES, FloatNum_t, "78.40014", 789.01, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile15, VALID__EDGE_CASES, Null_t, "78.40014", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile16, VALID__EDGE_CASES, String_t, "78.40014[0]", "new element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile17, VALID__EDGE_CASES, IntNum_t, "78.40014[0]", 123, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile18, VALID__EDGE_CASES, Bool_t, "78.40014[0]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile19, VALID__EDGE_CASES, FloatNum_t, "78.40014[0]", 456.78, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile20, VALID__EDGE_CASES, Null_t, "78.40014[0]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile21, VALID__EDGE_CASES, String_t, "78.40014[1]", "another element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile22, VALID__EDGE_CASES, IntNum_t, "78.40014[1]", 456, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile23, VALID__EDGE_CASES, Bool_t, "78.40014[1]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile24, VALID__EDGE_CASES, FloatNum_t, "78.40014[1]", 789.01, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile25, VALID__EDGE_CASES, Null_t, "78.40014[1]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile26, VALID__EDGE_CASES, String_t, "78.40014[0]", "yet another element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile27, VALID__EDGE_CASES, IntNum_t, "78.40014[1]", 789, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile28, VALID__EDGE_CASES, Bool_t, "78.40014[0]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile29, VALID__EDGE_CASES, FloatNum_t, "78.40014[1]", 123.45, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile30, VALID__EDGE_CASES, Null_t, "78.40014[0]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile31, VALID__EDGE_CASES, String_t, "78.40014[0]", "final element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile32, VALID__EDGE_CASES, IntNum_t, "78.40014[0]", 101112, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile33, VALID__EDGE_CASES, Bool_t, "78.40014[0]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile34, VALID__EDGE_CASES, FloatNum_t, "78.40014[0]", 456.78, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile35, VALID__EDGE_CASES, Null_t, "78.40014[0]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile36, VALID__EDGE_CASES, String_t, "78.40014[1]", "extra element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile37, VALID__EDGE_CASES, IntNum_t, "78.40014[1]", 131415, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile38, VALID__EDGE_CASES, Bool_t, "78.40014[1]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile39, VALID__EDGE_CASES, FloatNum_t, "78.40014[1]", 789.01, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile40, VALID__EDGE_CASES, Null_t, "78.40014[1]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile41, VALID__EDGE_CASES, String_t, "78.40014[0]", "last element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile42, VALID__EDGE_CASES, IntNum_t, "78.40014[0]", 161718, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile43, VALID__EDGE_CASES, Bool_t, "78.40014[0]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile44, VALID__EDGE_CASES, FloatNum_t, "78.40014[0]", 123.45, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile45, VALID__EDGE_CASES, Null_t, "78.40014[0]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile46, VALID__EDGE_CASES, String_t, "78.40014[1]", "final final element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile47, VALID__EDGE_CASES, IntNum_t, "78.40014[1]", 192021, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile48, VALID__EDGE_CASES, Bool_t, "78.40014[1]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile49, VALID__EDGE_CASES, FloatNum_t, "78.40014[1]", 456.78, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile50, VALID__EDGE_CASES, Null_t, "78.40014[1]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile51, VALID__EDGE_CASES, String_t, "78.40014[0]", "extra extra element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile52, VALID__EDGE_CASES, IntNum_t, "78.40014[0]", 222324, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile53, VALID__EDGE_CASES, Bool_t, "78.40014[0]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile54, VALID__EDGE_CASES, FloatNum_t, "78.40014[0]", 789.01, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile55, VALID__EDGE_CASES, Null_t, "78.40014[0]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile56, VALID__EDGE_CASES, String_t, "78.40014[1]", "final final final element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile57, VALID__EDGE_CASES, IntNum_t, "78.40014[1]", 252627, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile58, VALID__EDGE_CASES, Bool_t, "78.40014[1]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile59, VALID__EDGE_CASES, FloatNum_t, "78.40014[1]", 123.45, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile60, VALID__EDGE_CASES, Null_t, "78.40014[1]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile61, VALID__EDGE_CASES, String_t, "78.40014[0]", "extra extra extra element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile62, VALID__EDGE_CASES, IntNum_t, "78.40014[0]", 282930, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile63, VALID__EDGE_CASES, Bool_t, "78.40014[0]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile64, VALID__EDGE_CASES, FloatNum_t, "78.40014[0]", 456.78, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile65, VALID__EDGE_CASES, Null_t, "78.40014[0]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile66, VALID__EDGE_CASES, String_t, "78.40014[1]", "final final final final element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile67, VALID__EDGE_CASES, IntNum_t, "78.40014[1]", 313233, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile68, VALID__EDGE_CASES, Bool_t, "78.40014[1]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile69, VALID__EDGE_CASES, FloatNum_t, "78.40014[1]", 789.01, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile70, VALID__EDGE_CASES, Null_t, "78.40014[1]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile71, VALID__EDGE_CASES, String_t, "iamanormalkey[0]<0>", "testing_hard_test_case", true, (std::array<std::string, 3>{".", "<", ">"}));
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile72, VALID__EDGE_CASES, IntNum_t, "iamanormalkey[0]<0>", 74, true, (std::array<std::string, 3>{".", "<", ">"}));
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithEdgeCasesFile73, VALID__EDGE_CASES, IntNum_t, "iamanormalkey[0]<1>", 74, true, (std::array<std::string, 3>{".", "<", ">"}));

            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithLargeFile1, VALID__LARGE, IntNum_t, "[0]age", 30, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithLargeFile2, VALID__LARGE, String_t, "[15]name", "John Doe", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithLargeFile3, VALID__LARGE, Bool_t, "[13]isActive", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithLargeFile4, VALID__LARGE, FloatNum_t, "[9]latitude", 45.123456, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithLargeFile5, VALID__LARGE, FloatNum_t, "[9]friends[0].specialFriend", 78487.2635, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithLargeFile6, VALID__LARGE, String_t, "[9]friends[0].specialFriend.secondName", "yoyo", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithLargeFile7, VALID__LARGE, Null_t, "[9]friends[0].specialFriend.secondName", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithLargeFile8, VALID__LARGE, IntNum_t, "[9]friends[2]", 88, true, JSON_DEFAULT_SEPARATORS);

            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile1, VALID__NESTED, String_t, "name", "Jane Doe", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile2, VALID__NESTED, IntNum_t, "age", 35, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile3, VALID__NESTED, Bool_t, "isStudent", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile4, VALID__NESTED, FloatNum_t, "age", 30.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile5, VALID__NESTED, Null_t, "email", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile6, VALID__NESTED, String_t, "address.street", "456 Elm St", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile7, VALID__NESTED, IntNum_t, "grades.math", 90, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile8, VALID__NESTED, Bool_t, "grades.math", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile9, VALID__NESTED, FloatNum_t, "grades.math", 85.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile10, VALID__NESTED, Null_t, "grades.english", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile11, VALID__NESTED, String_t, "phone", "+1 987-654-3210", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile12, VALID__NESTED, IntNum_t, "grades.history", 80, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile13, VALID__NESTED, Bool_t, "grades.history", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile14, VALID__NESTED, FloatNum_t, "grades.history", 78.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile15, VALID__NESTED, Null_t, "grades.math", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile16, VALID__NESTED, String_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested", "false", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile17, VALID__NESTED, IntNum_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 100, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile18, VALID__NESTED, Bool_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile19, VALID__NESTED, FloatNum_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 42.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile20, VALID__NESTED, Null_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile21, VALID__NESTED, String_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", "New Value", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile22, VALID__NESTED, IntNum_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 200, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile23, VALID__NESTED, Bool_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile24, VALID__NESTED, FloatNum_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 84.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile25, VALID__NESTED, Null_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile26, VALID__NESTED, String_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", "Another Value", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile27, VALID__NESTED, IntNum_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 300, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile28, VALID__NESTED, Bool_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile29, VALID__NESTED, FloatNum_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 126.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile30, VALID__NESTED, Null_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile31, VALID__NESTED, String_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", "Final Value", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile32, VALID__NESTED, IntNum_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 400, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile33, VALID__NESTED, Bool_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile34, VALID__NESTED, FloatNum_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 168.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile35, VALID__NESTED, Null_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile36, VALID__NESTED, String_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", "Ultimate Value", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile37, VALID__NESTED, IntNum_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 500, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile38, VALID__NESTED, Bool_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile39, VALID__NESTED, FloatNum_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 210.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile40, VALID__NESTED, Null_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile41, VALID__NESTED, Null_t, "nestedData.level1", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile42, VALID__NESTED, String_t, "nestedData.level1", "no", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWithNestedFile43, VALID__NESTED, FloatNum_t, "nestedData.level1", 158.69789452014, true, JSON_DEFAULT_SEPARATORS);
            
            // Testing when inserting new keys
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWhenInsertingNewKeyAndValueWithBasicFile1, VALID__BASIC, FloatNum_t, "newKey", 45.223, false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWhenInsertingNewKeyAndValueWithBasicFile2, VALID__BASIC, Null_t, "hobbies[5]", nullptr, false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWhenInsertingNewKeyAndValueWithBasicFile3, VALID__BASIC, Bool_t, "address.story.secondAddress", false, false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWhenInsertingNewKeyAndValueWithEdgeCasesFile1, VALID__EDGE_CASES, String_t, "78/an.other.[ke.y]<2>", "true", false, (std::array<std::string, 3>{"/", "<", ">"}));
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWhenInsertingNewKeyAndValueWithEdgeCasesFile2, VALID__EDGE_CASES, IntNum_t, "78/an.other.[ke.y]<1>/ohehe", 897800001, false, (std::array<std::string, 3>{"/", "<", ">"}));
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWhenInsertingNewKeyAndValueWithLargeFile1, VALID__LARGE, String_t, "[14]", "hello", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWhenInsertingNewKeyAndValueWithLargeFile2, VALID__LARGE, FloatNum_t, "[14]", 46.56007, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWhenInsertingNewKeyAndValueWithNestedFile1, VALID__NESTED, Bool_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(newValueShouldBeEqualWhenInsertingNewKeyAndValueWithNestedFile2, VALID__NESTED, FloatNum_t, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", 472.356, true, JSON_DEFAULT_SEPARATORS);

#undef _CREATE_RETURNED_VALUE_TEST

        } // namespace Json
    } // namespace jsonio
} // namespace test

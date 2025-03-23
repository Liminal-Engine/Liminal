/**
 * @file insert.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
*/

// //**********
// // Incudes required for OutJson internal calls TODO : remove this ?
#include "jsonio/include/_private/_lexing/_types.hpp"
#include "jsonio/include/_private/_lexing/_lexing.hpp"
// //**********

#include "jsonio/OutJson.hpp"
#include "jsonio/is_in_variant_v.hpp"
#include "jsonio/types.hpp"

#include "test/jsonio/Helper.hpp"
#include "test/jsonio/OutJson/Helper.hpp"

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

/**
 * TODO : 
 * 1. tester ajouter clée et value simples erase = true -> returned value
 * 3. tester ajouter clée et value simples erase = false -> returned value
 * retester tout ça mais sans ouvrir un json existant cette fois ci
 * when givven invalid file
 * tester avec jsonPath = "" simple et complex values
 * tester sans création de fichier
 * s'assurer que tous les returns de d'appells de fonctions internes soient bien tester
*/

namespace test {
    namespace jsonio {
        namespace OutJson {


                class JsonIOOutJsonInsertMethodReturnedStatus: public ::testing::Test
                {
                    private:
                        ::jsonio::OutJson _instance;

                    protected:

                        void create(const std::string &filePath = "") { // if file path is empty, no file will be parsed
                            if ( !filePath.empty() ) this->_instance.parse(::fs::Path(filePath));
                        };

                        template<typename T>
                        requires ::jsonio::is_in_variant_v<T, ::jsonio::types::Any_t>
                        void test_returned_value(
                            const ::jsonio::Status &expectedResult,
                            const std::string &jsonPath = "",
                            const T &value = nullptr,
                            const bool &erase = false,
                            const std::array<std::string, 3> &separators = JSON_DEFAULT_SEPARATORS
                        ) {
                            ::jsonio::Status returnedStatus = this->_instance.insert<T>(jsonPath, value, erase, separators);
                            EXPECT_EQ(returnedStatus, expectedResult);
                        }
                };

#define _CREATE_RETURNED_VALUE_TEST(testName, fileName, jsonIOType, expectedStatus, jsonPath, value, erase, separators) \
    TEST_F(JsonIOOutJsonInsertMethodReturnedStatus, testName) { \
        create(::test::jsonio::Helper::fileName.asStr()); \
        test_returned_value<::jsonio::types::jsonIOType>(::jsonio::Status::expectedStatus, jsonPath, value, erase, separators); \
    }
            

            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile1, VALID__BASIC, IntNum_t, OK, "name", 8, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile2, VALID__BASIC, String_t, OK, "address.story.right", "yoyo", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile3, VALID__BASIC, Null_t, OK, "address.state", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile4, VALID__BASIC, FloatNum_t, OK, "hobbies[4].secondNestedHobbies", 0.23, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile5, VALID__BASIC, Bool_t, OK, "hobbies[4].secondNestedHobbies[3]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile6, VALID__BASIC, FloatNum_t, OK, "hobbies", 178.555556f, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile7, VALID__BASIC, FloatNum_t, OK, "address", 457888720, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile8, VALID__BASIC, IntNum_t, OK, "age", 25, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile9, VALID__BASIC, String_t, OK, "address.city", "New York", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile10, VALID__BASIC, Bool_t, OK, "isEmployed", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile11, VALID__BASIC, FloatNum_t, OK, "address.story.left", 20.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile12, VALID__BASIC, Null_t, OK, "address.anotherData", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile13, VALID__BASIC, String_t, OK, "address.street", "456 Elm St", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile14, VALID__BASIC, IntNum_t, OK, "address.postalCode", 54321, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile15, VALID__BASIC, Bool_t, OK, "happy", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile16, VALID__BASIC, FloatNum_t, OK, "address.story.right", 700.75, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile17, VALID__BASIC, String_t, OK, "hobbies[0]", "swimming", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile18, VALID__BASIC, IntNum_t, OK, "hobbies[4].secondNestedHobbies[2]", 4, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile19, VALID__BASIC, Bool_t, OK, "hobbies[4].nothingImportantHere", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile20, VALID__BASIC, FloatNum_t, OK, "address.anotherData", 50.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile21, VALID__BASIC, String_t, OK, "hobbies[3].nestedHobby", "yes", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile22, VALID__BASIC, IntNum_t, OK, "age", 35, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile23, VALID__BASIC, Bool_t, OK, "isEmployed", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile24, VALID__BASIC, FloatNum_t, OK, "address.story.left", 10.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile25, VALID__BASIC, String_t, OK, "address.city", "Oldtown", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile26, VALID__BASIC, IntNum_t, OK, "address.postalCode", 67890, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile27, VALID__BASIC, Bool_t, OK, "happy", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile28, VALID__BASIC, FloatNum_t, OK, "address.story.right", 800.25, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile29, VALID__BASIC, String_t, OK, "hobbies[1]", "coding", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile30, VALID__BASIC, IntNum_t, OK, "hobbies[4].secondNestedHobbies[2]", 5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile31, VALID__BASIC, Bool_t, OK, "hobbies[4].nothingImportantHere", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile32, VALID__BASIC, FloatNum_t, OK, "address.anotherData", 60.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile33, VALID__BASIC, String_t, OK, "hobbies[3].nestedHobby", "maybe", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile34, VALID__BASIC, IntNum_t, OK, "age", 40, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile35, VALID__BASIC, Bool_t, OK, "isEmployed", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile36, VALID__BASIC, FloatNum_t, OK, "address.story.left", 5.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile37, VALID__BASIC, String_t, OK, "address.city", "Smalltown", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile38, VALID__BASIC, IntNum_t, OK, "address.postalCode", 98765, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile39, VALID__BASIC, Bool_t, OK, "happy", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile40, VALID__BASIC, FloatNum_t, OK, "address.story.right", 900.75, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile41, VALID__BASIC, String_t, OK, "name", "Jane Doe", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile42, VALID__BASIC, FloatNum_t, OK, "age", 30.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile43, VALID__BASIC, IntNum_t, OK, "isEmployed", 1, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile44, VALID__BASIC, String_t, OK, "address", "New Address", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile45, VALID__BASIC, Bool_t, OK, "address.story", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile46, VALID__BASIC, FloatNum_t, OK, "address.story.left", 30.0, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile47, VALID__BASIC, IntNum_t, OK, "address.story.right", 100, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile48, VALID__BASIC, String_t, OK, "address.street", "789 Pine St", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile49, VALID__BASIC, FloatNum_t, OK, "address.city", 123.45, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile50, VALID__BASIC, IntNum_t, OK, "address.state", 50, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile51, VALID__BASIC, Bool_t, OK, "address.postalCode", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile52, VALID__BASIC, String_t, OK, "address.anotherData", "Data", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile53, VALID__BASIC, IntNum_t, OK, "hobbies", 5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile54, VALID__BASIC, FloatNum_t, OK, "hobbies[0]", 1.1, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile55, VALID__BASIC, Bool_t, OK, "hobbies[1]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile56, VALID__BASIC, String_t, OK, "hobbies[2]", "new hobby", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile57, VALID__BASIC, IntNum_t, OK, "hobbies[3]", 10, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile58, VALID__BASIC, FloatNum_t, OK, "hobbies[4]", 20.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile59, VALID__BASIC, String_t, OK, "hobbies[4].secondNestedHobbies", "nested", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile60, VALID__BASIC, IntNum_t, OK, "hobbies[4].nothingImportantHere", 0, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile61, VALID__BASIC, Bool_t, OK, "happy", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile62, VALID__BASIC, FloatNum_t, OK, "happy", 1.0, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile63, VALID__BASIC, IntNum_t, OK, "happy", 1, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile64, VALID__BASIC, String_t, OK, "address.story.left", "left", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile65, VALID__BASIC, Bool_t, OK, "address.story.right", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile66, VALID__BASIC, FloatNum_t, OK, "address.story", 123.45, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile67, VALID__BASIC, IntNum_t, OK, "address", 12345, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile68, VALID__BASIC, String_t, OK, "hobbies", "new hobbies", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile69, VALID__BASIC, Bool_t, OK, "hobbies[4].secondNestedHobbies[2]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile70, VALID__BASIC, FloatNum_t, OK, "hobbies[4].nothingImportantHere", 0.0, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile71, VALID__BASIC, IntNum_t, OK, "address.story", 789545, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile72, VALID__BASIC, Bool_t, OK, "hobbies[3].nestedHobby", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFile73, VALID__BASIC, Object_t, OK, "hobbies[4]", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);

            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile1, VALID__EDGE_CASES, String_t, OK, "isThisAnObjec\\tt?::\\n:::,  ", "new string", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile2, VALID__EDGE_CASES, IntNum_t, OK, "isThisAnObjec\\tt?::\\n:::,  ", 12345, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile3, VALID__EDGE_CASES, Bool_t, OK, "isThisAnObjec\\tt?::\\n:::,  ", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile4, VALID__EDGE_CASES, FloatNum_t, OK, "isThisAnObjec\\tt?::\\n:::,  ", 123.45, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile5, VALID__EDGE_CASES, Null_t, OK, "isThisAnObjec\\tt?::\\n:::,  ", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile6, VALID__EDGE_CASES, String_t, OK, "-12345", "new object", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile7, VALID__EDGE_CASES, IntNum_t, OK, "-12345", 67890, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile8, VALID__EDGE_CASES, Bool_t, OK, "-12345", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile9, VALID__EDGE_CASES, FloatNum_t, OK, "-12345", 456.78, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile10, VALID__EDGE_CASES, Null_t, OK, "-12345", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile11, VALID__EDGE_CASES, String_t, OK, "78.40014", "new array", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile12, VALID__EDGE_CASES, IntNum_t, OK, "78.40014", 98765, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile13, VALID__EDGE_CASES, Bool_t, OK, "78.40014", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile14, VALID__EDGE_CASES, FloatNum_t, OK, "78.40014", 789.01, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile15, VALID__EDGE_CASES, Null_t, OK, "78.40014", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile16, VALID__EDGE_CASES, String_t, OK, "78.40014[0]", "new element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile17, VALID__EDGE_CASES, IntNum_t, OK, "78.40014[0]", 123, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile18, VALID__EDGE_CASES, Bool_t, OK, "78.40014[0]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile19, VALID__EDGE_CASES, FloatNum_t, OK, "78.40014[0]", 456.78, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile20, VALID__EDGE_CASES, Null_t, OK, "78.40014[0]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile21, VALID__EDGE_CASES, String_t, OK, "78.40014[1]", "another element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile22, VALID__EDGE_CASES, IntNum_t, OK, "78.40014[1]", 456, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile23, VALID__EDGE_CASES, Bool_t, OK, "78.40014[1]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile24, VALID__EDGE_CASES, FloatNum_t, OK, "78.40014[1]", 789.01, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile25, VALID__EDGE_CASES, Null_t, OK, "78.40014[1]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile26, VALID__EDGE_CASES, String_t, OK, "78.40014[0]", "yet another element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile27, VALID__EDGE_CASES, IntNum_t, OK, "78.40014[1]", 789, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile28, VALID__EDGE_CASES, Bool_t, OK, "78.40014[0]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile29, VALID__EDGE_CASES, FloatNum_t, OK, "78.40014[1]", 123.45, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile30, VALID__EDGE_CASES, Null_t, OK, "78.40014[0]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile31, VALID__EDGE_CASES, String_t, OK, "78.40014[0]", "final element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile32, VALID__EDGE_CASES, IntNum_t, OK, "78.40014[0]", 101112, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile33, VALID__EDGE_CASES, Bool_t, OK, "78.40014[0]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile34, VALID__EDGE_CASES, FloatNum_t, OK, "78.40014[0]", 456.78, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile35, VALID__EDGE_CASES, Null_t, OK, "78.40014[0]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile36, VALID__EDGE_CASES, String_t, OK, "78.40014[1]", "extra element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile37, VALID__EDGE_CASES, IntNum_t, OK, "78.40014[1]", 131415, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile38, VALID__EDGE_CASES, Bool_t, OK, "78.40014[1]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile39, VALID__EDGE_CASES, FloatNum_t, OK, "78.40014[1]", 789.01, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile40, VALID__EDGE_CASES, Null_t, OK, "78.40014[1]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile41, VALID__EDGE_CASES, String_t, OK, "78.40014[0]", "last element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile42, VALID__EDGE_CASES, IntNum_t, OK, "78.40014[0]", 161718, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile43, VALID__EDGE_CASES, Bool_t, OK, "78.40014[0]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile44, VALID__EDGE_CASES, FloatNum_t, OK, "78.40014[0]", 123.45, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile45, VALID__EDGE_CASES, Null_t, OK, "78.40014[0]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile46, VALID__EDGE_CASES, String_t, OK, "78.40014[1]", "final final element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile47, VALID__EDGE_CASES, IntNum_t, OK, "78.40014[1]", 192021, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile48, VALID__EDGE_CASES, Bool_t, OK, "78.40014[1]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile49, VALID__EDGE_CASES, FloatNum_t, OK, "78.40014[1]", 456.78, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile50, VALID__EDGE_CASES, Null_t, OK, "78.40014[1]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile51, VALID__EDGE_CASES, String_t, OK, "78.40014[0]", "extra extra element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile52, VALID__EDGE_CASES, IntNum_t, OK, "78.40014[0]", 222324, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile53, VALID__EDGE_CASES, Bool_t, OK, "78.40014[0]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile54, VALID__EDGE_CASES, FloatNum_t, OK, "78.40014[0]", 789.01, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile55, VALID__EDGE_CASES, Null_t, OK, "78.40014[0]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile56, VALID__EDGE_CASES, String_t, OK, "78.40014[1]", "final final final element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile57, VALID__EDGE_CASES, IntNum_t, OK, "78.40014[1]", 252627, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile58, VALID__EDGE_CASES, Bool_t, OK, "78.40014[1]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile59, VALID__EDGE_CASES, FloatNum_t, OK, "78.40014[1]", 123.45, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile60, VALID__EDGE_CASES, Null_t, OK, "78.40014[1]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile61, VALID__EDGE_CASES, String_t, OK, "78.40014[0]", "extra extra extra element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile62, VALID__EDGE_CASES, IntNum_t, OK, "78.40014[0]", 282930, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile63, VALID__EDGE_CASES, Bool_t, OK, "78.40014[0]", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile64, VALID__EDGE_CASES, FloatNum_t, OK, "78.40014[0]", 456.78, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile65, VALID__EDGE_CASES, Null_t, OK, "78.40014[0]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile66, VALID__EDGE_CASES, String_t, OK, "78.40014[1]", "final final final final element", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile67, VALID__EDGE_CASES, IntNum_t, OK, "78.40014[1]", 313233, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile68, VALID__EDGE_CASES, Bool_t, OK, "78.40014[1]", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile69, VALID__EDGE_CASES, FloatNum_t, OK, "78.40014[1]", 789.01, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile70, VALID__EDGE_CASES, Null_t, OK, "78.40014[1]", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile71, VALID__EDGE_CASES, String_t, OK, "iamanormalkey[0]<0>", "testing_hard_test_case", true, (std::array<std::string, 3>{".", "<", ">"}));
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile72, VALID__EDGE_CASES, IntNum_t, OK, "iamanormalkey[0]<0>", 74, true, (std::array<std::string, 3>{".", "<", ">"}));
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFile73, VALID__EDGE_CASES, IntNum_t, OK, "iamanormalkey[0]<1>", 74, true, (std::array<std::string, 3>{".", "<", ">"}));

            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithLargeFile1, VALID__LARGE, IntNum_t, OK, "[0]age", 30, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithLargeFile2, VALID__LARGE, String_t, OK, "[15]name", "John Doe", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithLargeFile3, VALID__LARGE, Bool_t, OK, "[13]isActive", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithLargeFile4, VALID__LARGE, FloatNum_t, OK, "[9]latitude", 45.123456, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithLargeFile5, VALID__LARGE, FloatNum_t, OK, "[9]friends[0].specialFriend", 78487.2635, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithLargeFile6, VALID__LARGE, String_t, OK, "[9]friends[0].specialFriend.secondName", "yoyo", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithLargeFile7, VALID__LARGE, Null_t, OK, "[9]friends[0].specialFriend.secondName", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithLargeFile8, VALID__LARGE, IntNum_t, OK, "[9]friends[2]", 88, true, JSON_DEFAULT_SEPARATORS);

            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile1, VALID__NESTED, String_t, OK, "name", "Jane Doe", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile2, VALID__NESTED, IntNum_t, OK, "age", 35, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile3, VALID__NESTED, Bool_t, OK, "isStudent", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile4, VALID__NESTED, FloatNum_t, OK, "age", 30.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile5, VALID__NESTED, Null_t, OK, "email", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile6, VALID__NESTED, String_t, OK, "address.street", "456 Elm St", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile7, VALID__NESTED, IntNum_t, OK, "grades.math", 90, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile8, VALID__NESTED, Bool_t, OK, "grades.math", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile9, VALID__NESTED, FloatNum_t, OK, "grades.math", 85.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile10, VALID__NESTED, Null_t, OK, "grades.english", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile11, VALID__NESTED, String_t, OK, "phone", "+1 987-654-3210", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile12, VALID__NESTED, IntNum_t, OK, "grades.history", 80, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile13, VALID__NESTED, Bool_t, OK, "grades.history", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile14, VALID__NESTED, FloatNum_t, OK, "grades.history", 78.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile15, VALID__NESTED, Null_t, OK, "grades.math", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile16, VALID__NESTED, String_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested", "false", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile17, VALID__NESTED, IntNum_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 100, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile18, VALID__NESTED, Bool_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile19, VALID__NESTED, FloatNum_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 42.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile20, VALID__NESTED, Null_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile21, VALID__NESTED, String_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", "New Value", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile22, VALID__NESTED, IntNum_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 200, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile23, VALID__NESTED, Bool_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile24, VALID__NESTED, FloatNum_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 84.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile25, VALID__NESTED, Null_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile26, VALID__NESTED, String_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", "Another Value", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile27, VALID__NESTED, IntNum_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 300, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile28, VALID__NESTED, Bool_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile29, VALID__NESTED, FloatNum_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 126.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile30, VALID__NESTED, Null_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile31, VALID__NESTED, String_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", "Final Value", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile32, VALID__NESTED, IntNum_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 400, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile33, VALID__NESTED, Bool_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", true, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile34, VALID__NESTED, FloatNum_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 168.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile35, VALID__NESTED, Null_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile36, VALID__NESTED, String_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", "Ultimate Value", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile37, VALID__NESTED, IntNum_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 500, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile38, VALID__NESTED, Bool_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", false, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile39, VALID__NESTED, FloatNum_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", 210.5, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile40, VALID__NESTED, Null_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile41, VALID__NESTED, Null_t, OK, "nestedData.level1", nullptr, true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile42, VALID__NESTED, String_t, OK, "nestedData.level1", "no", true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFile43, VALID__NESTED, FloatNum_t, OK, "nestedData.level1", 158.69789452014, true, JSON_DEFAULT_SEPARATORS);

            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue1, VALID__BASIC, Object_t, OK, "address.story.right", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue2, VALID__BASIC, Array_t, OK, "hobbies[1]", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue3, VALID__BASIC, Object_t, OK, "hobbies[4].secondNestedHobbies[2]", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue4, VALID__BASIC, Array_t, OK, "hobbies[4].nothingImportantHere", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue5, VALID__BASIC, Object_t, OK, "address.anotherData", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue6, VALID__BASIC, Array_t, OK, "hobbies[3].nestedHobby", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue7, VALID__BASIC, Object_t, OK, "age", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue8, VALID__BASIC, Array_t, OK, "isEmployed", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue9, VALID__BASIC, Object_t, OK, "address.story.left", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue10, VALID__BASIC, Array_t, OK, "address.city", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue11, VALID__BASIC, Object_t, OK, "address.postalCode", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue12, VALID__BASIC, Array_t, OK, "happy", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue13, VALID__BASIC, Object_t, OK, "address.story.right", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue15, VALID__BASIC, Array_t, OK, "name", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue16, VALID__BASIC, Object_t, OK, "age", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue17, VALID__BASIC, Object_t, OK, "isEmployed", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue18, VALID__BASIC, Array_t, OK, "address", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue19, VALID__BASIC, Array_t, OK, "address.story", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue20, VALID__BASIC, Object_t, OK, "address.story.left", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue21, VALID__BASIC, Object_t, OK, "address.story.right", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue22, VALID__BASIC, Array_t, OK, "address.street", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue23, VALID__BASIC, Object_t, OK, "address.city", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue24, VALID__BASIC, Object_t, OK, "address.state", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithBasicFileAndComplexValue25, VALID__BASIC, Array_t, OK, "address.postalCode", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithLargeFileAndComplexValue1, VALID__LARGE, Array_t, OK, "[0]age", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFileAndComplexValue1, VALID__EDGE_CASES, Array_t, OK, "iamanormalkey[0]<1>", ::jsonio::types::Array_t(), true, (std::array<std::string, 3>{".", "<", ">"}));
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithEdgeCasesFileAndComplexValue2, VALID__EDGE_CASES, Object_t, OK, "iamanormalkey[0]<1>", ::jsonio::types::Object_t(), true, (std::array<std::string, 3>{".", "<", ">"}));

            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWithNestedFileAndComplexValue1, VALID__NESTED, Object_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);

            // Testing when inserting new keys
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWhenInsertingNewKeyAndValueWithBasicFile1, VALID__BASIC, FloatNum_t, OK, "newKey", 45.223, false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWhenInsertingNewKeyAndValueWithBasicFile2, VALID__BASIC, Object_t, OK, "hobbies[5]", ::jsonio::types::Object_t(), false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWhenInsertingNewKeyAndValueWithBasicFile3, VALID__BASIC, Bool_t, OK, "address.story.secondAddress", false, false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWhenInsertingNewKeyAndValueWithEdgeCasesFile1, VALID__EDGE_CASES, String_t, OK, "78/an.other.[ke.y]<2>", "true", false, (std::array<std::string, 3>{"/", "<", ">"}));
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWhenInsertingNewKeyAndValueWithEdgeCasesFile2, VALID__EDGE_CASES, IntNum_t, OK, "78/an.other.[ke.y]<1>/ohehe", 897800001, false, (std::array<std::string, 3>{"/", "<", ">"}));
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWhenInsertingNewKeyAndValueWithLargeFile1, VALID__LARGE, Object_t, OK, "[14]", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWhenInsertingNewKeyAndValueWithLargeFile2, VALID__LARGE, Array_t, OK, "[14]", ::jsonio::types::Array_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWhenInsertingNewKeyAndValueWithLargeFile3, VALID__LARGE, Object_t, OK, "", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWhenInsertingNewKeyAndValueWithNestedFile1, VALID__NESTED, Object_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWhenInsertingNewKeyAndValueWithNestedFile2, VALID__NESTED, FloatNum_t, OK, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", 472.356, true, JSON_DEFAULT_SEPARATORS);

            // Testing when inserting too many new keys
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnErrorWhenInsertingInTooManyKeyOrIndexDepthWithBasicFile1, VALID__BASIC, FloatNum_t, E_JSON_PATH, "newKey.secondNewKey", 45.223, false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnErrorWhenInsertingInTooManyKeyOrIndexDepthWithBasicFile2, VALID__BASIC, Object_t, E_INDEX, "hobbies[6]", ::jsonio::types::Object_t(), false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnErrorWhenInsertingInTooManyKeyOrIndexDepthWithBasicFile3, VALID__BASIC, Bool_t, E_JSON_PATH, "address.story.secondAddress.thirdAddress.fourthAddress", false, false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnErrorWhenInsertingInTooManyKeyOrIndexDepthWithEdgeCasesFile1, VALID__EDGE_CASES, String_t, E_INDEX, "78/an.other.[ke.y]<3>", "true", false, (std::array<std::string, 3>{"/", "<", ">"}));
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnErrorWhenInsertingInTooManyKeyOrIndexDepthWithEdgeCasesFile2, VALID__EDGE_CASES, IntNum_t, E_JSON_PATH, "78/an.other.[ke.y]<1>/ohehe/yaya", 897800001, false, (std::array<std::string, 3>{"/", "<", ">"}));
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnErrorWhenInsertingInTooManyKeyOrIndexDepthWithLargeFile1, VALID__LARGE, Object_t, E_INDEX, "[17]", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnErrorWhenInsertingInTooManyKeyOrIndexDepthWithLargeFile2, VALID__LARGE, Object_t, E_INDEX, "[14].friends[4]", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnErrorWhenInsertingInTooManyKeyOrIndexDepthWithNestedFile1, VALID__NESTED, Object_t, E_JSON_PATH, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.level22.randomKey1", ::jsonio::types::Object_t(), true, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnErrorWhenInsertingInTooManyKeyOrIndexDepthWithNestedFile2, VALID__NESTED, FloatNum_t, E_JSON_PATH, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey4.randomKey5", 472.356, true, JSON_DEFAULT_SEPARATORS);

            // Testing when point to existing value but not erasing it

            _CREATE_RETURNED_VALUE_TEST(ShouldReturnEValueExistsWithBasicFile1, VALID__BASIC, IntNum_t, E_VALUE_EXISTS, "name", 8, false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnEValueExistsWithBasicFile2, VALID__BASIC, String_t, E_VALUE_EXISTS, "address.story.right", "yoyo", false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnEValueExistsWithBasicFile3, VALID__BASIC, Null_t, E_VALUE_EXISTS, "address.state", nullptr, false, JSON_DEFAULT_SEPARATORS);
            
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnEValueExistsWithNestedFile1, VALID__NESTED, Bool_t, E_VALUE_EXISTS, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", false, false, JSON_DEFAULT_SEPARATORS);
            
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnEValueExistsWithEdgeCasesFile1, VALID__EDGE_CASES, String_t, E_VALUE_EXISTS, "iamanormalkey[0]<0>", "testing_hard_test_case", false, (std::array<std::string, 3>{".", "<", ">"}));

            _CREATE_RETURNED_VALUE_TEST(ShouldReturnEValueExistsWithEdgeCasesAndComplexValueFile1, VALID__EDGE_CASES, Array_t, E_VALUE_EXISTS, "iamanormalkey[0]<0>", ::jsonio::types::Array_t(), false, (std::array<std::string, 3>{".", "<", ">"}));

            // Testing on empty file
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWhenInsertingObjectOrArrayOnRootOnEmptyFile1, VALID__EMPTY, Object_t, OK, "", ::jsonio::types::Object_t(), false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnOKWhenInsertingObjectOrArrayOnRootOnEmptyFile2, VALID__EMPTY, Array_t, OK, "", ::jsonio::types::Array_t(), false, JSON_DEFAULT_SEPARATORS);

            _CREATE_RETURNED_VALUE_TEST(ShouldReturnETypeWhenInsertingSimpleValueOnRootOnEmptyFile1, VALID__EMPTY, IntNum_t, E_TYPE, "", 45, false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnETypeWhenInsertingSimpleValueOnRootOnEmptyFile2, VALID__EMPTY, FloatNum_t, E_TYPE, "", 45.46, false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnETypeWhenInsertingSimpleValueOnRootOnEmptyFile3, VALID__EMPTY, String_t, E_TYPE, "", "hello world!", false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnETypeWhenInsertingSimpleValueOnRootOnEmptyFile4, VALID__EMPTY, Bool_t, E_TYPE, "", false, false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnETypeWhenInsertingSimpleValueOnRootOnEmptyFile5, VALID__EMPTY, Bool_t, E_TYPE, "", true, false, JSON_DEFAULT_SEPARATORS);
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnETypeWhenInsertingSimpleValueOnRootOnEmptyFile6, VALID__EMPTY, Null_t, E_TYPE, "", nullptr, false, JSON_DEFAULT_SEPARATORS);
            
            _CREATE_RETURNED_VALUE_TEST(ShouldReturnEJsonPathWhenInsertingSimpleValueOnRootOnEmptyFile1, VALID__EMPTY, String_t, E_JSON_PATH, "newKey", "hello world!", false, JSON_DEFAULT_SEPARATORS);

#undef _CREATE_RETURNED_VALUE_TEST

        } // namespace OutJson
    } // namespace jsonio
} // namespace test

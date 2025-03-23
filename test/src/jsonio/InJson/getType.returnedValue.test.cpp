/**
 * @file getType.returnedValue.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
*/


//**********
// Incudes required for InJson internal calls TODO : remove this ?
#include "jsonio/include/_private/_lexing/_types.hpp"
#include "jsonio/include/_private/_lexing/_lexing.hpp"
//**********

#include "test/jsonio/Helper.hpp"

#include <jsonio/InJson.hpp>
#include <jsonio/separators.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace test {
    namespace jsonio {
        namespace Injson {
            class JsonIOInJsonGetTypeMethodReturnedValue : public ::testing::Test {
                protected:
                    ::jsonio::InJson __instance;
                
                public:
                    JsonIOInJsonGetTypeMethodReturnedValue(void) :
                    __instance(::jsonio::InJson())
                    {}                
            };
    
    
    #define _CREATE_INJSON_GET_TYPE_METHOD_TEST(testName, fileName, jsonPath, separators, expectedValueType) \
        TEST_F(JsonIOInJsonGetTypeMethodReturnedValue, testName) { \
            if (__instance.parse(::test::jsonio::Helper::fileName) != ::jsonio::Status::OK) FAIL() << "Failed to parse file"; \
            EXPECT_EQ(__instance.getType(jsonPath, separators), ::jsonio::types::ValueTypes::expectedValueType); \
        };
    
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile1, VALID__BASIC, "", JSON_DEFAULT_SEPARATORS, OBJECT);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile2, VALID__BASIC, "name", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile3, VALID__BASIC, "age", JSON_DEFAULT_SEPARATORS, INT_NUM);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile4, VALID__BASIC, "isEmployed", JSON_DEFAULT_SEPARATORS, BOOL);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile5, VALID__BASIC, "address", JSON_DEFAULT_SEPARATORS, OBJECT);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile6, VALID__BASIC, "address.story", JSON_DEFAULT_SEPARATORS, OBJECT);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile7, VALID__BASIC, "address.story.left", JSON_DEFAULT_SEPARATORS, INT_NUM);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile8, VALID__BASIC, "address.story.right", JSON_DEFAULT_SEPARATORS, FLOAT_NUM);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile9, VALID__BASIC, "address.street", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile10, VALID__BASIC, "address.city", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile11, VALID__BASIC, "address.state", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile12, VALID__BASIC, "address.postalCode", JSON_DEFAULT_SEPARATORS, INT_NUM);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile13, VALID__BASIC, "address.anotherData", JSON_DEFAULT_SEPARATORS, FLOAT_NUM);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile14, VALID__BASIC, "hobbies", JSON_DEFAULT_SEPARATORS, ARRAY);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile15, VALID__BASIC, "hobbies[0]", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile16, VALID__BASIC, "hobbies[1]", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile17, VALID__BASIC, "hobbies[2]", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile18, VALID__BASIC, "hobbies[3]", JSON_DEFAULT_SEPARATORS, OBJECT);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile19, VALID__BASIC, "hobbies[3].nestedHobby", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile20, VALID__BASIC, "hobbies[4]", JSON_DEFAULT_SEPARATORS, OBJECT);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile21, VALID__BASIC, "hobbies[4].secondNestedHobbies", JSON_DEFAULT_SEPARATORS, ARRAY);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile22, VALID__BASIC, "hobbies[4].secondNestedHobbies[0]", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile23, VALID__BASIC, "hobbies[4].secondNestedHobbies[1]", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile24, VALID__BASIC, "hobbies[4].secondNestedHobbies[2]", JSON_DEFAULT_SEPARATORS, INT_NUM);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile25, VALID__BASIC, "hobbies[4].secondNestedHobbies[3]", JSON_DEFAULT_SEPARATORS, NULL_VALUE);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile26, VALID__BASIC, "hobbies[4].nothingImportantHere", JSON_DEFAULT_SEPARATORS, NULL_VALUE);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenBasicJsonFile27, VALID__BASIC, "happy", JSON_DEFAULT_SEPARATORS, STRING);
    
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile1, VALID__EDGE_CASES, "", JSON_DEFAULT_SEPARATORS, OBJECT);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile2, VALID__EDGE_CASES, "isThisAnObjec\\tt?::\\n:::,  ", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile3, VALID__EDGE_CASES, "-12345", JSON_DEFAULT_SEPARATORS, OBJECT);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile4, VALID__EDGE_CASES, "78.40014", (std::array<std::string, 3>{"/", "[", "]"}), ARRAY);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile5, VALID__EDGE_CASES, "78", JSON_DEFAULT_SEPARATORS, OBJECT);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile6, VALID__EDGE_CASES, "78.40014", JSON_DEFAULT_SEPARATORS, ARRAY);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile7, VALID__EDGE_CASES, "78.40014[0]", JSON_DEFAULT_SEPARATORS, OBJECT);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile8, VALID__EDGE_CASES, "78.40014[0].yes", JSON_DEFAULT_SEPARATORS, ARRAY);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile9, VALID__EDGE_CASES, "78.40014[0].yes[0]", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile10, VALID__EDGE_CASES, "78.40014[0].yes[1]", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile11, VALID__EDGE_CASES, "78.40014[0].yes[2]", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile12, VALID__EDGE_CASES, "78/an.other.[ke.y]", (std::array<std::string, 3>{"/", "<", ">"}), ARRAY);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile13, VALID__EDGE_CASES, "78/an.other.[ke.y]<0>/yes", (std::array<std::string, 3>{"/", "<", ">"}), STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenEdgeCasesJsonFile14, VALID__EDGE_CASES, "78/an.other.[ke.y]<1>/no", (std::array<std::string, 3>{"/", "<", ">"}), NULL_VALUE);
    
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenLargeJsonFile1, VALID__LARGE, "", JSON_DEFAULT_SEPARATORS, ARRAY);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenLargeJsonFile2, VALID__LARGE, "[0].balance", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenLargeJsonFile3, VALID__LARGE, "[1].about", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenLargeJsonFile4, VALID__LARGE, "[1].about", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenLargeJsonFile5, VALID__LARGE, "[13]", JSON_DEFAULT_SEPARATORS, OBJECT);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenLargeJsonFile6, VALID__LARGE, "[13].registered", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenLargeJsonFile7, VALID__LARGE, "[14]", JSON_DEFAULT_SEPARATORS, OBJECT);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenLargeJsonFile8, VALID__LARGE, "[14].latitude", JSON_DEFAULT_SEPARATORS, FLOAT_NUM);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenLargeJsonFile9, VALID__LARGE, "[14].friends", JSON_DEFAULT_SEPARATORS, ARRAY);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenLargeJsonFile10, VALID__LARGE, "[14].friends[1]", JSON_DEFAULT_SEPARATORS, OBJECT);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenLargeJsonFile11, VALID__LARGE, "[14].friends[1].id", JSON_DEFAULT_SEPARATORS, INT_NUM);
    
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenNestedJsonFile1, VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested", JSON_DEFAULT_SEPARATORS, BOOL);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenNestedJsonFile2, VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenNestedJsonFile3, VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2", JSON_DEFAULT_SEPARATORS, INT_NUM);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenNestedJsonFile4, VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3", JSON_DEFAULT_SEPARATORS, BOOL);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenNestedJsonFile5, VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags[5]", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenNestedJsonFile6, VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2].id", JSON_DEFAULT_SEPARATORS, INT_NUM);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenNestedJsonFile7, VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenNestedJsonFile8, VALID__NESTED, "address.country", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenNestedJsonFile9, VALID__NESTED, "phone", JSON_DEFAULT_SEPARATORS, STRING);
        _CREATE_INJSON_GET_TYPE_METHOD_TEST(WhenGivenNestedJsonFile10, VALID__NESTED, "grades.english", JSON_DEFAULT_SEPARATORS, INT_NUM);
    
    #undef _CREATE_INJSON_GET_TYPE_METHOD_TEST
        } // namespace Injson
    } // namespace jsonio
} // namespace test

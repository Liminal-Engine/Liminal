/**
 * @file InJson.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-04
 * 
 * @copyright Copyright (c) 2023
 * 
*/


// //**********
// // Incudes required for InJson internal calls TODO : remove this ?
#include "jsonio/include/_private/_lexing/_types.hpp"
#include "jsonio/include/_private/_lexing/_lexing.hpp"
// //**********

#include "jsonio/InJson.hpp"

#include "constants.test.hpp"
#include "jsonio.test.hpp"

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

// TODO : test if send a non-json file
// TODO : test all JsonIO return status
class JsonIOInJsonParseMethod : public ::testing::TestWithParam<std::pair<fs::Path, jsonio::Status>> {

    protected:
        jsonio::InJson _instance;
        jsonio::Status returnedValue;

        JsonIOInJsonParseMethod(void) :
        _instance{jsonio::InJson()},
        returnedValue{__proceedParsing()}
        {}

    private:
        jsonio::Status __proceedParsing(void) {
            std::string tmp = sysop::getBinPath().toStr();
            
            return this->_instance.parse(GetParam().first);
        }

        void SetUp(void) override {}
        void TearDown(void) override {}


};

TEST_P(JsonIOInJsonParseMethod, ReturnsGivenStatus) {
    EXPECT_EQ(returnedValue, GetParam().second);
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenInvalidJsonContent,
    JsonIOInJsonParseMethod,
    testing::Values(
        std::make_pair(jsonio_test::paths::INVALID__ARRAY__WRONG_FORMAT, jsonio::Status::E_PARSING),
        
        std::make_pair(jsonio_test::paths::INVALID__BOOL__INCOMPLETE, jsonio::Status::E_PARSING),

        std::make_pair(jsonio_test::paths::INVALID__BRACE__MISSING_CLOSING, jsonio::Status::E_PARSING),
        std::make_pair(jsonio_test::paths::INVALID__BRACE__MISSING_OPENING, jsonio::Status::E_PARSING),

        std::make_pair(jsonio_test::paths::INVALID__BRACKET__MISING_CLOSING, jsonio::Status::E_PARSING),
        std::make_pair(jsonio_test::paths::INVALID__BRACKET__MISING_OPENING, jsonio::Status::E_PARSING),
        std::make_pair(jsonio_test::paths::INVALID__BRACKET__MISING_OPENING_AT_ROOT, jsonio::Status::E_PARSING),

        std::make_pair(jsonio_test::paths::INVALID_COLON__MISSING, jsonio::Status::E_PARSING),
        std::make_pair(jsonio_test::paths::INVALID_COLON__TOO_MANY, jsonio::Status::E_PARSING),
        std::make_pair(jsonio_test::paths::INVALID_COLON__TOO_MANY_IN_SIMPLE_KEY_VALUE_PAIR, jsonio::Status::E_PARSING),
        std::make_pair(jsonio_test::paths::INVALID_COLON__WRONG_CHAR, jsonio::Status::E_PARSING),

        std::make_pair(jsonio_test::paths::INVALID__COMMA__MISPLACED, jsonio::Status::E_PARSING),
        std::make_pair(jsonio_test::paths::INVALID__COMMA__MISSING, jsonio::Status::E_PARSING),
        std::make_pair(jsonio_test::paths::INVALID__COMMA__MISSING_IN_ARRAY, jsonio::Status::E_PARSING),
        std::make_pair(jsonio_test::paths::INVALID__COMMA__MISSING_IN_NESTED_ARRAY, jsonio::Status::E_PARSING),
        std::make_pair(jsonio_test::paths::INVALID__COMMA__MISSING_IN_NUM_ARRAY, jsonio::Status::E_PARSING),
        std::make_pair(jsonio_test::paths::INVALID__COMMA__MULTIPLE_MISSING_IN_ARRAY, jsonio::Status::E_PARSING),
        std::make_pair(jsonio_test::paths::INVALID__COMMA__TOO_MUCH, jsonio::Status::E_PARSING)

    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenValidJsonContent,
    JsonIOInJsonParseMethod,
    testing::Values(
        std::make_pair(jsonio_test::paths::VALID__BASIC, jsonio::Status::OK),
        std::make_pair(jsonio_test::paths::VALID__EDGE_CASES, jsonio::Status::OK),
        std::make_pair(jsonio_test::paths::VALID__NESTED, jsonio::Status::OK),
        std::make_pair(jsonio_test::paths::VALID__LARGE, jsonio::Status::OK)
    )
);

// # FIXME : transform this to status::FILE_NOT_FOUND
// INSTANTIATE_TEST_SUITE_P(
//     WhenFilePathDoesNotExist,
//     JsonIOInJsonParseMethod,
//     testing::Values(
//         std::make_pair(jsonio_test::paths::INEXISTANT_PATH, jsonio::Status::NOK),
//         std::make_pair(jsonio_test::paths::VALID__BASIC + jsonio_test::paths::INEXISTANT_PATH, jsonio::Status::NOK),
//         std::make_pair(jsonio_test::paths::MISSING_LETTER_IN_FILE_EXT, jsonio::Status::NOK)
//     )
// );

class JsonIOInJsonGetMethod : public ::testing::Test {
    protected:
        jsonio::InJson _instance;

        JsonIOInJsonGetMethod(void) :
        _instance{jsonio::InJson()}
        {
            
        }
        
        template <typename T>
        requires jsonio::is_in_variant_v<T, jsonio::types::Any_t>
        void has_value(const bool &expected, const std::string &jsonPath = "", const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS) {
            EXPECT_EQ(this->_instance.get<T>(jsonPath, separators).has_value(), expected);
        }

        template <typename T>
        requires jsonio::is_in_variant_v<T, jsonio::types::Any_t>
        void value_eq(const T &expected, const std::string &jsonPath = "", const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS) {
            if constexpr (std::is_same_v<T, jsonio::types::FloatNum_t>)
                EXPECT_NEAR(this->_instance.get<jsonio::types::FloatNum_t>(jsonPath, separators).value(), expected, constants::EXPECT_NEAR_ABSOLUTE_ERROR);
            else 
                EXPECT_EQ(this->_instance.get<T>(jsonPath, separators).value(), expected);
        }

        void type_eq(const jsonio::types::ValueTypes &expected, const std::string &jsonPath = "", const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS) {
            EXPECT_EQ(this->_instance.getType(jsonPath, separators), expected);
        }
};

// TODO : use macro instead

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile1) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::Object_t>(true);
    type_eq(jsonio::types::ValueTypes::OBJECT);
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile2) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::String_t>(true, "name");
    value_eq<jsonio::types::String_t>("John Doe", "name");
    type_eq(jsonio::types::ValueTypes::STRING, "name");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile3) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::IntNum_t>(true, "age");
    value_eq<jsonio::types::IntNum_t>(30, "age");
    type_eq(jsonio::types::ValueTypes::INT_NUM, "age");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile4) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::Bool_t>(true, "isEmployed");
    value_eq<jsonio::types::Bool_t>(true, "isEmployed");
    type_eq(jsonio::types::ValueTypes::BOOL, "isEmployed");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile5) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::Object_t>(true, "address");
    type_eq(jsonio::types::ValueTypes::OBJECT, "address");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile6) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::Object_t>(true, "address.story");
    type_eq(jsonio::types::ValueTypes::OBJECT, "address.story");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile7) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);
  
    has_value<jsonio::types::IntNum_t>(true, "address.story.left");
    value_eq<jsonio::types::IntNum_t>(15, "address.story.left");
    type_eq(jsonio::types::ValueTypes::INT_NUM, "address.story.left");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile8) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::FloatNum_t>(true, "address.story.right");
    value_eq<jsonio::types::FloatNum_t>(678.5, "address.story.right");
    type_eq(jsonio::types::ValueTypes::FLOAT_NUM, "address.story.right");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile9) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::String_t>(true, "address.street");
    value_eq<jsonio::types::String_t>("123 Main St", "address.street");
    type_eq(jsonio::types::ValueTypes::STRING, "address.street");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile10) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::String_t>(true, "address.city");
    value_eq<jsonio::types::String_t>("Anytown", "address.city");
    type_eq(jsonio::types::ValueTypes::STRING, "address.city");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile11) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::String_t>(true, "address.state");
    value_eq<jsonio::types::String_t>("Anystate", "address.state");
    type_eq(jsonio::types::ValueTypes::STRING, "address.state");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile12) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::IntNum_t>(true, "address.postalCode");
    value_eq<jsonio::types::IntNum_t>(12345, "address.postalCode");
    type_eq(jsonio::types::ValueTypes::INT_NUM, "address.postalCode");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile13) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::FloatNum_t>(true, "address.anotherData");
    value_eq<jsonio::types::FloatNum_t>(42.84, "address.anotherData");
    type_eq(jsonio::types::ValueTypes::FLOAT_NUM, "address.anotherData");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile14) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::Array_t>(true, "hobbies");
    type_eq(jsonio::types::ValueTypes::ARRAY, "hobbies");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile15) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::String_t>(true, "hobbies[0]");
    value_eq<jsonio::types::String_t>("reading", "hobbies[0]");
    type_eq(jsonio::types::ValueTypes::STRING, "hobbies[0]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile16) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::String_t>(true, "hobbies[1]");
    value_eq<jsonio::types::String_t>("gaming", "hobbies[1]");
    type_eq(jsonio::types::ValueTypes::STRING, "hobbies[1]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile17) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::String_t>(true, "hobbies[2]");
    value_eq<jsonio::types::String_t>("hiking", "hobbies[2]");
    type_eq(jsonio::types::ValueTypes::STRING, "hobbies[2]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile18) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::Object_t>(true, "hobbies[3]");
    type_eq(jsonio::types::ValueTypes::OBJECT, "hobbies[3]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile19) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::String_t>(true, "hobbies[3].nestedHobby");
    value_eq<jsonio::types::String_t>("no", "hobbies[3].nestedHobby");
    type_eq(jsonio::types::ValueTypes::STRING, "hobbies[3].nestedHobby");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile20) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::Object_t>(true, "hobbies[4]");
    type_eq(jsonio::types::ValueTypes::OBJECT, "hobbies[4]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile21) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::Array_t>(true, "hobbies[4].secondNestedHobbies");
    type_eq(jsonio::types::ValueTypes::ARRAY, "hobbies[4].secondNestedHobbies");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile22) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::String_t>(true, "hobbies[4].secondNestedHobbies[0]");
    value_eq<jsonio::types::String_t>("un", "hobbies[4].secondNestedHobbies[0]");
    type_eq(jsonio::types::ValueTypes::STRING, "hobbies[4].secondNestedHobbies[0]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile23) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::String_t>(true, "hobbies[4].secondNestedHobbies[1]");
    value_eq<jsonio::types::String_t>("dos", "hobbies[4].secondNestedHobbies[1]");
    type_eq(jsonio::types::ValueTypes::STRING, "hobbies[4].secondNestedHobbies[1]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile24) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::IntNum_t>(true, "hobbies[4].secondNestedHobbies[2]");
    value_eq<jsonio::types::IntNum_t>(3, "hobbies[4].secondNestedHobbies[2]");
    type_eq(jsonio::types::ValueTypes::INT_NUM, "hobbies[4].secondNestedHobbies[2]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile25) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::Null_t>(true, "hobbies[4].secondNestedHobbies[3]");
    value_eq<jsonio::types::Null_t>(nullptr, "hobbies[4].secondNestedHobbies[3]");
    type_eq(jsonio::types::ValueTypes::NULL_VALUE, "hobbies[4].secondNestedHobbies[3]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile26) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::Null_t>(true, "hobbies[4].nothingImportantHere");
    value_eq<jsonio::types::Null_t>(nullptr, "hobbies[4].nothingImportantHere");
    type_eq(jsonio::types::ValueTypes::NULL_VALUE, "hobbies[4].nothingImportantHere");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenBasicJsonFile27) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);

    has_value<jsonio::types::String_t>(true, "happy");
    value_eq<jsonio::types::String_t>("yes", "happy");
    type_eq(jsonio::types::ValueTypes::STRING, "happy");
};



TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile1) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::Object_t>(true);
    type_eq(jsonio::types::ValueTypes::OBJECT);
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile2) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    //TODO : create and test a liminal_string interpret escaped chars func
    has_value<jsonio::types::String_t>(true, "isThisAnObjec\\tt?::\\n:::,  ");
    value_eq<jsonio::types::String_t>("{\\\"I\\\": \\\"don't\\\",\\n\\t\\\"think\\\": false }", "isThisAnObjec\\tt?::\\n:::,  ");
    type_eq(jsonio::types::ValueTypes::STRING, "isThisAnObjec\\tt?::\\n:::,  ");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile3) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::Object_t>(true, "-12345");
    type_eq(jsonio::types::ValueTypes::OBJECT, "-12345");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile4) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::Array_t>(true, "78.40014", std::vector<std::string>{"/", "[", "]"});
    type_eq(jsonio::types::ValueTypes::ARRAY, "78.40014", std::vector<std::string>{"/", "[", "]"});
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile5) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::Object_t>(true, "78");
    type_eq(jsonio::types::ValueTypes::OBJECT, "78");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile6) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::Array_t>(true, "78.40014");
    type_eq(jsonio::types::ValueTypes::ARRAY, "78.40014");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile7) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::Object_t>(true, "78.40014[0]");
    type_eq(jsonio::types::ValueTypes::OBJECT, "78.40014[0]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile8) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::Array_t>(true, "78.40014[0].yes");
    type_eq(jsonio::types::ValueTypes::ARRAY, "78.40014[0].yes");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile9) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::String_t>(true, "78.40014[0].yes[0]");
    value_eq<jsonio::types::String_t>("no", "78.40014[0].yes[0]");
    type_eq(jsonio::types::ValueTypes::STRING, "78.40014[0].yes[0]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile10) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::String_t>(true, "78.40014[0].yes[1]");
    value_eq<jsonio::types::String_t>("maybe", "78.40014[0].yes[1]");
    type_eq(jsonio::types::ValueTypes::STRING, "78.40014[0].yes[1]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile11) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::String_t>(true, "78.40014[0].yes[2]");
    value_eq<jsonio::types::String_t>("this[is]a.[key]", "78.40014[0].yes[2]");
    type_eq(jsonio::types::ValueTypes::STRING, "78.40014[0].yes[2]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile12) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::Array_t>(true, "78/an.other.[ke.y]", std::vector<std::string>{"/", "<", ">"});
    type_eq(jsonio::types::ValueTypes::ARRAY, "78/an.other.[ke.y]", std::vector<std::string>{"/", "<", ">"});
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile13) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::String_t>(true, "78/an.other.[ke.y]<0>/yes", std::vector<std::string>{"/", "<", ">"});
    value_eq<jsonio::types::String_t>("no", "78/an.other.[ke.y]<0>/yes", std::vector<std::string>{"/", "<", ">"});
    type_eq(jsonio::types::ValueTypes::STRING, "78/an.other.[ke.y]<0>/yes", std::vector<std::string>{"/", "<", ">"});
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenEdgeCasesJsonFile14) {
    _instance.parse(jsonio_test::paths::VALID__EDGE_CASES);

    has_value<jsonio::types::Null_t>(true, "78/an.other.[ke.y]<1>/no", std::vector<std::string>{"/", "<", ">"});
    value_eq<jsonio::types::Null_t>(nullptr, "78/an.other.[ke.y]<1>/no", std::vector<std::string>{"/", "<", ">"});
    type_eq(jsonio::types::ValueTypes::NULL_VALUE, "78/an.other.[ke.y]<1>/no", std::vector<std::string>{"/", "<", ">"});
}



/**
 * Here, we do one test for the whole file to test if getting successive values without re parsing the file has a side effetct,
 * saving test execution time at the same time since in the the large json file
 */ 
TEST_F(JsonIOInJsonGetMethod, WhenGivenLargeJsonFile) {
    _instance.parse(jsonio_test::paths::VALID__LARGE);

    has_value<jsonio::types::Array_t>(true);
    type_eq(jsonio::types::ValueTypes::ARRAY);

    has_value<jsonio::types::String_t>(true, "[0].balance");
    value_eq<jsonio::types::String_t>("$2,399.08", "[0].balance");
    type_eq(jsonio::types::ValueTypes::STRING, "[0].balance");

    has_value<jsonio::types::String_t>(true, "[1].about");
    value_eq<jsonio::types::String_t>("Minim cupidatat dolor mollit proident enim qui dolore dolor id nisi. Id sunt excepteur nisi officia elit qui aliqua excepteur aliquip fugiat et do Lorem. Qui cupidatat commodo consectetur do laborum elit aute ipsum aliquip. Pariatur dolore commodo enim aute excepteur.\\r\\n", "[1].about");
    type_eq(jsonio::types::ValueTypes::STRING, "[1].about");

    has_value<jsonio::types::Object_t>(true, "[13]");
    type_eq(jsonio::types::ValueTypes::OBJECT, "[13]");

    has_value<jsonio::types::String_t>(true, "[13].registered");
    value_eq<jsonio::types::String_t>("2022-03-08T09:55:37 -01:00", "[13].registered");
    type_eq(jsonio::types::ValueTypes::STRING, "[13].registered");

    has_value<jsonio::types::Object_t>(true, "[14]");
    type_eq(jsonio::types::ValueTypes::OBJECT, "[14]");

    has_value<jsonio::types::FloatNum_t>(true, "[14].latitude");
    value_eq<jsonio::types::FloatNum_t>(-76.371709, "[14].latitude");
    type_eq(jsonio::types::ValueTypes::FLOAT_NUM, "[14].latitude");

    has_value<jsonio::types::Array_t>(true, "[14].friends");
    type_eq(jsonio::types::ValueTypes::ARRAY, "[14].friends");
    
    has_value<jsonio::types::Object_t>(true, "[14].friends[1]");
    type_eq(jsonio::types::ValueTypes::OBJECT, "[14].friends[1]");

    has_value<jsonio::types::IntNum_t>(true, "[14].friends[1].id");
    value_eq<jsonio::types::IntNum_t>(1, "[14].friends[1].id");
    type_eq(jsonio::types::ValueTypes::INT_NUM, "[14].friends[1].id");
};



TEST_F(JsonIOInJsonGetMethod, WhenGivenNestedJsonFile1) {
    _instance.parse(jsonio_test::paths::VALID__NESTED);

    has_value<jsonio::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested");
    value_eq<jsonio::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested");
    type_eq(jsonio::types::ValueTypes::BOOL, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenNestedJsonFile2) {
    _instance.parse(jsonio_test::paths::VALID__NESTED);

    has_value<jsonio::types::String_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1");
    value_eq<jsonio::types::String_t>("Random Value 1", "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1");
    type_eq(jsonio::types::ValueTypes::STRING, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenNestedJsonFile3) {
    _instance.parse(jsonio_test::paths::VALID__NESTED);

    has_value<jsonio::types::IntNum_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2");
    value_eq<jsonio::types::IntNum_t>(42, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2");
    type_eq(jsonio::types::ValueTypes::INT_NUM, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenNestedJsonFile4) {
    _instance.parse(jsonio_test::paths::VALID__NESTED);

    has_value<jsonio::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3");
    value_eq<jsonio::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3");
    type_eq(jsonio::types::ValueTypes::BOOL, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenNestedJsonFile5) {
    _instance.parse(jsonio_test::paths::VALID__NESTED);

    has_value<jsonio::types::String_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags[5]");
    value_eq<jsonio::types::String_t>("proident", "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags[5]");
    type_eq(jsonio::types::ValueTypes::STRING, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags[5]");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenNestedJsonFile6) {
    _instance.parse(jsonio_test::paths::VALID__NESTED);

    has_value<jsonio::types::IntNum_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2].id");
    value_eq<jsonio::types::IntNum_t>(2, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2].id");
    type_eq(jsonio::types::ValueTypes::INT_NUM, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2].id");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenNestedJsonFile7) {
    _instance.parse(jsonio_test::paths::VALID__NESTED);

    has_value<jsonio::types::String_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting");
    value_eq<jsonio::types::String_t>("Hello, Madelyn Gilliam! You have 8 unread messages.", "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting");
    type_eq(jsonio::types::ValueTypes::STRING, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenNestedJsonFile8) {
    _instance.parse(jsonio_test::paths::VALID__NESTED);

    has_value<jsonio::types::String_t>(true, "address.country");
    value_eq<jsonio::types::String_t>("USA", "address.country");
    type_eq(jsonio::types::ValueTypes::STRING, "address.country");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenNestedJsonFile9) {
    _instance.parse(jsonio_test::paths::VALID__NESTED);

    has_value<jsonio::types::String_t>(true, "phone");
    value_eq<jsonio::types::String_t>("+1 123-456-7890", "phone");
    type_eq(jsonio::types::ValueTypes::STRING, "phone");
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenNestedJsonFile10) {
    _instance.parse(jsonio_test::paths::VALID__NESTED);

    has_value<jsonio::types::IntNum_t>(true, "grades.english");
    value_eq<jsonio::types::IntNum_t>(92, "grades.english");
    type_eq(jsonio::types::ValueTypes::INT_NUM, "grades.english");
};



TEST_F(JsonIOInJsonGetMethod, WhenGivenWrongRequestedTypeWithNestedJsonFile) {
    _instance.parse(jsonio_test::paths::VALID__NESTED);
    EXPECT_FALSE(_instance.get<jsonio::types::FloatNum_t>("nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2").has_value());
    EXPECT_FALSE(_instance.get<jsonio::types::Null_t>("nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting").has_value());
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenWrongRequestedTypeWithLargeJsonFile) {
    _instance.parse(jsonio_test::paths::VALID__LARGE);
    EXPECT_FALSE(_instance.get<jsonio::types::IntNum_t>("[14].latitude").has_value());
};

TEST_F(JsonIOInJsonGetMethod, WhenGivenWrongRequestedTypeWithBasicJsonFile) {
    _instance.parse(jsonio_test::paths::VALID__BASIC);
    EXPECT_FALSE(_instance.get<jsonio::types::FloatNum_t>("name").has_value());
}

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
#include "json_io/include/_private/_lexing/_types.hpp"
#include "json_io/include/_private/_lexing/_lexing.hpp"
// //**********

#include "json_io/InJson.hpp"

#include "constants.test.hpp"
#include "json_io.test.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <variant>
#include <tuple>
#include <type_traits>

// TODO : test if send a non-json file
// TODO : test all JsonIo return status
// TODO : test when missing root end brace and bracket
class JsonIoInJsonParseMethod : public ::testing::TestWithParam<std::pair<fs::Path, json_io::Status>> {

    protected:
        json_io::InJson _instance;
        json_io::Status returnedValue;

        JsonIoInJsonParseMethod(void) :
        _instance{json_io::InJson()},
        returnedValue{__proceedParsing()}
        {}

    private:
        json_io::Status __proceedParsing(void) {
            std::filesystem::current_path("../../tests");
            return this->_instance.parse(GetParam().first);
        }

        void SetUp(void) override {}
        void TearDown(void) override {}


};

TEST_P(JsonIoInJsonParseMethod, ReturnsGivenStatus) {
    EXPECT_EQ(returnedValue, GetParam().second);
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenInvalidJsonContent,
    JsonIoInJsonParseMethod,
    testing::Values(
        std::make_pair(json_io_test::paths::INVALID__ARRAY__WRONG_FORMAT, json_io::Status::E_PARSING),
        
        std::make_pair(json_io_test::paths::INVALID__BOOL__INCOMPLETE, json_io::Status::E_PARSING),

        std::make_pair(json_io_test::paths::INVALID__BRACE__MISSING_CLOSING, json_io::Status::E_PARSING),
        std::make_pair(json_io_test::paths::INVALID__BRACE__MISSING_OPENING, json_io::Status::E_PARSING),

        std::make_pair(json_io_test::paths::INVALID__BRACKET__MISING_CLOSING, json_io::Status::E_PARSING),
        std::make_pair(json_io_test::paths::INVALID__BRACKET__MISING_OPENING, json_io::Status::E_PARSING),
        std::make_pair(json_io_test::paths::INVALID__BRACKET__MISING_OPENING_AT_ROOT, json_io::Status::E_PARSING),

        std::make_pair(json_io_test::paths::INVALID_COLON__MISSING, json_io::Status::E_PARSING),
        std::make_pair(json_io_test::paths::INVALID_COLON__TOO_MANY, json_io::Status::E_PARSING),
        std::make_pair(json_io_test::paths::INVALID_COLON__TOO_MANY_IN_SIMPLE_KEY_VALUE_PAIR, json_io::Status::E_PARSING),
        std::make_pair(json_io_test::paths::INVALID_COLON__WRONG_CHAR, json_io::Status::E_PARSING),

        std::make_pair(json_io_test::paths::INVALID__COMMA__MISPLACED, json_io::Status::E_PARSING),
        std::make_pair(json_io_test::paths::INVALID__COMMA__MISSING, json_io::Status::E_PARSING),
        std::make_pair(json_io_test::paths::INVALID__COMMA__MISSING_IN_ARRAY, json_io::Status::E_PARSING),
        std::make_pair(json_io_test::paths::INVALID__COMMA__MISSING_IN_NESTED_ARRAY, json_io::Status::E_PARSING),
        std::make_pair(json_io_test::paths::INVALID__COMMA__MISSING_IN_NUM_ARRAY, json_io::Status::E_PARSING),
        std::make_pair(json_io_test::paths::INVALID__COMMA__MULTIPLE_MISSING_IN_ARRAY, json_io::Status::E_PARSING),
        std::make_pair(json_io_test::paths::INVALID__COMMA__TOO_MUCH, json_io::Status::E_PARSING)

    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenValidJsonContent,
    JsonIoInJsonParseMethod,
    testing::Values(
        std::make_pair(json_io_test::paths::VALID__BASIC, json_io::Status::OK),
        std::make_pair(json_io_test::paths::VALID__EDGE_CASES, json_io::Status::OK),
        std::make_pair(json_io_test::paths::VALID__NESTED, json_io::Status::OK),
        std::make_pair(json_io_test::paths::VALID__LARGE, json_io::Status::OK)
    )
);

// # FIXME : transform this to status::FILE_NOT_FOUND
// INSTANTIATE_TEST_SUITE_P(
//     WhenFilePathDoesNotExist,
//     JsonIoInJsonParseMethod,
//     testing::Values(
//         std::make_pair(json_io_test::paths::INEXISTANT_PATH, json_io::Status::NOK),
//         std::make_pair(json_io_test::paths::VALID__BASIC + json_io_test::paths::INEXISTANT_PATH, json_io::Status::NOK),
//         std::make_pair(json_io_test::paths::MISSING_LETTER_IN_FILE_EXT, json_io::Status::NOK)
//     )
// );

class JsonIoInJsonGetMethod : public ::testing::Test {
    protected:
        json_io::InJson _instance;

        JsonIoInJsonGetMethod(void) :
        _instance{json_io::InJson()}
        {
            std::filesystem::current_path("../../tests");
        }
        
        template <typename T>
        requires json_io::is_in_variant_v<T, json_io::types::Any_t>
        void has_value(const bool &expected, const std::string &jsonPath = "", const std::vector<std::string> &separators = std::vector<std::string>{".", "[", "]"}) {
            EXPECT_EQ(this->_instance.get<T>(jsonPath, separators).has_value(), expected);
        }

        template <typename T>
        requires json_io::is_in_variant_v<T, json_io::types::Any_t>
        void value_eq(const T &expected, const std::string &jsonPath = "", const std::vector<std::string> &separators = std::vector<std::string>{".", "[", "]"}) {
            if constexpr (std::is_same_v<T, json_io::types::FloatNum_t>)
                EXPECT_NEAR(this->_instance.get<json_io::types::FloatNum_t>(jsonPath, separators).value(), expected, constants::EXPECT_NEAR_ABSOLUTE_ERROR);
            else 
                EXPECT_EQ(this->_instance.get<T>(jsonPath, separators).value(), expected);
        }

        void type_eq(const json_io::types::ValueTypes &expected, const std::string &jsonPath = "", const std::vector<std::string> &separators = std::vector<std::string>{".", "[", "]"}) {
            EXPECT_EQ(this->_instance.getType(jsonPath, separators), expected);
        }
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile1) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::Object_t>(true);
    type_eq(json_io::types::ValueTypes::OBJECT);
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile2) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::String_t>(true, "name");
    value_eq<json_io::types::String_t>("John Doe", "name");
    type_eq(json_io::types::ValueTypes::STRING, "name");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile3) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::IntNum_t>(true, "age");
    value_eq<json_io::types::IntNum_t>(30, "age");
    type_eq(json_io::types::ValueTypes::INT_NUM, "age");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile4) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::Bool_t>(true, "isEmployed");
    value_eq<json_io::types::Bool_t>(true, "isEmployed");
    type_eq(json_io::types::ValueTypes::BOOL, "isEmployed");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile5) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::Object_t>(true, "address");
    type_eq(json_io::types::ValueTypes::OBJECT, "address");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile6) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::Object_t>(true, "address.story");
    type_eq(json_io::types::ValueTypes::OBJECT, "address.story");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile7) {
    _instance.parse(json_io_test::paths::VALID__BASIC);
  
    has_value<json_io::types::IntNum_t>(true, "address.story.left");
    value_eq<json_io::types::IntNum_t>(15, "address.story.left");
    type_eq(json_io::types::ValueTypes::INT_NUM, "address.story.left");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile8) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::FloatNum_t>(true, "address.story.right");
    value_eq<json_io::types::FloatNum_t>(678.5, "address.story.right");
    type_eq(json_io::types::ValueTypes::FLOAT_NUM, "address.story.right");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile9) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::String_t>(true, "address.street");
    value_eq<json_io::types::String_t>("123 Main St", "address.street");
    type_eq(json_io::types::ValueTypes::STRING, "address.street");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile10) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::String_t>(true, "address.city");
    value_eq<json_io::types::String_t>("Anytown", "address.city");
    type_eq(json_io::types::ValueTypes::STRING, "address.city");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile11) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::String_t>(true, "address.state");
    value_eq<json_io::types::String_t>("Anystate", "address.state");
    type_eq(json_io::types::ValueTypes::STRING, "address.state");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile12) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::IntNum_t>(true, "address.postalCode");
    value_eq<json_io::types::IntNum_t>(12345, "address.postalCode");
    type_eq(json_io::types::ValueTypes::INT_NUM, "address.postalCode");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile13) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::FloatNum_t>(true, "address.anotherData");
    value_eq<json_io::types::FloatNum_t>(42.84, "address.anotherData");
    type_eq(json_io::types::ValueTypes::FLOAT_NUM, "address.anotherData");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile14) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::Array_t>(true, "hobbies");
    type_eq(json_io::types::ValueTypes::ARRAY, "hobbies");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile15) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::String_t>(true, "hobbies[0]");
    value_eq<json_io::types::String_t>("reading", "hobbies[0]");
    type_eq(json_io::types::ValueTypes::STRING, "hobbies[0]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile16) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::String_t>(true, "hobbies[1]");
    value_eq<json_io::types::String_t>("gaming", "hobbies[1]");
    type_eq(json_io::types::ValueTypes::STRING, "hobbies[1]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile17) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::String_t>(true, "hobbies[2]");
    value_eq<json_io::types::String_t>("hiking", "hobbies[2]");
    type_eq(json_io::types::ValueTypes::STRING, "hobbies[2]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile18) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::Object_t>(true, "hobbies[3]");
    type_eq(json_io::types::ValueTypes::OBJECT, "hobbies[3]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile19) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::String_t>(true, "hobbies[3].nestedHobby");
    value_eq<json_io::types::String_t>("no", "hobbies[3].nestedHobby");
    type_eq(json_io::types::ValueTypes::STRING, "hobbies[3].nestedHobby");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile20) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::Object_t>(true, "hobbies[4]");
    type_eq(json_io::types::ValueTypes::OBJECT, "hobbies[4]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile21) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::Array_t>(true, "hobbies[4].secondNestedHobbies");
    type_eq(json_io::types::ValueTypes::ARRAY, "hobbies[4].secondNestedHobbies");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile22) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::String_t>(true, "hobbies[4].secondNestedHobbies[0]");
    value_eq<json_io::types::String_t>("un", "hobbies[4].secondNestedHobbies[0]");
    type_eq(json_io::types::ValueTypes::STRING, "hobbies[4].secondNestedHobbies[0]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile23) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::String_t>(true, "hobbies[4].secondNestedHobbies[1]");
    value_eq<json_io::types::String_t>("dos", "hobbies[4].secondNestedHobbies[1]");
    type_eq(json_io::types::ValueTypes::STRING, "hobbies[4].secondNestedHobbies[1]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile24) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::IntNum_t>(true, "hobbies[4].secondNestedHobbies[2]");
    value_eq<json_io::types::IntNum_t>(3, "hobbies[4].secondNestedHobbies[2]");
    type_eq(json_io::types::ValueTypes::INT_NUM, "hobbies[4].secondNestedHobbies[2]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile25) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::Null_t>(true, "hobbies[4].secondNestedHobbies[3]");
    value_eq<json_io::types::Null_t>(nullptr, "hobbies[4].secondNestedHobbies[3]");
    type_eq(json_io::types::ValueTypes::NULL_VALUE, "hobbies[4].secondNestedHobbies[3]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile26) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::Null_t>(true, "hobbies[4].nothingImportantHere");
    value_eq<json_io::types::Null_t>(nullptr, "hobbies[4].nothingImportantHere");
    type_eq(json_io::types::ValueTypes::NULL_VALUE, "hobbies[4].nothingImportantHere");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenBasicJsonFile27) {
    _instance.parse(json_io_test::paths::VALID__BASIC);

    has_value<json_io::types::String_t>(true, "happy");
    value_eq<json_io::types::String_t>("yes", "happy");
    type_eq(json_io::types::ValueTypes::STRING, "happy");
};



TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile1) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::Object_t>(true);
    type_eq(json_io::types::ValueTypes::OBJECT);
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile2) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    //TODO : create and test a liminal_string interpret escaped chars func
    has_value<json_io::types::String_t>(true, "isThisAnObjec\\tt?::\\n:::,  ");
    value_eq<json_io::types::String_t>("{\\\"I\\\": \\\"don't\\\",\\n\\t\\\"think\\\": false }", "isThisAnObjec\\tt?::\\n:::,  ");
    type_eq(json_io::types::ValueTypes::STRING, "isThisAnObjec\\tt?::\\n:::,  ");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile3) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::Object_t>(true, "-12345");
    type_eq(json_io::types::ValueTypes::OBJECT, "-12345");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile4) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::Array_t>(true, "78.40014", std::vector<std::string>{"/", "[", "]"});
    type_eq(json_io::types::ValueTypes::ARRAY, "78.40014", std::vector<std::string>{"/", "[", "]"});
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile5) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::Object_t>(true, "78");
    type_eq(json_io::types::ValueTypes::OBJECT, "78");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile6) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::Array_t>(true, "78.40014");
    type_eq(json_io::types::ValueTypes::ARRAY, "78.40014");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile7) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::Object_t>(true, "78.40014[0]");
    type_eq(json_io::types::ValueTypes::OBJECT, "78.40014[0]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile8) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::Array_t>(true, "78.40014[0].yes");
    type_eq(json_io::types::ValueTypes::ARRAY, "78.40014[0].yes");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile9) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::String_t>(true, "78.40014[0].yes[0]");
    value_eq<json_io::types::String_t>("no", "78.40014[0].yes[0]");
    type_eq(json_io::types::ValueTypes::STRING, "78.40014[0].yes[0]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile10) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::String_t>(true, "78.40014[0].yes[1]");
    value_eq<json_io::types::String_t>("maybe", "78.40014[0].yes[1]");
    type_eq(json_io::types::ValueTypes::STRING, "78.40014[0].yes[1]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile11) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::String_t>(true, "78.40014[0].yes[2]");
    value_eq<json_io::types::String_t>("this[is]a.[key]", "78.40014[0].yes[2]");
    type_eq(json_io::types::ValueTypes::STRING, "78.40014[0].yes[2]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile12) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::Array_t>(true, "78/an.other.[ke.y]", std::vector<std::string>{"/", "<", ">"});
    type_eq(json_io::types::ValueTypes::ARRAY, "78/an.other.[ke.y]", std::vector<std::string>{"/", "<", ">"});
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile13) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::String_t>(true, "78/an.other.[ke.y]<0>/yes", std::vector<std::string>{"/", "<", ">"});
    value_eq<json_io::types::String_t>("no", "78/an.other.[ke.y]<0>/yes", std::vector<std::string>{"/", "<", ">"});
    type_eq(json_io::types::ValueTypes::STRING, "78/an.other.[ke.y]<0>/yes", std::vector<std::string>{"/", "<", ">"});
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenEdgeCasesJsonFile14) {
    _instance.parse(json_io_test::paths::VALID__EDGE_CASES);

    has_value<json_io::types::Null_t>(true, "78/an.other.[ke.y]<1>/no", std::vector<std::string>{"/", "<", ">"});
    value_eq<json_io::types::Null_t>(nullptr, "78/an.other.[ke.y]<1>/no", std::vector<std::string>{"/", "<", ">"});
    type_eq(json_io::types::ValueTypes::NULL_VALUE, "78/an.other.[ke.y]<1>/no", std::vector<std::string>{"/", "<", ">"});
}



/**
 * Here, we do one test for the whole file to test if getting successive values without re parsing the file has a side effetct,
 * saving test execution time at the same time since in the the large json file
 */ 
TEST_F(JsonIoInJsonGetMethod, WhenGivenLargeJsonFile) {
    _instance.parse(json_io_test::paths::VALID__LARGE);

    has_value<json_io::types::Array_t>(true);
    type_eq(json_io::types::ValueTypes::ARRAY);

    has_value<json_io::types::String_t>(true, "[0].balance");
    value_eq<json_io::types::String_t>("$2,399.08", "[0].balance");
    type_eq(json_io::types::ValueTypes::STRING, "[0].balance");

    has_value<json_io::types::String_t>(true, "[1].about");
    value_eq<json_io::types::String_t>("Minim cupidatat dolor mollit proident enim qui dolore dolor id nisi. Id sunt excepteur nisi officia elit qui aliqua excepteur aliquip fugiat et do Lorem. Qui cupidatat commodo consectetur do laborum elit aute ipsum aliquip. Pariatur dolore commodo enim aute excepteur.\\r\\n", "[1].about");
    type_eq(json_io::types::ValueTypes::STRING, "[1].about");

    has_value<json_io::types::Object_t>(true, "[13]");
    type_eq(json_io::types::ValueTypes::OBJECT, "[13]");

    has_value<json_io::types::String_t>(true, "[13].registered");
    value_eq<json_io::types::String_t>("2022-03-08T09:55:37 -01:00", "[13].registered");
    type_eq(json_io::types::ValueTypes::STRING, "[13].registered");

    has_value<json_io::types::Object_t>(true, "[14]");
    type_eq(json_io::types::ValueTypes::OBJECT, "[14]");

    has_value<json_io::types::FloatNum_t>(true, "[14].latitude");
    value_eq<json_io::types::FloatNum_t>(-76.371709, "[14].latitude");
    type_eq(json_io::types::ValueTypes::FLOAT_NUM, "[14].latitude");

    has_value<json_io::types::Array_t>(true, "[14].friends");
    type_eq(json_io::types::ValueTypes::ARRAY, "[14].friends");
    
    has_value<json_io::types::Object_t>(true, "[14].friends[1]");
    type_eq(json_io::types::ValueTypes::OBJECT, "[14].friends[1]");

    has_value<json_io::types::IntNum_t>(true, "[14].friends[1].id");
    value_eq<json_io::types::IntNum_t>(1, "[14].friends[1].id");
    type_eq(json_io::types::ValueTypes::INT_NUM, "[14].friends[1].id");
};



TEST_F(JsonIoInJsonGetMethod, WhenGivenNestedJsonFile1) {
    _instance.parse(json_io_test::paths::VALID__NESTED);

    has_value<json_io::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested");
    value_eq<json_io::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested");
    type_eq(json_io::types::ValueTypes::BOOL, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenNestedJsonFile2) {
    _instance.parse(json_io_test::paths::VALID__NESTED);

    has_value<json_io::types::String_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1");
    value_eq<json_io::types::String_t>("Random Value 1", "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1");
    type_eq(json_io::types::ValueTypes::STRING, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenNestedJsonFile3) {
    _instance.parse(json_io_test::paths::VALID__NESTED);

    has_value<json_io::types::IntNum_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2");
    value_eq<json_io::types::IntNum_t>(42, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2");
    type_eq(json_io::types::ValueTypes::INT_NUM, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenNestedJsonFile4) {
    _instance.parse(json_io_test::paths::VALID__NESTED);

    has_value<json_io::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3");
    value_eq<json_io::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3");
    type_eq(json_io::types::ValueTypes::BOOL, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenNestedJsonFile5) {
    _instance.parse(json_io_test::paths::VALID__NESTED);

    has_value<json_io::types::String_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags[5]");
    value_eq<json_io::types::String_t>("proident", "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags[5]");
    type_eq(json_io::types::ValueTypes::STRING, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags[5]");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenNestedJsonFile6) {
    _instance.parse(json_io_test::paths::VALID__NESTED);

    has_value<json_io::types::IntNum_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2].id");
    value_eq<json_io::types::IntNum_t>(2, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2].id");
    type_eq(json_io::types::ValueTypes::INT_NUM, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2].id");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenNestedJsonFile7) {
    _instance.parse(json_io_test::paths::VALID__NESTED);

    has_value<json_io::types::String_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting");
    value_eq<json_io::types::String_t>("Hello, Madelyn Gilliam! You have 8 unread messages.", "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting");
    type_eq(json_io::types::ValueTypes::STRING, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenNestedJsonFile8) {
    _instance.parse(json_io_test::paths::VALID__NESTED);

    has_value<json_io::types::String_t>(true, "address.country");
    value_eq<json_io::types::String_t>("USA", "address.country");
    type_eq(json_io::types::ValueTypes::STRING, "address.country");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenNestedJsonFile9) {
    _instance.parse(json_io_test::paths::VALID__NESTED);

    has_value<json_io::types::String_t>(true, "phone");
    value_eq<json_io::types::String_t>("+1 123-456-7890", "phone");
    type_eq(json_io::types::ValueTypes::STRING, "phone");
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenNestedJsonFile10) {
    _instance.parse(json_io_test::paths::VALID__NESTED);

    has_value<json_io::types::IntNum_t>(true, "grades.english");
    value_eq<json_io::types::IntNum_t>(92, "grades.english");
    type_eq(json_io::types::ValueTypes::INT_NUM, "grades.english");
};



TEST_F(JsonIoInJsonGetMethod, WhenGivenWrongRequestedTypeWithNestedJsonFile) {
    _instance.parse(json_io_test::paths::VALID__NESTED);
    EXPECT_FALSE(_instance.get<json_io::types::FloatNum_t>("nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2").has_value());
    EXPECT_FALSE(_instance.get<json_io::types::Null_t>("nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting").has_value());
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenWrongRequestedTypeWithLargeJsonFile) {
    _instance.parse(json_io_test::paths::VALID__LARGE);
    EXPECT_FALSE(_instance.get<json_io::types::IntNum_t>("[14].latitude").has_value());
};

TEST_F(JsonIoInJsonGetMethod, WhenGivenWrongRequestedTypeWithBasicJsonFile) {
    _instance.parse(json_io_test::paths::VALID__BASIC);
    EXPECT_FALSE(_instance.get<json_io::types::FloatNum_t>("name").has_value());
}

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
#include "liminal_json_io/include/_private/_lexing/_types.hpp"
#include "liminal_json_io/include/_private/_lexing/_lexing.hpp"
// //**********

#include "liminal_json_io/InJson.hpp"

#include "constants.test.hpp"
#include "liminal_json_io.test.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <variant>
#include <tuple>
#include <type_traits>

class LiminalJsonIOInJsonParseMethod : public ::testing::TestWithParam<std::pair<std::string, liminal_json_io::Status>> {

    protected:
        liminal_json_io::InJson _instance;
        liminal_json_io::Status returnedValue;

        LiminalJsonIOInJsonParseMethod(void) :
        _instance{liminal_json_io::InJson()},
        returnedValue{__proceedParsing()}
        {}

    private:
        liminal_json_io::Status __proceedParsing(void) {
            std::filesystem::current_path("../../tests");
            return this->_instance.parse(GetParam().first);
        }

        void SetUp(void) override {}
        void TearDown(void) override {}


};

TEST_P(LiminalJsonIOInJsonParseMethod, ReturnsGivenStatus) {
    EXPECT_EQ(returnedValue, GetParam().second);
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenInvalidJsonContent,
    LiminalJsonIOInJsonParseMethod,
    testing::Values(
        std::make_pair(liminal_json_io_test::paths::INVALID__ARRAY__WRONG_FORMAT, liminal_json_io::Status::PARSING_ERR),
        
        std::make_pair(liminal_json_io_test::paths::INVALID__BOOL__INCOMPLETE, liminal_json_io::Status::PARSING_ERR),

        std::make_pair(liminal_json_io_test::paths::INVALID__BRACE__MISSING_CLOSING, liminal_json_io::Status::PARSING_ERR),
        std::make_pair(liminal_json_io_test::paths::INVALID__BRACE__MISSING_OPENING, liminal_json_io::Status::PARSING_ERR),

        std::make_pair(liminal_json_io_test::paths::INVALID__BRACKET__MISING_CLOSING, liminal_json_io::Status::PARSING_ERR),
        std::make_pair(liminal_json_io_test::paths::INVALID__BRACKET__MISING_OPENING, liminal_json_io::Status::PARSING_ERR),
        std::make_pair(liminal_json_io_test::paths::INVALID__BRACKET__MISING_OPENING_AT_ROOT, liminal_json_io::Status::PARSING_ERR),

        std::make_pair(liminal_json_io_test::paths::INVALID_COLON__MISSING, liminal_json_io::Status::PARSING_ERR),
        std::make_pair(liminal_json_io_test::paths::INVALID_COLON__TOO_MANY, liminal_json_io::Status::PARSING_ERR),
        std::make_pair(liminal_json_io_test::paths::INVALID_COLON__TOO_MANY_IN_SIMPLE_KEY_VALUE_PAIR, liminal_json_io::Status::PARSING_ERR),
        std::make_pair(liminal_json_io_test::paths::INVALID_COLON__WRONG_CHAR, liminal_json_io::Status::PARSING_ERR),

        std::make_pair(liminal_json_io_test::paths::INVALID__COMMA__MISPLACED, liminal_json_io::Status::PARSING_ERR),
        std::make_pair(liminal_json_io_test::paths::INVALID__COMMA__MISSING, liminal_json_io::Status::PARSING_ERR),
        std::make_pair(liminal_json_io_test::paths::INVALID__COMMA__MISSING_IN_ARRAY, liminal_json_io::Status::PARSING_ERR),
        std::make_pair(liminal_json_io_test::paths::INVALID__COMMA__MISSING_IN_NESTED_ARRAY, liminal_json_io::Status::PARSING_ERR),
        std::make_pair(liminal_json_io_test::paths::INVALID__COMMA__MISSING_IN_NUM_ARRAY, liminal_json_io::Status::PARSING_ERR),
        std::make_pair(liminal_json_io_test::paths::INVALID__COMMA__MULTIPLE_MISSING_IN_ARRAY, liminal_json_io::Status::PARSING_ERR)
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenValidJsonContent,
    LiminalJsonIOInJsonParseMethod,
    testing::Values(
        std::make_pair(liminal_json_io_test::paths::VALID__BASIC, liminal_json_io::Status::OK),
        std::make_pair(liminal_json_io_test::paths::VALID__NESTED, liminal_json_io::Status::OK),
        std::make_pair(liminal_json_io_test::paths::VALID__LARGE, liminal_json_io::Status::OK)
    )
);

// # FIXME : transform this to status::FILE_NOT_FOUND
// INSTANTIATE_TEST_SUITE_P(
//     WhenFilePathDoesNotExist,
//     LiminalJsonIOInJsonParseMethod,
//     testing::Values(
//         std::make_pair(liminal_json_io_test::paths::INEXISTANT_PATH, liminal_json_io::Status::NOK),
//         std::make_pair(liminal_json_io_test::paths::VALID__BASIC + liminal_json_io_test::paths::INEXISTANT_PATH, liminal_json_io::Status::NOK),
//         std::make_pair(liminal_json_io_test::paths::MISSING_LETTER_IN_FILE_EXT, liminal_json_io::Status::NOK)
//     )
// );

class LiminalJsonIOInJsonGetMethod : public ::testing::Test {
    protected:
        liminal_json_io::InJson _instance;

        LiminalJsonIOInJsonGetMethod(void) :
        _instance{liminal_json_io::InJson()}
        {
            std::filesystem::current_path("../../tests");
        }
        
        template <typename T>
        requires liminal_json_io::is_in_variant_v<T, liminal_json_io::types::Any_t>
        void has_value(const bool &expected, const std::string &jsonPath = "") {
            EXPECT_EQ(this->_instance.get<T>(jsonPath).has_value(), expected);
        }

        template <typename T>
        requires liminal_json_io::is_in_variant_v<T, liminal_json_io::types::Any_t>
        void value_eq(const T &expected, const std::string &jsonPath = "") {
            if constexpr (std::is_same_v<T, liminal_json_io::types::FloatNum_t>)
                EXPECT_NEAR(this->_instance.get<liminal_json_io::types::FloatNum_t>(jsonPath).value(), expected, constants::EXPECT_NEAR_ABSOLUTE_ERROR);
            else 
                EXPECT_EQ(this->_instance.get<T>(jsonPath).value(), expected);
        }

        void type_eq(const liminal_json_io::types::ValueTypes &expected, const std::string &jsonPath = "") {
            EXPECT_EQ(this->_instance.getType(jsonPath), expected);
        }
};

TEST_F(LiminalJsonIOInJsonGetMethod, WhenGivenBasicJsonFile) {
    _instance.parse(liminal_json_io_test::paths::VALID__BASIC);

    has_value<liminal_json_io::types::Object_t>(true);
    type_eq(liminal_json_io::types::ValueTypes::OBJECT);

    has_value<liminal_json_io::types::String_t>(true, "name");
    value_eq<liminal_json_io::types::String_t>("John Doe", "name");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "name");

    has_value<liminal_json_io::types::IntNum_t>(true, "age");
    value_eq<liminal_json_io::types::IntNum_t>(30, "age");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "age");

    has_value<liminal_json_io::types::Bool_t>(true, "isEmployed");
    value_eq<liminal_json_io::types::Bool_t>(true, "isEmployed");
    type_eq(liminal_json_io::types::ValueTypes::BOOL, "isEmployed");

    has_value<liminal_json_io::types::Object_t>(true, "address");
    type_eq(liminal_json_io::types::ValueTypes::OBJECT, "address");

    has_value<liminal_json_io::types::Object_t>(true, "address.story");
    type_eq(liminal_json_io::types::ValueTypes::OBJECT, "address.story");
    
    has_value<liminal_json_io::types::IntNum_t>(true, "address.story.left");
    value_eq<liminal_json_io::types::IntNum_t>(15, "address.story.left");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "address.story.left");

    has_value<liminal_json_io::types::FloatNum_t>(true, "address.story.right");
    value_eq<liminal_json_io::types::FloatNum_t>(678.5, "address.story.right");
    type_eq(liminal_json_io::types::ValueTypes::FLOAT_NUM, "address.story.right");

    has_value<liminal_json_io::types::String_t>(true, "address.street");
    value_eq<liminal_json_io::types::String_t>("123 Main St", "address.street");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "address.street");

    has_value<liminal_json_io::types::String_t>(true, "address.city");
    value_eq<liminal_json_io::types::String_t>("Anytown", "address.city");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "address.city");

    has_value<liminal_json_io::types::String_t>(true, "address.state");
    value_eq<liminal_json_io::types::String_t>("Anystate", "address.state");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "address.state");

    has_value<liminal_json_io::types::IntNum_t>(true, "address.postalCode");
    value_eq<liminal_json_io::types::IntNum_t>(12345, "address.postalCode");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "address.postalCode");

    has_value<liminal_json_io::types::FloatNum_t>(true, "address.anotherData");
    value_eq<liminal_json_io::types::FloatNum_t>(42.84, "address.anotherData");
    type_eq(liminal_json_io::types::ValueTypes::FLOAT_NUM, "address.anotherData");

    has_value<liminal_json_io::types::Array_t>(true, "hobbies");
    type_eq(liminal_json_io::types::ValueTypes::ARRAY, "hobbies");

    has_value<liminal_json_io::types::String_t>(true, "hobbies[0]");
    value_eq<liminal_json_io::types::String_t>("reading", "hobbies[0]");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "hobbies[0]");

    has_value<liminal_json_io::types::String_t>(true, "hobbies[1]");
    value_eq<liminal_json_io::types::String_t>("gaming", "hobbies[1]");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "hobbies[1]");

    has_value<liminal_json_io::types::String_t>(true, "hobbies[2]");
    value_eq<liminal_json_io::types::String_t>("hiking", "hobbies[2]");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "hobbies[2]");

    has_value<liminal_json_io::types::Object_t>(true, "hobbies[3]");
    type_eq(liminal_json_io::types::ValueTypes::OBJECT, "hobbies[3]");

    has_value<liminal_json_io::types::String_t>(true, "hobbies[3].nestedHobby");
    value_eq<liminal_json_io::types::String_t>("no", "hobbies[3].nestedHobby");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "hobbies[3].nestedHobby");

    has_value<liminal_json_io::types::Object_t>(true, "hobbies[4]");
    type_eq(liminal_json_io::types::ValueTypes::OBJECT, "hobbies[4]");

    has_value<liminal_json_io::types::Array_t>(true, "hobbies[4].secondNestedHobbies");
    type_eq(liminal_json_io::types::ValueTypes::ARRAY, "hobbies[4].secondNestedHobbies");

    has_value<liminal_json_io::types::String_t>(true, "hobbies[4].secondNestedHobbies[0]");
    value_eq<liminal_json_io::types::String_t>("un", "hobbies[4].secondNestedHobbies[0]");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "hobbies[4].secondNestedHobbies[0]");

    has_value<liminal_json_io::types::String_t>(true, "hobbies[4].secondNestedHobbies[1]");
    value_eq<liminal_json_io::types::String_t>("dos", "hobbies[4].secondNestedHobbies[1]");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "hobbies[4].secondNestedHobbies[1]");

    has_value<liminal_json_io::types::IntNum_t>(true, "hobbies[4].secondNestedHobbies[2]");
    value_eq<liminal_json_io::types::IntNum_t>(3, "hobbies[4].secondNestedHobbies[2]");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "hobbies[4].secondNestedHobbies[2]");

    has_value<liminal_json_io::types::Null_t>(true, "hobbies[4].secondNestedHobbies[3]");
    value_eq<liminal_json_io::types::Null_t>(nullptr, "hobbies[4].secondNestedHobbies[3]");
    type_eq(liminal_json_io::types::ValueTypes::NULL_VALUE, "hobbies[4].secondNestedHobbies[3]");

    has_value<liminal_json_io::types::Null_t>(true, "hobbies[4].nothingImportantHere");
    value_eq<liminal_json_io::types::Null_t>(nullptr, "hobbies[4].nothingImportantHere");
    type_eq(liminal_json_io::types::ValueTypes::NULL_VALUE, "hobbies[4].nothingImportantHere");

    has_value<liminal_json_io::types::String_t>(true, "happy");
    value_eq<liminal_json_io::types::String_t>("yes", "happy");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "happy");
}

TEST_F(LiminalJsonIOInJsonGetMethod, WhenGivenLargeJsonFile) {
    _instance.parse(liminal_json_io_test::paths::VALID__LARGE);

    has_value<liminal_json_io::types::Array_t>(true);
    type_eq(liminal_json_io::types::ValueTypes::ARRAY);

    has_value<liminal_json_io::types::String_t>(true, "[0].balance");
    value_eq<liminal_json_io::types::String_t>("$2,399.08", "[0].balance");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "[0].balance");

    has_value<liminal_json_io::types::String_t>(true, "[1].about");
    value_eq<liminal_json_io::types::String_t>("Minim cupidatat dolor mollit proident enim qui dolore dolor id nisi. Id sunt excepteur nisi officia elit qui aliqua excepteur aliquip fugiat et do Lorem. Qui cupidatat commodo consectetur do laborum elit aute ipsum aliquip. Pariatur dolore commodo enim aute excepteur.\\r\\n", "[1].about");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "[1].about");

    has_value<liminal_json_io::types::Object_t>(true, "[13]");
    type_eq(liminal_json_io::types::ValueTypes::OBJECT, "[13]");

    has_value<liminal_json_io::types::String_t>(true, "[13].registered");
    value_eq<liminal_json_io::types::String_t>("2022-03-08T09:55:37 -01:00", "[13].registered");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "[13].registered");

    has_value<liminal_json_io::types::Object_t>(true, "[14]");
    type_eq(liminal_json_io::types::ValueTypes::OBJECT, "[14]");

    has_value<liminal_json_io::types::FloatNum_t>(true, "[14].latitude");
    value_eq<liminal_json_io::types::FloatNum_t>(-76.371709, "[14].latitude");
    type_eq(liminal_json_io::types::ValueTypes::FLOAT_NUM, "[14].latitude");

    has_value<liminal_json_io::types::Array_t>(true, "[14].friends");
    type_eq(liminal_json_io::types::ValueTypes::ARRAY, "[14].friends");
    
    has_value<liminal_json_io::types::Object_t>(true, "[14].friends[1]");
    type_eq(liminal_json_io::types::ValueTypes::OBJECT, "[14].friends[1]");

    has_value<liminal_json_io::types::IntNum_t>(true, "[14].friends[1].id");
    value_eq<liminal_json_io::types::IntNum_t>(1, "[14].friends[1].id");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "[14].friends[1].id");
}

TEST_F(LiminalJsonIOInJsonGetMethod, WhenGivenNestedJsonFile) {
    _instance.parse(liminal_json_io_test::paths::VALID__NESTED);

    has_value<liminal_json_io::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested");
    value_eq<liminal_json_io::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested");
    type_eq(liminal_json_io::types::ValueTypes::BOOL, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.isNested");

    has_value<liminal_json_io::types::String_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1");
    value_eq<liminal_json_io::types::String_t>("Random Value 1", "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey1");
    
    has_value<liminal_json_io::types::IntNum_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2");
    value_eq<liminal_json_io::types::IntNum_t>(42, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2");

    has_value<liminal_json_io::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3");
    value_eq<liminal_json_io::types::Bool_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3");
    type_eq(liminal_json_io::types::ValueTypes::BOOL, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey3");
    
    has_value<liminal_json_io::types::String_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags[5]");
    value_eq<liminal_json_io::types::String_t>("proident", "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags[5]");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags[5]");
    
    has_value<liminal_json_io::types::IntNum_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2].id");
    value_eq<liminal_json_io::types::IntNum_t>(2, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2].id");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2].id");

    has_value<liminal_json_io::types::String_t>(true, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting");
    value_eq<liminal_json_io::types::String_t>("Hello, Madelyn Gilliam! You have 8 unread messages.", "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting");

    has_value<liminal_json_io::types::String_t>(true, "address.country");
    value_eq<liminal_json_io::types::String_t>("USA", "address.country");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "address.country");

    has_value<liminal_json_io::types::String_t>(true, "phone");
    value_eq<liminal_json_io::types::String_t>("+1 123-456-7890", "phone");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "phone");

    has_value<liminal_json_io::types::IntNum_t>(true, "grades.english");
    value_eq<liminal_json_io::types::IntNum_t>(92, "grades.english");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "grades.english");
}

TEST_F(LiminalJsonIOInJsonGetMethod, WhenGivenWrongRequestedType) {
    _instance.parse(liminal_json_io_test::paths::VALID__NESTED);
    EXPECT_FALSE(_instance.get<liminal_json_io::types::FloatNum_t>("nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21.randomKey2").has_value());
    EXPECT_FALSE(_instance.get<liminal_json_io::types::Null_t>("nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.greeting").has_value());

    _instance.parse(liminal_json_io_test::paths::VALID__LARGE);
    EXPECT_FALSE(_instance.get<liminal_json_io::types::IntNum_t>("[14].latitude").has_value());

    _instance.parse(liminal_json_io_test::paths::VALID__BASIC);
    EXPECT_FALSE(_instance.get<liminal_json_io::types::FloatNum_t>("name").has_value());
}

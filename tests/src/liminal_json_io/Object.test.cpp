/**
 * @file Object.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-03
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "liminal_json_io/InJson.hpp"
#include "liminal_json_io/types.hpp"

#include "constants.test.hpp"
#include "liminal_json_io.test.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include <filesystem>

/**
 * Class liminal_json_io::types::Object
*       -> Object(const Object &other) : test with simple values, nested values, edge cases
            -> for each of the following tetsts, test with both InJson.parsing and this constructor
 *      -> &operator= : test with simple values, nested values, edge cases
            -> for each of the following tetsts, test with both InJson.parsing and this constructor, and the operator =
 *      -> hasNestedComplexValues(void) : test both with nested and non nested, several nested, edge cases
            -> test fixture, and test_p with returned value
 *      -> getNestedComplexValuesKeys : test both with nested and non nested, several nested, edge cases, test every values
 *          -> test fixture, and test_p with returned value
 *      ->  template <typename T>
            requires is_in_variant_v<T, types::SimpleTypes_t>
            std::optional<T> get(const types::Key_t &key) const : same that with in json but for object only
 *              -> for each case, make a test_f for each case and tests each or almost each values depending on the size

        -> make sure to test equality with each simple types

        -> edge case :
            -> json object inside of which there's a stringed object : "{"yes": "no"}" for has complexvalues and getcomplexvalues
            -> test if special chars match : '\n', '\t', etc... (option in parse to read special chars ?)
 */

// param = tuple<string:  filePath, string: jsonKeyPath, bool: expectedValue>
class LiminalJsonIoObjectHasComplexValueMethod : public ::testing::TestWithParam<std::tuple<std::string, std::string, bool>> {
    protected:
        liminal_json_io::types::Object_t _instanceCreatedFromInJsonParseMethod;
        liminal_json_io::types::Object_t _instanceCreatedFromCopyConstructor;
        liminal_json_io::types::Object_t _instanceCreatedFromEqualOperator;

        LiminalJsonIoObjectHasComplexValueMethod(void) : 
        _instanceCreatedFromInJsonParseMethod{__createInstanceFromInJsonParseMethod()},
        _instanceCreatedFromCopyConstructor{__createInstanceFromCopyConstructor()},
        _instanceCreatedFromEqualOperator{__createInstanceFromEqualOperator()}
        {}

    private:
        liminal_json_io::types::Object_t __createInstanceFromInJsonParseMethod(void) {
            std::filesystem::current_path("../../tests");
            liminal_json_io::InJson inJson{};
            inJson.parse(std::get<0>(GetParam()));
            return inJson.get<liminal_json_io::types::Object_t>(std::get<1>(GetParam())).value();
        }

        liminal_json_io::types::Object_t __createInstanceFromCopyConstructor(void) {
            return liminal_json_io::types::Object_t(this->_instanceCreatedFromInJsonParseMethod);
        }

        liminal_json_io::types::Object_t __createInstanceFromEqualOperator(void) {
            liminal_json_io::types::Object_t copy = this->_instanceCreatedFromInJsonParseMethod;
            return copy;
        }
};

TEST_P(LiminalJsonIoObjectHasComplexValueMethod, ReturnGivenBool) {
    EXPECT_EQ(_instanceCreatedFromInJsonParseMethod.hasNestedComplexValues(), std::get<2>(GetParam()));
    EXPECT_EQ(_instanceCreatedFromCopyConstructor.hasNestedComplexValues(), std::get<2>(GetParam()));
    EXPECT_EQ(_instanceCreatedFromEqualOperator.hasNestedComplexValues(), std::get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathOfObjectContainingComplexValues,
    LiminalJsonIoObjectHasComplexValueMethod,
    testing::Values(
        std::make_tuple(liminal_json_io_test::paths::VALID__BASIC, "address", true),
        std::make_tuple(liminal_json_io_test::paths::VALID__BASIC, "hobbies[4]", true),

        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "", true),
        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "nestedData", true),
        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4", true),
        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8", true),
        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15", true),
        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20", true),
        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9", true),

        std::make_tuple(liminal_json_io_test::paths::VALID__LARGE, "[0]", true),
        std::make_tuple(liminal_json_io_test::paths::VALID__LARGE, "[14]", true),
        std::make_tuple(liminal_json_io_test::paths::VALID__LARGE, "[9].friends[0]", true)
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathOfObjectNotContainingComplexValues,
    LiminalJsonIoObjectHasComplexValueMethod,
    testing::Values(
        std::make_tuple(liminal_json_io_test::paths::VALID__BASIC, "address.story", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__BASIC, "hobbies[3]", false),

        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "address", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "grades", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[0]", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[1]", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2]", false),

        std::make_tuple(liminal_json_io_test::paths::VALID__LARGE, "[0].friends[0]", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__LARGE, "[0].friends[1]", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__LARGE, "[0].friends[2]", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__LARGE, "[9].friends[0].specialFriend", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__LARGE, "[9].friends[1]", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__LARGE, "[9].friends[2]", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__LARGE, "[13].friends[0]", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__LARGE, "[13].friends[1]", false),
        std::make_tuple(liminal_json_io_test::paths::VALID__LARGE, "[13].friends[2]", false)

    )
);

class LiminalJsonIoObjectGetMethod : public ::testing::Test {
    protected:
        
        LiminalJsonIoObjectGetMethod(void)
        {}

        void load_object(const std::string &filePath, const std::string &jsonPath = "") {
            this->__instanceCreatedFromInJsonParseMethod = std::make_unique<liminal_json_io::types::Object_t>(this->__createInstanceFromInJsonParseMethod(filePath, jsonPath));
            this->__instanceCreatedFromCopyConstructor = std::make_unique<liminal_json_io::types::Object_t>(this->__createInstanceFromCopyConstructor());
            this->__instanceCreatedFromEqualOperator = std::make_unique<liminal_json_io::types::Object_t>(this->__createInstanceFromEqualOperator());
        }

        template<typename T>
        requires liminal_json_io::is_in_variant_v<T, liminal_json_io::types::SimpleTypes_t>
        void value_eq(const T &expected, const std::string &jsonPath = "") {
            if constexpr (std::is_same_v<T, liminal_json_io::types::FloatNum_t>) {
                EXPECT_NEAR(__instanceCreatedFromInJsonParseMethod->get<T>(jsonPath).value(), expected, constants::EXPECT_NEAR_ABSOLUTE_ERROR);
                EXPECT_NEAR(__instanceCreatedFromCopyConstructor->get<T>(jsonPath).value(), expected, constants::EXPECT_NEAR_ABSOLUTE_ERROR);
                EXPECT_NEAR(__instanceCreatedFromEqualOperator->get<T>(jsonPath).value(), expected, constants::EXPECT_NEAR_ABSOLUTE_ERROR);
            }
            else {
                EXPECT_EQ(__instanceCreatedFromInJsonParseMethod->get<T>(jsonPath).value(), expected);
                EXPECT_EQ(__instanceCreatedFromCopyConstructor->get<T>(jsonPath).value(), expected);
                EXPECT_EQ(__instanceCreatedFromEqualOperator->get<T>(jsonPath).value(), expected);
            }
        }

    private:
        std::unique_ptr<liminal_json_io::types::Object_t> __instanceCreatedFromInJsonParseMethod;
        std::unique_ptr<liminal_json_io::types::Object_t> __instanceCreatedFromCopyConstructor;
        std::unique_ptr<liminal_json_io::types::Object_t> __instanceCreatedFromEqualOperator;

        liminal_json_io::types::Object_t __createInstanceFromInJsonParseMethod(const std::string &filePath = "", const std::string &jsonPath = "") {
            liminal_json_io::InJson inJson{};
            inJson.parse(filePath);
            return inJson.get<liminal_json_io::types::Object_t>(jsonPath).value();
        }

        liminal_json_io::types::Object_t __createInstanceFromCopyConstructor(void) {
            return liminal_json_io::types::Object_t(*this->__instanceCreatedFromInJsonParseMethod);
        }

        liminal_json_io::types::Object_t __createInstanceFromEqualOperator(void) {
            liminal_json_io::types::Object_t copy = *this->__instanceCreatedFromInJsonParseMethod;
            return copy;
        }
};

TEST_F(LiminalJsonIoObjectGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile) {
    std::filesystem::current_path("../../tests");

    load_object(liminal_json_io_test::paths::VALID__BASIC, "address.story");
    value_eq<liminal_json_io::types::IntNum_t>(15, "left");
    value_eq<liminal_json_io::types::FloatNum_t>(678.5, "right");

    load_object(liminal_json_io_test::paths::VALID__BASIC, "address");
    value_eq<liminal_json_io::types::String_t>("123 Main St", "street");
    value_eq<liminal_json_io::types::String_t>("Anytown", "city");
    value_eq<liminal_json_io::types::String_t>("Anystate", "state");
    value_eq<liminal_json_io::types::IntNum_t>(12345, "postalCode");
    value_eq<liminal_json_io::types::FloatNum_t>(42.84, "anotherData");

    load_object(liminal_json_io_test::paths::VALID__BASIC, "hobbies[3]");
    value_eq<liminal_json_io::types::String_t>("no", "nestedHobby");

    load_object(liminal_json_io_test::paths::VALID__BASIC, "hobbies[4]");
    value_eq<liminal_json_io::types::Null_t>(nullptr, "nothingImportantHere");

    load_object(liminal_json_io_test::paths::VALID__BASIC, "");
    value_eq<liminal_json_io::types::String_t>("John Doe", "name");
    value_eq<liminal_json_io::types::IntNum_t>(30, "age");
    value_eq<liminal_json_io::types::Bool_t>(true, "isEmployed");
    value_eq<liminal_json_io::types::String_t>("yes", "happy");
};

TEST_F(LiminalJsonIoObjectGetMethod, ShouldMatchExpectedValuesWithLargeJsonFile) {
    std::filesystem::current_path("../../tests");

    load_object(liminal_json_io_test::paths::VALID__LARGE, "[0]");
    value_eq<liminal_json_io::types::String_t>("018a1a54-0e66-44b2-bf88-6349a4839645", "guid");
    value_eq<liminal_json_io::types::String_t>("2019-12-25T04:23:12 -01:00", "registered");
    value_eq<liminal_json_io::types::FloatNum_t>(-48.602054, "latitude");
    value_eq<liminal_json_io::types::String_t>("+1 (906) 540-3410", "phone");
    value_eq<liminal_json_io::types::String_t>("kirbynielsen@dragbot.com", "email");
    value_eq<liminal_json_io::types::String_t>("http://placehold.it/32x32", "picture");
    value_eq<liminal_json_io::types::String_t>("$2,399.08", "balance");

    load_object(liminal_json_io_test::paths::VALID__LARGE, "[9].friends[0]");
    value_eq<liminal_json_io::types::IntNum_t>(0, "id");
    value_eq<liminal_json_io::types::String_t>("Gomez Rowe", "name");

    load_object(liminal_json_io_test::paths::VALID__LARGE, "[9].friends[0].specialFriend");
    value_eq<liminal_json_io::types::String_t>("John", "firstsName");
    value_eq<liminal_json_io::types::String_t>("Doe", "secondName");
}

TEST_F(LiminalJsonIoObjectGetMethod, ShouldMatchExpectedValuesWithNestedJsonFile) {
    std::filesystem::current_path("../../tests");

    load_object(liminal_json_io_test::paths::VALID__NESTED, "address");
    value_eq<liminal_json_io::types::String_t>("123 Main St", "street");
    value_eq<liminal_json_io::types::String_t>("Anytown", "city");
    value_eq<liminal_json_io::types::String_t>("USA", "country");

    load_object(liminal_json_io_test::paths::VALID__NESTED, "grades");
    value_eq<liminal_json_io::types::IntNum_t>(85, "math");
    value_eq<liminal_json_io::types::IntNum_t>(92, "english");
    value_eq<liminal_json_io::types::IntNum_t>(78, "history");

    load_object(liminal_json_io_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8");
    value_eq<liminal_json_io::types::Bool_t>(true, "isNested");

    load_object(liminal_json_io_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21");
    value_eq<liminal_json_io::types::String_t>("Random Value 1", "randomKey1");
    value_eq<liminal_json_io::types::IntNum_t>(42, "randomKey2");
    value_eq<liminal_json_io::types::Bool_t>(true, "randomKey3");

    load_object(liminal_json_io_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9");
    value_eq<liminal_json_io::types::FloatNum_t>(155.61306, "longitude");
    value_eq<liminal_json_io::types::String_t>("Hello, Madelyn Gilliam! You have 8 unread messages.", "greeting");
    value_eq<liminal_json_io::types::String_t>("banana", "favoriteFruit");
}
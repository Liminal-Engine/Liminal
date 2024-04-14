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

#include "jsonio/InJson.hpp"
#include "jsonio/types.hpp"

#include "constants.test.hpp"
#include "jsonio.test.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <tuple>
#include <filesystem>

// param = tuple<string:  filePath, string: jsonKeyPath, bool: expectedValue, std::vector<std::string>: separators>
using ObjectParamType = std::tuple<fs::Path, std::string, bool, std::vector<std::string>>;
class JsonIOObjectHasComplexValueMethod : public ::testing::TestWithParam<ObjectParamType> {
    protected:
        jsonio::types::Object_t _instanceCreatedFromInJsonParseMethod;
        jsonio::types::Object_t _instanceCreatedFromCopyConstructor;
        jsonio::types::Object_t _instanceCreatedFromEqualOperator;

        JsonIOObjectHasComplexValueMethod(void) : 
        _instanceCreatedFromInJsonParseMethod{__createInstanceFromInJsonParseMethod()},
        _instanceCreatedFromCopyConstructor{__createInstanceFromCopyConstructor()},
        _instanceCreatedFromEqualOperator{__createInstanceFromEqualOperator()}
        {}

    private:
        jsonio::types::Object_t __createInstanceFromInJsonParseMethod(void) {
            
            jsonio::InJson inJson{};
            inJson.parse(std::get<0>(GetParam()));
            return inJson.get<jsonio::types::Object_t>(std::get<1>(GetParam()), std::get<3>(GetParam())).value();
        }

        jsonio::types::Object_t __createInstanceFromCopyConstructor(void) {
            return jsonio::types::Object_t(this->_instanceCreatedFromInJsonParseMethod);
        }

        jsonio::types::Object_t __createInstanceFromEqualOperator(void) {
            jsonio::types::Object_t copy = this->_instanceCreatedFromInJsonParseMethod;
            return copy;
        }
};

ObjectParamType createObjectParams(
    const fs::Path &filePath,
    const std::string &jsonKeyPath,
    const bool &res,
    const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS
) {
    return std::make_tuple(filePath, jsonKeyPath, res, separators);
}

TEST_P(JsonIOObjectHasComplexValueMethod, ReturnGivenBool) {
    EXPECT_EQ(_instanceCreatedFromInJsonParseMethod.hasNestedComplexValues(), std::get<2>(GetParam()));
    EXPECT_EQ(_instanceCreatedFromCopyConstructor.hasNestedComplexValues(), std::get<2>(GetParam()));
    EXPECT_EQ(_instanceCreatedFromEqualOperator.hasNestedComplexValues(), std::get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathOfObjectContainingComplexValues,
    JsonIOObjectHasComplexValueMethod,
    testing::Values(
        createObjectParams(jsonio_test::paths::VALID__BASIC, "address", true),
        createObjectParams(jsonio_test::paths::VALID__BASIC, "hobbies[4]", true),

        createObjectParams(jsonio_test::paths::VALID__EDGE_CASES, "", true),
        createObjectParams(jsonio_test::paths::VALID__EDGE_CASES, "78", true),
        createObjectParams(jsonio_test::paths::VALID__EDGE_CASES, "78.40014[0]", true),

        createObjectParams(jsonio_test::paths::VALID__NESTED, "", true),
        createObjectParams(jsonio_test::paths::VALID__NESTED, "nestedData", true),
        createObjectParams(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4", true),
        createObjectParams(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8", true),
        createObjectParams(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15", true),
        createObjectParams(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20", true),
        createObjectParams(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9", true),

        createObjectParams(jsonio_test::paths::VALID__LARGE, "[0]", true),
        createObjectParams(jsonio_test::paths::VALID__LARGE, "[14]", true),
        createObjectParams(jsonio_test::paths::VALID__LARGE, "[9].friends[0]", true)
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathOfObjectNotContainingComplexValues,
    JsonIOObjectHasComplexValueMethod,
    testing::Values(
        createObjectParams(jsonio_test::paths::VALID__BASIC, "address.story", false),
        createObjectParams(jsonio_test::paths::VALID__BASIC, "hobbies[3]", false),

        createObjectParams(jsonio_test::paths::VALID__EDGE_CASES, "-12345", false),
        createObjectParams(jsonio_test::paths::VALID__EDGE_CASES, "78/an.other.[ke.y]<0>", false, std::vector<std::string>{"/", "<", ">"}),

        createObjectParams(jsonio_test::paths::VALID__NESTED, "address", false),
        createObjectParams(jsonio_test::paths::VALID__NESTED, "grades", false),
        createObjectParams(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21", false),
        createObjectParams(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[0]", false),
        createObjectParams(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[1]", false),
        createObjectParams(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends[2]", false),

        createObjectParams(jsonio_test::paths::VALID__LARGE, "[0].friends[0]", false),
        createObjectParams(jsonio_test::paths::VALID__LARGE, "[0].friends[1]", false),
        createObjectParams(jsonio_test::paths::VALID__LARGE, "[0].friends[2]", false),
        createObjectParams(jsonio_test::paths::VALID__LARGE, "[9].friends[0].specialFriend", false),
        createObjectParams(jsonio_test::paths::VALID__LARGE, "[9].friends[1]", false),
        createObjectParams(jsonio_test::paths::VALID__LARGE, "[9].friends[2]", false),
        createObjectParams(jsonio_test::paths::VALID__LARGE, "[13].friends[0]", false),
        createObjectParams(jsonio_test::paths::VALID__LARGE, "[13].friends[1]", false),
        createObjectParams(jsonio_test::paths::VALID__LARGE, "[13].friends[2]", false)
    )
);

class JsonIOObjectGetMethod : public ::testing::Test {
    protected:
        
        JsonIOObjectGetMethod(void)
        {}

        void load_object(
            const fs::Path &filePath,
            const std::string &jsonPath = "",
            const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS
        ) {
            this->__instanceCreatedFromInJsonParseMethod = std::make_unique<jsonio::types::Object_t>(this->__createInstanceFromInJsonParseMethod(filePath, jsonPath, separators));
            this->__instanceCreatedFromCopyConstructor = std::make_unique<jsonio::types::Object_t>(this->__createInstanceFromCopyConstructor());
            this->__instanceCreatedFromEqualOperator = std::make_unique<jsonio::types::Object_t>(this->__createInstanceFromEqualOperator());
        }

        template<typename T>
        requires jsonio::is_in_variant_v<T, jsonio::types::SimpleTypes_t>
        void value_eq(
            const T &expected,
            const std::string &jsonPath = ""
        ) {
            if constexpr (std::is_same_v<T, jsonio::types::FloatNum_t>) {
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
        std::unique_ptr<jsonio::types::Object_t> __instanceCreatedFromInJsonParseMethod;
        std::unique_ptr<jsonio::types::Object_t> __instanceCreatedFromCopyConstructor;
        std::unique_ptr<jsonio::types::Object_t> __instanceCreatedFromEqualOperator;

        jsonio::types::Object_t __createInstanceFromInJsonParseMethod(
            const fs::Path &filePath = fs::Path{""},
            const std::string &jsonPath = "",
            const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS
        ) {
            jsonio::InJson inJson{};
            inJson.parse(filePath);
            return inJson.get<jsonio::types::Object_t>(jsonPath, separators).value();
        }

        jsonio::types::Object_t __createInstanceFromCopyConstructor(void) {
            return jsonio::types::Object_t(*this->__instanceCreatedFromInJsonParseMethod);
        }

        jsonio::types::Object_t __createInstanceFromEqualOperator(void) {
            jsonio::types::Object_t copy = *this->__instanceCreatedFromInJsonParseMethod;
            return copy;
        }
};

TEST_F(JsonIOObjectGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile1) {
    

    load_object(jsonio_test::paths::VALID__BASIC, "address.story");
    value_eq<jsonio::types::IntNum_t>(15, "left");
    value_eq<jsonio::types::FloatNum_t>(678.5, "right");
};

TEST_F(JsonIOObjectGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile21) {
    
    load_object(jsonio_test::paths::VALID__BASIC, "address");
    value_eq<jsonio::types::String_t>("123 Main St", "street");
    value_eq<jsonio::types::String_t>("Anytown", "city");
    value_eq<jsonio::types::String_t>("Anystate", "state");
    value_eq<jsonio::types::IntNum_t>(12345, "postalCode");
    value_eq<jsonio::types::FloatNum_t>(42.84, "anotherData");
};

TEST_F(JsonIOObjectGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile3) {
    

    load_object(jsonio_test::paths::VALID__BASIC, "hobbies[3]");
    value_eq<jsonio::types::String_t>("no", "nestedHobby");
};

TEST_F(JsonIOObjectGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile4) {
    
    load_object(jsonio_test::paths::VALID__BASIC, "hobbies[4]");
    value_eq<jsonio::types::Null_t>(nullptr, "nothingImportantHere");
};

TEST_F(JsonIOObjectGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile5) {
    
    load_object(jsonio_test::paths::VALID__BASIC, "");
    value_eq<jsonio::types::String_t>("John Doe", "name");
    value_eq<jsonio::types::IntNum_t>(30, "age");
    value_eq<jsonio::types::Bool_t>(true, "isEmployed");
    value_eq<jsonio::types::String_t>("yes", "happy");
};



TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithEdgeCasesJsonFile1) {
    

    load_object(jsonio_test::paths::VALID__EDGE_CASES, "");
    value_eq<jsonio::types::String_t>("{'yes': 'no}", "/////////....//////?!?!?!!!![12e-89]");
};

TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithEdgeCasesJsonFile2) {
    

    load_object(jsonio_test::paths::VALID__EDGE_CASES, "78/an.other.[ke.y]<0>", std::vector<std::string>{"/", "<", ">"});
    value_eq<jsonio::types::String_t>("no", "yes");
};

TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithEdgeCasesJsonFile3) {
    

    load_object(jsonio_test::paths::VALID__EDGE_CASES, "78/an.other.[ke.y]<1>", std::vector<std::string>{"/", "<", ">"});
    value_eq<jsonio::types::Null_t>(nullptr, "no");
};



TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithLargeJsonFile1) {
    

    load_object(jsonio_test::paths::VALID__LARGE, "[0]");
    value_eq<jsonio::types::String_t>("018a1a54-0e66-44b2-bf88-6349a4839645", "guid");
    value_eq<jsonio::types::String_t>("2019-12-25T04:23:12 -01:00", "registered");
    value_eq<jsonio::types::FloatNum_t>(-48.602054, "latitude");
    value_eq<jsonio::types::String_t>("+1 (906) 540-3410", "phone");
    value_eq<jsonio::types::String_t>("kirbynielsen@dragbot.com", "email");
    value_eq<jsonio::types::String_t>("http://placehold.it/32x32", "picture");
    value_eq<jsonio::types::String_t>("$2,399.08", "balance");
};

TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithLargeJsonFile2) {
    

    load_object(jsonio_test::paths::VALID__LARGE, "[9].friends[0]");
    value_eq<jsonio::types::IntNum_t>(0, "id");
    value_eq<jsonio::types::String_t>("Gomez Rowe", "name");
};

TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithLargeJsonFile3) {
    

    load_object(jsonio_test::paths::VALID__LARGE, "[9].friends[0].specialFriend");
    value_eq<jsonio::types::String_t>("John", "firstsName");
    value_eq<jsonio::types::String_t>("Doe", "secondName");
};



TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithNestedJsonFile1) {
    

    load_object(jsonio_test::paths::VALID__NESTED, "address");
    value_eq<jsonio::types::String_t>("123 Main St", "street");
    value_eq<jsonio::types::String_t>("Anytown", "city");
    value_eq<jsonio::types::String_t>("USA", "country");
};

TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithNestedJsonFile2) {
    

    load_object(jsonio_test::paths::VALID__NESTED, "address");
    load_object(jsonio_test::paths::VALID__NESTED, "grades");
    value_eq<jsonio::types::IntNum_t>(85, "math");
    value_eq<jsonio::types::IntNum_t>(92, "english");
    value_eq<jsonio::types::IntNum_t>(78, "history");
};

TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithNestedJsonFile3) {
    

    load_object(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8");
    value_eq<jsonio::types::Bool_t>(true, "isNested");
};

TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithNestedJsonFile4) {
    

    load_object(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.level10.level11.level12.level13.level14.level15.level16.level17.level18.level19.level20.level21");
    value_eq<jsonio::types::String_t>("Random Value 1", "randomKey1");
    value_eq<jsonio::types::IntNum_t>(42, "randomKey2");
    value_eq<jsonio::types::Bool_t>(true, "randomKey3");
};

TEST_F(JsonIOObjectGetMethod, ShouldMatchExpectedValuesWithNestedJsonFile5) {
    

    load_object(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9");
    value_eq<jsonio::types::FloatNum_t>(155.61306, "longitude");
    value_eq<jsonio::types::String_t>("Hello, Madelyn Gilliam! You have 8 unread messages.", "greeting");
    value_eq<jsonio::types::String_t>("banana", "favoriteFruit");
}
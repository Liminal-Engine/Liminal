/**
 * @file Array.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-17
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
using ArrayHasComplexValueMethodParamType = std::tuple<fs::Path, std::string, bool, std::vector<std::string>>;
class JsonIOArrayHasComplexValueMethod : public ::testing::TestWithParam<ArrayHasComplexValueMethodParamType> {
    protected:
        jsonio::types::Array_t _instanceCreatedFromInJsonParseMethod;
        jsonio::types::Array_t _instanceCreatedFromCopyConstructor;
        jsonio::types::Array_t _instanceCreatedFromEqualOperator; 

    JsonIOArrayHasComplexValueMethod(void) : 
    _instanceCreatedFromInJsonParseMethod{__createInstanceFromInJsonParseMethod()},
    _instanceCreatedFromCopyConstructor{__createInstanceFromCopyConstructor()},
    _instanceCreatedFromEqualOperator{__createInstanceFromEqualOperator()}
    {}

    private:
        jsonio::types::Array_t __createInstanceFromInJsonParseMethod(void) {
            jsonio::InJson inJson{};
            inJson.parse(std::get<0>(GetParam()));
            return inJson.get<jsonio::types::Array_t>(std::get<1>(GetParam()), std::get<3>(GetParam())).value();
        }

        jsonio::types::Array_t __createInstanceFromCopyConstructor(void) {
            return jsonio::types::Array_t(this->_instanceCreatedFromInJsonParseMethod);
        }

        jsonio::types::Array_t __createInstanceFromEqualOperator(void) {
            jsonio::types::Array_t copy = this->_instanceCreatedFromInJsonParseMethod;
            return copy;
        }
};

ArrayHasComplexValueMethodParamType createArrayHasComplexValueMethodParams(
    const fs::Path &filePath,
    const std::string &jsonKeyPath,
    const bool &res,
    const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS
) {
    return std::make_tuple(filePath, jsonKeyPath, res, separators);
}

TEST_P(JsonIOArrayHasComplexValueMethod, ReturnGivenBool) {
    EXPECT_EQ(_instanceCreatedFromInJsonParseMethod.hasNestedComplexValues(), std::get<2>(GetParam()));
    EXPECT_EQ(_instanceCreatedFromCopyConstructor.hasNestedComplexValues(), std::get<2>(GetParam()));
    EXPECT_EQ(_instanceCreatedFromEqualOperator.hasNestedComplexValues(), std::get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathOfArrayContainingComplexValues,
    JsonIOArrayHasComplexValueMethod,
    testing::Values(
        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__BASIC, "hobbies", true),

        
        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__EDGE_CASES, "78/40014", true, std::vector<std::string>{"/", "[", "]"}),
        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__EDGE_CASES, "78/an.other.[ke.y]", true, std::vector<std::string>{"/", "<", ">"}),

        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.friends", true),

        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__LARGE, "[0].friends", true),
        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__LARGE, "[9].friends", true),
        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__LARGE, "[14].friends", true)
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathOfArrayNotContainingComplexValues,
    JsonIOArrayHasComplexValueMethod,
    testing::Values(
        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__BASIC, "hobbies[4].secondNestedHobbies", false),

        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__EDGE_CASES, "78.40014", false, std::vector<std::string>{"/", "[", "]"}),
        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__EDGE_CASES, "78/40014[0]/yes", false, std::vector<std::string>{"/", "[", "]"}),

        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__NESTED, "interests", false),
        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags", false),
        

        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__LARGE, "[0].tags", false),
        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__LARGE, "[9].tags", false),
        createArrayHasComplexValueMethodParams(jsonio_test::paths::VALID__LARGE, "[14].tags", false)

    )
);

class JsonIOArrayGetMethod : public ::testing::Test {
    protected:
        
        JsonIOArrayGetMethod(void)
        {}

        void load_array(
            const fs::Path &filePath,
            const std::string &jsonPath = "",
            const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS
        ) {
            this->__instanceCreatedFromInJsonParseMethod = std::make_unique<jsonio::types::Array_t>(this->__createInstanceFromInJsonParseMethod(filePath, jsonPath, separators));
            this->__instanceCreatedFromCopyConstructor = std::make_unique<jsonio::types::Array_t>(this->__createInstanceFromCopyConstructor());
            this->__instanceCreatedFromEqualOperator = std::make_unique<jsonio::types::Array_t>(this->__createInstanceFromEqualOperator());
        }

        template<typename T>
        requires jsonio::is_in_variant_v<T, jsonio::types::SimpleTypes_t>
        void value_eq(
            const T &expected,
            const std::size_t &index
        ) {
            if constexpr (std::is_same_v<T, jsonio::types::FloatNum_t>) {
                EXPECT_NEAR(__instanceCreatedFromInJsonParseMethod->get<T>(index).value(), expected, constants::EXPECT_NEAR_ABSOLUTE_ERROR);
                EXPECT_NEAR(__instanceCreatedFromCopyConstructor->get<T>(index).value(), expected, constants::EXPECT_NEAR_ABSOLUTE_ERROR);
                EXPECT_NEAR(__instanceCreatedFromEqualOperator->get<T>(index).value(), expected, constants::EXPECT_NEAR_ABSOLUTE_ERROR);
            }
            else {
                EXPECT_EQ(__instanceCreatedFromInJsonParseMethod->get<T>(index).value(), expected);
                EXPECT_EQ(__instanceCreatedFromCopyConstructor->get<T>(index).value(), expected);
                EXPECT_EQ(__instanceCreatedFromEqualOperator->get<T>(index).value(), expected);
            }
        }

    private:
        std::unique_ptr<jsonio::types::Array_t> __instanceCreatedFromInJsonParseMethod;
        std::unique_ptr<jsonio::types::Array_t> __instanceCreatedFromCopyConstructor;
        std::unique_ptr<jsonio::types::Array_t> __instanceCreatedFromEqualOperator;

        jsonio::types::Array_t __createInstanceFromInJsonParseMethod(
            const fs::Path &filePath = fs::Path{""},
            const std::string &jsonPath = "",
            const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS
        ) {
            jsonio::InJson inJson{};
            inJson.parse(filePath);
            return inJson.get<jsonio::types::Array_t>(jsonPath, separators).value();
        }

        jsonio::types::Array_t __createInstanceFromCopyConstructor(void) {
            return jsonio::types::Array_t(*this->__instanceCreatedFromInJsonParseMethod);
        }

        jsonio::types::Array_t __createInstanceFromEqualOperator(void) {
            jsonio::types::Array_t copy = *this->__instanceCreatedFromInJsonParseMethod;
            return copy;
        }
};

TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile1) {
    

    load_array(jsonio_test::paths::VALID__BASIC, "hobbies");
    value_eq<jsonio::types::String_t>("reading", 0);
    value_eq<jsonio::types::String_t>("gaming", 1);
    value_eq<jsonio::types::String_t>("hiking", 2);
}

TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesWithBasicJsonFile2) {
    

    load_array(jsonio_test::paths::VALID__BASIC, "hobbies[4].secondNestedHobbies");
    value_eq<jsonio::types::String_t>("un", 0);
    value_eq<jsonio::types::String_t>("dos", 1);
    value_eq<jsonio::types::IntNum_t>(3, 2);
    value_eq<jsonio::types::Null_t>(nullptr, 3);
};

TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesEdgeCasesJsonFile1) {
    

    load_array(jsonio_test::paths::VALID__EDGE_CASES, "78/40014!0$/yes", std::vector<std::string>{"/", "!", "$"});
    value_eq<jsonio::types::String_t>("no", 0);
    value_eq<jsonio::types::String_t>("maybe", 1);
    value_eq<jsonio::types::String_t>("this[is]a.[key]", 2);
};


TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesLargeJsonFile0) {
    

    load_array(jsonio_test::paths::VALID__LARGE, "[0].tags");
    value_eq<jsonio::types::String_t>("tempor", 0);
    value_eq<jsonio::types::String_t>("proident", 1);
    value_eq<jsonio::types::String_t>("ut", 2);
    value_eq<jsonio::types::String_t>("sint", 3);
    value_eq<jsonio::types::String_t>("ad", 4);
    value_eq<jsonio::types::String_t>("laboris", 5);
    value_eq<jsonio::types::String_t>("ullamco", 6);
};

TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesLargeJsonFile1) {
    

    load_array(jsonio_test::paths::VALID__LARGE, "[6].tags");
    value_eq<jsonio::types::String_t>("ullamco", 0);
    value_eq<jsonio::types::String_t>("dolore", 1);
    value_eq<jsonio::types::String_t>("officia", 2);
    value_eq<jsonio::types::String_t>("sit", 3);
    value_eq<jsonio::types::String_t>("deserunt", 4);
    value_eq<jsonio::types::String_t>("exercitation", 5);
    value_eq<jsonio::types::String_t>("deserunt", 6);
};

TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesLargeJsonFile2) {
    

    load_array(jsonio_test::paths::VALID__LARGE, "[9].tags");
    value_eq<jsonio::types::String_t>("voluptate", 0);
    value_eq<jsonio::types::String_t>("do", 1);
    value_eq<jsonio::types::String_t>("incididunt", 2);
    value_eq<jsonio::types::String_t>("commodo", 3);
    value_eq<jsonio::types::String_t>("ea", 4);
    value_eq<jsonio::types::String_t>("in", 5);
    value_eq<jsonio::types::String_t>("labore", 6);
};

TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesLargeJsonFile3) {
    

    load_array(jsonio_test::paths::VALID__LARGE, "[15].tags");
    value_eq<jsonio::types::String_t>("sit", 0);
    value_eq<jsonio::types::String_t>("deserunt", 1);
    value_eq<jsonio::types::String_t>("commodo", 2);
    value_eq<jsonio::types::String_t>("esse", 3);
    value_eq<jsonio::types::String_t>("aliquip", 4);
    value_eq<jsonio::types::String_t>("labore", 5);
    value_eq<jsonio::types::String_t>("deserunt", 6);
};

TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesNestedJsonFile1) {
    

    load_array(jsonio_test::paths::VALID__NESTED, "interests");
    value_eq<jsonio::types::String_t>("reading", 0);
    value_eq<jsonio::types::String_t>("traveling", 1);
    value_eq<jsonio::types::String_t>("coding", 2);
};

TEST_F(JsonIOArrayGetMethod, ShoudlMatchExpectedValuesNestedJsonFile2) {
    

    load_array(jsonio_test::paths::VALID__NESTED, "nestedData.level1.level2.level3.level4.level5.level6.level7.level8.level9.tags");
    value_eq<jsonio::types::String_t>("dolore", 0);
    value_eq<jsonio::types::String_t>("do", 1);
    value_eq<jsonio::types::String_t>("commodo", 2);
    value_eq<jsonio::types::String_t>("consequat", 3);
    value_eq<jsonio::types::String_t>("ut", 4);
    value_eq<jsonio::types::String_t>("proident", 5);
    value_eq<jsonio::types::String_t>("sint", 6);
};

// param = tuple<string:  filePath, string: jsonKeyPath, std::size_t: expectedValue, std::vector<std::string>: separators>
using ArrayGetLenMethodParamType = std::tuple<fs::Path, std::string, std::size_t, std::vector<std::string>>;
class JsonIOArrayGetLenMethod : public ::testing::TestWithParam<ArrayGetLenMethodParamType> {

    protected:
        jsonio::types::Array_t _instanceCreatedFromInJsonParseMethod;
        jsonio::types::Array_t _instanceCreatedFromCopyConstructor;
        jsonio::types::Array_t _instanceCreatedFromEqualOperator; 

    JsonIOArrayGetLenMethod(void) : 
    _instanceCreatedFromInJsonParseMethod{__createInstanceFromInJsonParseMethod()},
    _instanceCreatedFromCopyConstructor{__createInstanceFromCopyConstructor()},
    _instanceCreatedFromEqualOperator{__createInstanceFromEqualOperator()}
    {}

    private:
        jsonio::types::Array_t __createInstanceFromInJsonParseMethod(void) {
            
            jsonio::InJson inJson{};
            inJson.parse(std::get<0>(GetParam()));
            return inJson.get<jsonio::types::Array_t>(std::get<1>(GetParam()), std::get<3>(GetParam())).value();
        }

        jsonio::types::Array_t __createInstanceFromCopyConstructor(void) {
            return jsonio::types::Array_t(this->_instanceCreatedFromInJsonParseMethod);
        }

        jsonio::types::Array_t __createInstanceFromEqualOperator(void) {
            jsonio::types::Array_t copy = this->_instanceCreatedFromInJsonParseMethod;
            return copy;
        }
};

ArrayGetLenMethodParamType createArrayGetLenMethodParams(
    const fs::Path &filePath,
    const std::string &jsonKeyPath,
    const std::size_t &res,
    const std::vector<std::string> &separators = JSON_DEFAULT_SEPARATORS
) {
    return std::make_tuple(filePath, jsonKeyPath, res, separators);
}

TEST_P(JsonIOArrayGetLenMethod, ReturnGivenLength) {
    EXPECT_EQ(_instanceCreatedFromInJsonParseMethod.getLen(), std::get<2>(GetParam()));
    EXPECT_EQ(_instanceCreatedFromCopyConstructor.getLen(), std::get<2>(GetParam()));
    EXPECT_EQ(_instanceCreatedFromEqualOperator.getLen(), std::get<2>(GetParam()));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathOfArraysInValidJsonFiles,
    JsonIOArrayGetLenMethod,
    testing::Values(
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__BASIC, "hobbies", 5),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__BASIC, "hobbies[4].secondNestedHobbies", 4),

        createArrayGetLenMethodParams(jsonio_test::paths::VALID__EDGE_CASES, "78.40014", 0, std::vector<std::string>{"/", "[", "]"}),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__EDGE_CASES, "78.40014", 1),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__EDGE_CASES, "78.40014[0].yes", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__EDGE_CASES, "78/an.other.[ke.y]", 2, std::vector<std::string>{"/", "<", ">"}),


        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[0].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[0].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[1].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[1].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[2].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[2].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[3].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[3].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[4].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[4].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[5].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[5].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[6].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[6].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[7].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[7].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[8].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[8].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[9].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[9].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[10].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[10].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[11].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[11].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[12].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[12].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[13].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[13].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[14].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[14].friends", 3),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[15].tags", 7),
        createArrayGetLenMethodParams(jsonio_test::paths::VALID__LARGE, "[15].friends", 3)
    )
);
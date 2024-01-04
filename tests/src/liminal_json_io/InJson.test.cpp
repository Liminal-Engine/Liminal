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


//**********
// Incudes required for InJson internal calls
#include "liminal_json_io/include/_private/_lexing/_types.hpp"
#include "liminal_json_io/include/_private/_lexing/_lexing.hpp"
//**********

#include "liminal_json_io/InJson.hpp"

#include "constants.test.hpp"
#include "liminal_json_io.test.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <fstream>
#include <filesystem>

// Fixture
class liminal_json_io_InJson : public ::testing::Test {
    protected:
        liminal_json_io::InJson instance;
        const std::string nonExistingPath = "~~~~~thisPath/Sure----lyDontExists.unkownFileExt123456789";

        void createSimpleFile(void) {
            this->_fileContent = liminal_json_io_test::SIMPLE_JSON_NO_ERROR;
            std::ofstream tmpFile(this->_filePath);
            tmpFile << this->_fileContent;
            tmpFile.close();
        }

        void createComplexFile(void) {
            this->_fileContent = liminal_json_io_test::LARGE_JSON_NO_ERROR;
            std::ofstream tmpFile(this->_filePath);
            tmpFile << this->_fileContent;
            tmpFile.close();
        }

        void parse(void) {
            this->instance.parse(this->getFilePath());
        }


        template <typename T>
        requires liminal_json_io::is_in_variant_v<T, liminal_json_io::types::Any_t>
        void has_value(const std::string &jsonPath = "") {
            EXPECT_EQ(instance.get<T>(jsonPath).has_value(), true);
        }

        template <typename T>
        requires liminal_json_io::is_in_variant_v<T, liminal_json_io::types::Any_t>
        void value_eq(const T &value, const std::string jsonPath = "") {
            EXPECT_EQ(instance.get<T>(jsonPath).value(), value);
        }

        void value_near(const liminal_json_io::types::FloatNum_t &value, const std::string &jsonPath = "") {
            EXPECT_NEAR(instance.get<liminal_json_io::types::FloatNum_t>(jsonPath).value(), value, constants::EXPECT_NEAR_ABSOLUTE_ERROR);
        }

        void type_eq(const liminal_json_io::types::ValueTypes &type, const std::string &jsonPath = "") {
            EXPECT_EQ(instance.getType(jsonPath), type);
        }



        std::string getFilePath(void) const { return this->_filePath; }
        std::string getFileContent(void) const { return this->_fileContent; }

        void SetUp(void) override {
            std::filesystem::create_directories(std::filesystem::path{std::string{constants::TMP_FILE_DEFAULT_PATH}});
            this->_filePath = std::string{constants::TMP_FILE_DEFAULT_PATH} + std::string{"temp.json"};
            this->_fileContent = "";            
        }

        void TearDown(void) override {
            std::filesystem::remove_all(std::filesystem::path{std::string{constants::TMP_FILE_DEFAULT_PATH}});
            this->_filePath = "";
            this->_fileContent = "";
        }

    private:
        std::string _filePath;
        std::string _fileContent;
};

// Context : given path don't exists
TEST_F(liminal_json_io_InJson, parse__RETURN_PARSING_ERR__whenPathDontExists) {
    // File does not exsts yet, test should return NOK
    EXPECT_EQ(instance.parse(nonExistingPath), liminal_json_io::Status::PARSING_ERR);
}

// TODO : active once returned value of liminal_json_io parse have been implmented
// TEST_F(liminal_json_io_InJson, get__RETURN_EMPTY_OPTIONAL_ROOT_VALUE__whenPathDontExists) {
//     instance.parse(nonExistingPath);
//     EXPECT_EQ(instance.get<liminal_json_io::types::IntNum_t>().has_value(), false);
// }

// TEST_F(liminal_json_io_InJson, getType__RETURN_UNKNOWN_TYPE__whenPathDontExists) {

// }

// TEST_F(liminal_json_io_InJson, getType__RETURN_UNKNOWN_TYPE__whenPathDontExistsAndJsonPathInvaid) {

// }

// Context : simple basic file without errors is given :
TEST_F(liminal_json_io_InJson, parse__RETURN_OK__whenGivenSimpleFile) {
    createSimpleFile();
    EXPECT_EQ(instance.parse(getFilePath()), liminal_json_io::Status::OK);
}

TEST_F(liminal_json_io_InJson, get__RETURN_VALID_VALUES__whenGivenSimpleFile) {
    createSimpleFile();
    parse();

    has_value<liminal_json_io::types::Object_t>();
    has_value<liminal_json_io::types::String_t>("name");
    value_eq<liminal_json_io::types::String_t>("John Doe", "name");
    has_value<liminal_json_io::types::IntNum_t>("age");
    value_eq<liminal_json_io::types::IntNum_t>(30, "age");
    has_value<liminal_json_io::types::Bool_t>("isEmployed");
    value_eq<liminal_json_io::types::Bool_t>(true, "isEmployed");
    has_value<liminal_json_io::types::Object_t>("address");
    has_value<liminal_json_io::types::Object_t>("address.story");
    has_value<liminal_json_io::types::IntNum_t>("address.story.left");
    value_eq<liminal_json_io::types::IntNum_t>(15, "address.story.left");
    has_value<liminal_json_io::types::FloatNum_t>("address.story.right");
    value_near(678.5, "address.story.right");
    has_value<liminal_json_io::types::String_t>("address.street");
    value_eq<liminal_json_io::types::String_t>("123 Main St", "address.street");
    has_value<liminal_json_io::types::String_t>("address.city");
    value_eq<liminal_json_io::types::String_t>("Anytown", "address.city");
    has_value<liminal_json_io::types::String_t>("address.state");
    value_eq<liminal_json_io::types::String_t>("Anystate", "address.state");
    has_value<liminal_json_io::types::IntNum_t>("address.postalCode");
    value_eq<liminal_json_io::types::IntNum_t>(12345, "address.postalCode");
    has_value<liminal_json_io::types::FloatNum_t>("address.anotherData");
    value_near(42.84, "address.anotherData");
    has_value<liminal_json_io::types::Array_t>("hobbies");
    has_value<liminal_json_io::types::String_t>("hobbies[0]");
    value_eq<liminal_json_io::types::String_t>("reading", "hobbies[0]");
    has_value<liminal_json_io::types::String_t>("hobbies[1]");
    value_eq<liminal_json_io::types::String_t>("gaming", "hobbies[1]");
    has_value<liminal_json_io::types::String_t>("hobbies[2]");
    value_eq<liminal_json_io::types::String_t>("hiking", "hobbies[2]");
    has_value<liminal_json_io::types::Object_t>("hobbies[3]");
    has_value<liminal_json_io::types::String_t>("hobbies[3].nestedHobby");
    value_eq<liminal_json_io::types::String_t>("no", "hobbies[3].nestedHobby");
    has_value<liminal_json_io::types::Object_t>("hobbies[4]");
    has_value<liminal_json_io::types::Array_t>("hobbies[4].secondNestedHobbies");
    has_value<liminal_json_io::types::String_t>("hobbies[4].secondNestedHobbies[0]");
    value_eq<liminal_json_io::types::String_t>("un", "hobbies[4].secondNestedHobbies[0]");
    has_value<liminal_json_io::types::String_t>("hobbies[4].secondNestedHobbies[1]");
    value_eq<liminal_json_io::types::String_t>("dos", "hobbies[4].secondNestedHobbies[1]");
    has_value<liminal_json_io::types::IntNum_t>("hobbies[4].secondNestedHobbies[2]");
    value_eq<liminal_json_io::types::IntNum_t>(3, "hobbies[4].secondNestedHobbies[2]");
    has_value<liminal_json_io::types::Null_t>("hobbies[4].secondNestedHobbies[3]");
    value_eq<liminal_json_io::types::Null_t>(nullptr, "hobbies[4].secondNestedHobbies[3]");
    has_value<liminal_json_io::types::Null_t>("hobbies[4].nothingImportantHere");
    value_eq<liminal_json_io::types::Null_t>(nullptr, "hobbies[4].nothingImportantHere");
    has_value<liminal_json_io::types::String_t>("happy");
    value_eq<liminal_json_io::types::String_t>("yes", "happy");
}

TEST_F(liminal_json_io_InJson, get__RETURN_EMPTY_VALUES_whenGivenWrongTemplateTypeWithSimpleFile) {
    createSimpleFile();
    parse();

    EXPECT_EQ(instance.get<liminal_json_io::types::FloatNum_t>("name").has_value(), false);
}

TEST_F(liminal_json_io_InJson, getType__RETURN_VALID_VALUES__whenGivenSimpleFile) {
    createSimpleFile();
    parse();

    type_eq(liminal_json_io::types::ValueTypes::STRING, "name");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "age");
    type_eq(liminal_json_io::types::ValueTypes::BOOL, "isEmployed");
    type_eq(liminal_json_io::types::ValueTypes::OBJECT, "address");
    type_eq(liminal_json_io::types::ValueTypes::OBJECT, "address.story");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "address.story.left");
    type_eq(liminal_json_io::types::ValueTypes::FLOAT_NUM, "address.story.right");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "address.street");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "address.state");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "address.postalCode");
    type_eq(liminal_json_io::types::ValueTypes::FLOAT_NUM, "address.anotherData");
    type_eq(liminal_json_io::types::ValueTypes::ARRAY, "hobbies");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "hobbies[0]");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "hobbies[1]");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "hobbies[2]");
    type_eq(liminal_json_io::types::ValueTypes::OBJECT, "hobbies[3]");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "hobbies[3].nestedHobby");
    type_eq(liminal_json_io::types::ValueTypes::ARRAY, "hobbies[4].secondNestedHobbies");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "hobbies[4].secondNestedHobbies[0]");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "hobbies[4].secondNestedHobbies[1]");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "hobbies[4].secondNestedHobbies[2]");
    type_eq(liminal_json_io::types::ValueTypes::NULL_VALUE, "hobbies[4].secondNestedHobbies[3]");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "happy");
}


// Context : large json with no errors
TEST_F(liminal_json_io_InJson, parse__RETURN_OK__whenGivenLargeFile) {
    createComplexFile();
    
    EXPECT_EQ(instance.parse(getFilePath()), liminal_json_io::Status::OK);

}

TEST_F(liminal_json_io_InJson, get__RETURN_VALID_VALUES__whenGivenLargeFile) {
    createComplexFile();
    parse();

    has_value<liminal_json_io::types::Array_t>();
    has_value<liminal_json_io::types::String_t>("[0].balance");
    value_eq<liminal_json_io::types::String_t>("$2,399.08", "[0].balance");
    has_value<liminal_json_io::types::String_t>("[1].about");
    value_eq<liminal_json_io::types::String_t>("Minim cupidatat dolor mollit proident enim qui dolore dolor id nisi. Id sunt excepteur nisi officia elit qui aliqua excepteur aliquip fugiat et do Lorem. Qui cupidatat commodo consectetur do laborum elit aute ipsum aliquip. Pariatur dolore commodo enim aute excepteur.\\r\\n", "[1].about");
    has_value<liminal_json_io::types::Object_t>("[13]");
    has_value<liminal_json_io::types::String_t>("[13].registered");
    value_eq<liminal_json_io::types::String_t>("2022-03-08T09:55:37 -01:00", "[13].registered");
    has_value<liminal_json_io::types::Object_t>("[14]");
    has_value<liminal_json_io::types::FloatNum_t>("[14].latitude");
    value_near(-76.371709, "[14].latitude");
    has_value<liminal_json_io::types::Array_t>("[14].friends");
    has_value<liminal_json_io::types::Object_t>("[14].friends[1]");
    has_value<liminal_json_io::types::IntNum_t>("[14].friends[1].id");
    value_eq<liminal_json_io::types::IntNum_t>(1, "[14].friends[1].id");
}

TEST_F(liminal_json_io_InJson, get__RETURN_EMPTY_VALUES_whenGivenWrongTemplateTypeWithLargeFile) {
    createComplexFile();
    parse();

    EXPECT_EQ(instance.get<liminal_json_io::types::IntNum_t>("[14].latitude").has_value(), false);
}


TEST_F(liminal_json_io_InJson, getType__RETURN_VALID_VALUES__whenGivenLargeFile) {
    createComplexFile();
    parse();

    type_eq(liminal_json_io::types::ValueTypes::STRING, "[12].gender");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "[12].phone");
    type_eq(liminal_json_io::types::ValueTypes::FLOAT_NUM, "[12].longitude");
    type_eq(liminal_json_io::types::ValueTypes::INT_NUM, "[12].friends[2].id");
    type_eq(liminal_json_io::types::ValueTypes::STRING, "[12]._id");
    type_eq(liminal_json_io::types::ValueTypes::BOOL, "[11].isActive");
}
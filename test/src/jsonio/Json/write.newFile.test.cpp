/**
 * @file write.newFile.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-09
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
#include <optional>
#include <vector>
#include <sstream>

namespace test {
    namespace jsonio {
        namespace Json {

            using JsonIOJsonWriteMethodNewFileParams = std::tuple<
                ::fs::Path, //input path,
                ::fs::Path // path of the file whose content will be compared to the written file
            >;

            class JsonIOJsonWriteMethodNewFile : public ::testing::TestWithParam<JsonIOJsonWriteMethodNewFileParams> {

                protected:
                    ::jsonio::Json _instanceWithoutPath;
                    ::jsonio::Json _instanceWithPath;
                    ::fs::Path _instanceWithoutPathOutputPath;
                    ::fs::Path _instanceWithPathOutputPath;

                    JsonIOJsonWriteMethodNewFile(void) :
                    _instanceWithoutPath(),
                    _instanceWithPath(),
                    _instanceWithoutPathOutputPath(::test::jsonio::OutJson::Helper::generateTmpOutputPath()),
                    _instanceWithPathOutputPath(::test::jsonio::OutJson::Helper::generateTmpOutputPath())
                    {
                        try { // we copy the output of instanceWithoutPath to avoid modifying the test/assets json file
                            std::filesystem::copy(std::get<0>(GetParam()).asStr(), _instanceWithoutPathOutputPath.asStr());
                        }
                        catch(const std::filesystem::filesystem_error& e) { return; }                            
                        _instanceWithoutPath.parse(_instanceWithoutPathOutputPath);
                        _instanceWithPath.parse(std::get<0>(GetParam()));
                    }

                    ~JsonIOJsonWriteMethodNewFile() {
                        if (std::filesystem::exists(this->_instanceWithoutPathOutputPath.asStr())) {
                            std::filesystem::remove(this->_instanceWithoutPathOutputPath.asStr());
                        }
                        if (std::filesystem::exists(this->_instanceWithPathOutputPath.asStr())) {
                            std::filesystem::remove(this->_instanceWithPathOutputPath.asStr());
                        }
                    }

            };

            TEST_P(JsonIOJsonWriteMethodNewFile, FileContentMatches) {
                if (_instanceWithoutPath.write(true) != ::jsonio::Status::OK) FAIL() << "Failed to write _instanceWithoutPath";
                if (_instanceWithPath.write(this->_instanceWithPathOutputPath) != ::jsonio::Status::OK) FAIL() << "Failed to write _instanceWithPath";
                EXPECT_TRUE(::test::jsonio::OutJson::Helper::filesAreEqual(std::get<1>(GetParam()), _instanceWithoutPathOutputPath));
                EXPECT_TRUE(::test::jsonio::OutJson::Helper::filesAreEqual(std::get<1>(GetParam()), _instanceWithPathOutputPath));
            };

            INSTANTIATE_TEST_SUITE_P(
                whenExpectingStatusOK,
                JsonIOJsonWriteMethodNewFile,
                testing::Values(
                    std::make_tuple(::test::jsonio::Helper::VALID__BASIC_WITHOUT_FLOATING_POINT_NUMBERS, ::test::jsonio::Helper::CORRECTED__BASIC_WITHOUT_FLOATING_POINT_NUMBERS),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, ::test::jsonio::Helper::CORRECTED__EDGE_CASES),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE_WITHOUT_FLOATING_POINT_NUMBERS, ::test::jsonio::Helper::CORRECTED__LARGE_WITHOUT_FLOATING_POINT_NUMBERS),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED_WITHOUT_FLOATING_POINT_NUMBERS, ::test::jsonio::Helper::CORRECTED__NESTED_WITHOUT_FLOATING_POINT_NUMBERS)
                )
            );

            TEST(JsonIOJsonWriteMethodNewFile, FloatingPointNumberFileContentMatches) {
                // 1. Perform json writing
                ::jsonio::Json json;
                if ( json.parse(::test::jsonio::Helper::VALID__FLOATING_POINT_NUMBERS) != ::jsonio::Status::OK) FAIL() << "Failed to parse json";
                ::fs::Path outputPath = ::test::jsonio::OutJson::Helper::generateTmpOutputPath();
                if ( json.write(outputPath) != ::jsonio::Status::OK ) FAIL() << "Failed to write json";
                // 2. Read files content                
                std::ifstream outputFile(outputPath.asStr());
                std::ifstream correctedFile(::test::jsonio::Helper::CORRECTED__FLOATING_POINT_NUMBERS.asStr());
                std::vector<std::string> outputFileContent{};
                std::vector<std::string> correctedFileContent{};
                if ( !outputFile.is_open() ) FAIL() << "Failed to open output file";
                if ( !correctedFile.is_open() ) FAIL() << "Failed to open corrected file";
                std::string buffer("");
                while (std::getline(outputFile, buffer)) outputFileContent.push_back(buffer);
                while (std::getline(correctedFile, buffer)) correctedFileContent.push_back(buffer);
                outputFile.close();
                correctedFile.close();
                if (std::filesystem::exists(outputPath.asStr())) {
                    std::filesystem::remove(outputPath.asStr());
                }

                // 3. Extract the actual floating point number
                std::stringstream outputSS(outputFileContent.at(1));
                std::stringstream correctedSS(correctedFileContent.at(1));
                std::vector<std::string> outputSplittedLine{};
                std::vector<std::string> correctedSplittedLine{};
                while (std::getline(outputSS, buffer, ':')) if ( !buffer.empty() ) outputSplittedLine.push_back(buffer);
                while (std::getline(correctedSS, buffer, ':')) if ( !buffer.empty() ) correctedSplittedLine.push_back(buffer);
                long double outputValue = std::stold(outputSplittedLine.at(1));
                long double correctedValue = std::stold(correctedSplittedLine.at(1));

                // 4. Test long double values equality
                EXPECT_TRUE(outputValue == correctedValue);
            }

        } // namespace Json
    } // namespace jsonio
} // namespace test
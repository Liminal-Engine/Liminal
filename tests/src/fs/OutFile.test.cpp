/**
 * @file OutFile.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-09
 * 
 * @copyright Copyright (c) 2024
 * 
*/


#include <fs/OutFile.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <tuple>
#include <string>
#include <unistd.h>
#include <iostream>

// We also tests the commond methods : because of the implementation with a different streeam type, their behaivior could change

using FSOutFileOpenParam = std::tuple<
    fs::Path, // path
    fs::Status //expected status
>;
class FSOutFileOpenMethod : public ::testing::TestWithParam<FSOutFileOpenParam> {
    protected:
        fs::OutFile _instance;

        FSOutFileOpenMethod(void):
        _instance{fs::OutFile{std::get<0>(GetParam())}}
        {}
};

TEST_P(FSOutFileOpenMethod, ReturnGivenStatus) {
    EXPECT_EQ(_instance.open(), std::get<1>(GetParam()));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenValidFilePaths,
    FSOutFileOpenMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, fs::Status::NOK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/incomplete.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingClosing.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingOpening.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingClosing.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpening.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missing.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooMany.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/wrongChar.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/misplaced.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInArray.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNumArray.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/tooMuch.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/valid/basic.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/valid/edgeCases.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/valid/large.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/json/valid/nested.json"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, fs::Status::OK),
        // std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/|||empty|||"}, fs::Status::OK)
    )
);

// INSTANTIATE_TEST_SUITE_P(
//     WhenGivenPathWithNoRealTarget,
//     FSOutFileOpenMethod,
//     testing::Values(
//         std::make_tuple(fs::Path{"../../tests/../../do/not/exists////---/"}, fs::Status::E_PATH_NO_TARGET),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.jso"}, fs::Status::E_PATH_NO_TARGET),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, fs::Status::E_PATH_NO_TARGET),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*("}, fs::Status::E_PATH_NO_TARGET),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.hidde"}, fs::Status::E_PATH_NO_TARGET),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.h"}, fs::Status::E_PATH_NO_TARGET),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/________._"}, fs::Status::E_PATH_NO_TARGET),
//         std::make_tuple(fs::Path{"/abc/def/IDoNotExists/"}, fs::Status::E_PATH_NO_TARGET)
//     )
// );

// INSTANTIATE_TEST_SUITE_P(
//     WhenGivenPathOfDirectory,
//     FSOutFileOpenMethod,
//     testing::Values(
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array"}, fs::Status::E_PATH_IS_DIR),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/"}, fs::Status::E_PATH_IS_DIR),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool"}, fs::Status::E_PATH_IS_DIR),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/"}, fs::Status::E_PATH_IS_DIR),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace"}, fs::Status::E_PATH_IS_DIR),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/"}, fs::Status::E_PATH_IS_DIR),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket"}, fs::Status::E_PATH_IS_DIR),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/"}, fs::Status::E_PATH_IS_DIR),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon"}, fs::Status::E_PATH_IS_DIR),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/"}, fs::Status::E_PATH_IS_DIR),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid"}, fs::Status::E_PATH_IS_DIR),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/"}, fs::Status::E_PATH_IS_DIR),
//         std::make_tuple(fs::Path{"/"}, fs::Status::E_PATH_IS_DIR)
//     )
// );


// using FSOutFileCloseParam = std::tuple<
//     fs::Path, // path
//     fs::Status //expected status
// >;
// class FSOutFileCloseMethod : public ::testing::TestWithParam<FSOutFileCloseParam> {
//     protected:
//         fs::OutFile _instance;

//         FSOutFileCloseMethod(void):
//         _instance{fs::OutFile{std::get<0>(GetParam())}}
//         {}
// };

// TEST_P(FSOutFileCloseMethod, ReturnGivenStatus) {
//     _instance.open();
//     EXPECT_EQ(_instance.close(), std::get<1>(GetParam()));
// };

// INSTANTIATE_TEST_SUITE_P(
//     WhenGivenPathOfFileThatShouldBeOpened,
//     FSOutFileCloseMethod,
//     testing::Values(
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/incomplete.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingClosing.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingOpening.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingClosing.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpening.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missing.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooMany.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/wrongChar.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/misplaced.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInArray.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNumArray.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/tooMuch.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid/basic.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid/edgeCases.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid/large.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid/nested.json"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, fs::Status::OK),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/|||empty|||"}, fs::Status::OK)
//     )
// );

// INSTANTIATE_TEST_SUITE_P(
//     WhenGivenPathOfFileThatShouldNotBeOpened,
//     FSOutFileCloseMethod,
//     testing::Values(
//         std::make_tuple(fs::Path{"../../tests/../../do/not/exists////---/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.jso"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*("}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.hidde"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.h"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/________._"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"/abc/def/IDoNotExists/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
//         std::make_tuple(fs::Path{"/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN)
//     )
// );

// using FSOutFileGetExtensionParam = std::tuple<
//     fs::Path, // path
//     std::optional<std::string> //expected value
// >;
// class FSOutFileGetExtensionMethod : public ::testing::TestWithParam<FSOutFileGetExtensionParam> {
//     protected:
//         fs::OutFile _instance;

//         FSOutFileGetExtensionMethod(void):
//         _instance{fs::OutFile{std::get<0>(GetParam())}}
//         {}
// };

// TEST_P(FSOutFileGetExtensionMethod, ReturnGivenValue) {
//     _instance.open();
//     EXPECT_EQ(_instance.getExtension(), std::get<1>(GetParam()));
// };

// INSTANTIATE_TEST_SUITE_P(
//     WhenGivenPathWithExtension,
//     FSOutFileGetExtensionMethod,
//     testing::Values(
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, std::optional<std::string>{"json"}),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, std::optional<std::string>{"json"}),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, std::optional<std::string>{" *"}),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, std::optional<std::string>{"__"}),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/________._"}, std::optional<std::string>{"_"}),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, std::optional<std::string>{"!@#$%^&*()"}),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*().@#$%^&*()"}, std::optional<std::string>{"!@#$%^&*().@#$%^&*()"}),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, std::optional<std::string>{"hidden"}),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.123.456"}, std::optional<std::string>{"123.456"}),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/file.txt.json"}, std::optional<std::string>{"txt.json"}),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/file. txt"}, std::optional<std::string>{" txt"}),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/file.@#$.txt"}, std::optional<std::string>{"@#$.txt"}),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/file."}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/file.TXT"}, std::optional<std::string>{"TXT"}),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/file.TxT"}, std::optional<std::string>{"TxT"})
//     )
// );

// INSTANTIATE_TEST_SUITE_P(
//     WhenGivenPathWithOutExtension,
//     FSOutFileGetExtensionMethod,
//     testing::Values(
//         std::make_tuple(fs::Path{"../../tests/assets/fs/file."}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/../../do/not/exists////---/"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject    .   "}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/________."}, std::nullopt),
//         std::make_tuple(fs::Path{"/abc/def/IDoNotExists/"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid"}, std::nullopt),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/"}, std::nullopt),
//         std::make_tuple(fs::Path{"/"}, std::nullopt)
//     )
// );

// using FSOutFileIsOpenParam = std::tuple<
//     fs::Path, // path
//     bool, // whether to call the "close" method
//     bool //expected result
// >;
// class FSOutFileIsOpenMethod : public ::testing::TestWithParam<FSOutFileIsOpenParam> {
//     protected:
//         fs::OutFile _instance;

//         FSOutFileIsOpenMethod(void):
//         _instance{fs::OutFile{std::get<0>(GetParam())}}
//         {}
// };

// TEST_P(FSOutFileIsOpenMethod, ReturnGivenValue) {
//     _instance.open();
//     if ( std::get<1>(GetParam()) ) _instance.close();
//     EXPECT_EQ(_instance.isOpen(), std::get<2>(GetParam()));
// }

// INSTANTIATE_TEST_SUITE_P(
//     WhenGivenOpenablePaths,
//     FSOutFileIsOpenMethod,
//     testing::Values(
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/incomplete.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/incomplete.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingClosing.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingClosing.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingOpening.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingOpening.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingClosing.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingClosing.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpening.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpening.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missing.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missing.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooMany.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooMany.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/wrongChar.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/wrongChar.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/misplaced.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/misplaced.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInArray.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInArray.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNumArray.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNumArray.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/tooMuch.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/tooMuch.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid/basic.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid/basic.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid/edgeCases.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid/edgeCases.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid/large.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid/large.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid/nested.json"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid/nested.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/|||empty|||"},false, true),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/|||empty|||"},true, false)
//     )
// );


// INSTANTIATE_TEST_SUITE_P(
//     WhenGivenUnopenablePaths,
//     FSOutFileIsOpenMethod,
//     testing::Values(
//         std::make_tuple(fs::Path{"../../tests/../../do/not/exists////---/"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/../../do/not/exists////---/"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.jso"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.jso"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*("}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*("}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.hidde"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.hidde"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.h"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/.h"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/________._"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/________._"}, false, false),
//         std::make_tuple(fs::Path{"/abc/def/IDoNotExists/"}, true, false),
//         std::make_tuple(fs::Path{"/abc/def/IDoNotExists/"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/json/valid"}, false, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/"}, true, false),
//         std::make_tuple(fs::Path{"../../tests/assets/fs/"}, false, false),
//         std::make_tuple(fs::Path{"/"}, true, false),
//         std::make_tuple(fs::Path{"/"}, false, false)
//     )
// );

// using FSOutFileClearParam = std::tuple<
//     fs::Path, // path
//     bool, // whether to call the "close" method
//     bool //expected result
// >;
// class FSOutFileClearMethod : public ::testing::TestWithParam<FSOutFileClearParam> {
//     protected:
//         fs::OutFile _instance;

//         FSOutFileClearMethod(void):
//         _instance{fs::OutFile{std::get<0>(GetParam())}}
//         {}
// };

// TEST_P(FSOutFileClearMethod, ReturnGivenValue) {
//     _instance.open();
//     if ( std::get<1>(_instance.clear()) ) _instance.close();
//     EXPECT_EQ(_instance.Clear(), std::get<2>(GetParam()));
// }


// TODO : tester :
/**
 * 1. create : ajotuer param pour crééer path si existe pas ?
 * 2. clear
 * 3. write : est-ce que le contenu est écrit "en direct" ou est-ce qu'il faut "flush" ou fermer le fichier ?
 * 
 * 
 * 
*/


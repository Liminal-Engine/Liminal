/**
 * @file InFile.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <fs/InFile.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <tuple>
#include <string>
#include <unistd.h>
#include <iostream>

/**
 * TODO : test all methods, even common methods because behavior could change
 * 
*/

using FSInFileOpenParam = std::tuple<
    fs::Path, // path
    fs::Status //expected status
>;
class FSInFileOpenMethod : public ::testing::TestWithParam<FSInFileOpenParam> {
    protected:
        fs::InFile _instance;

        FSInFileOpenMethod(void):
        _instance{fs::InFile{std::get<0>(GetParam())}}
        {}
};

TEST_P(FSInFileOpenMethod, ReturnGivenStatus) {
    EXPECT_EQ(_instance.open(), std::get<1>(GetParam()));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenValidFilePaths,
    FSInFileOpenMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/incomplete.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingClosing.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingOpening.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingClosing.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpening.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missing.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooMany.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/wrongChar.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/misplaced.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInArray.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNumArray.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/tooMuch.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/basic.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/edgeCases.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/large.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/nested.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/|||empty|||"}, fs::Status::OK)
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathWithNoRealTarget,
    FSInFileOpenMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/../../do/not/exists////---/"}, fs::Status::E_PATH_NO_TARGET),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.jso"}, fs::Status::E_PATH_NO_TARGET),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, fs::Status::E_PATH_NO_TARGET),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*("}, fs::Status::E_PATH_NO_TARGET),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidde"}, fs::Status::E_PATH_NO_TARGET),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.h"}, fs::Status::E_PATH_NO_TARGET),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________._"}, fs::Status::E_PATH_NO_TARGET),
        std::make_tuple(fs::Path{"/abc/def/IDoNotExists/"}, fs::Status::E_PATH_NO_TARGET)
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathOfDirectory,
    FSInFileOpenMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array"}, fs::Status::E_PATH_IS_DIR),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/"}, fs::Status::E_PATH_IS_DIR),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool"}, fs::Status::E_PATH_IS_DIR),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/"}, fs::Status::E_PATH_IS_DIR),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace"}, fs::Status::E_PATH_IS_DIR),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/"}, fs::Status::E_PATH_IS_DIR),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket"}, fs::Status::E_PATH_IS_DIR),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/"}, fs::Status::E_PATH_IS_DIR),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon"}, fs::Status::E_PATH_IS_DIR),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/"}, fs::Status::E_PATH_IS_DIR),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid"}, fs::Status::E_PATH_IS_DIR),
        std::make_tuple(fs::Path{"../../tests/assets/fs/"}, fs::Status::E_PATH_IS_DIR),
        std::make_tuple(fs::Path{"/"}, fs::Status::E_PATH_IS_DIR)
    )
);


using FSInFileCloseParam = std::tuple<
    fs::Path, // path
    fs::Status //expected status
>;
class FSInFileCloseMethod : public ::testing::TestWithParam<FSInFileCloseParam> {
    protected:
        fs::InFile _instance;

        FSInFileCloseMethod(void):
        _instance{fs::InFile{std::get<0>(GetParam())}}
        {}
};

TEST_P(FSInFileCloseMethod, ReturnGivenStatus) {
    _instance.open();
    EXPECT_EQ(_instance.close(), std::get<1>(GetParam()));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathOfFileThatShouldBeOpened,
    FSInFileCloseMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/incomplete.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingClosing.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingOpening.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingClosing.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpening.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missing.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooMany.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/wrongChar.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/misplaced.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInArray.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNumArray.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/tooMuch.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/basic.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/edgeCases.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/large.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/nested.json"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/|||empty|||"}, fs::Status::OK)
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathOfFileThatShouldNotBeOpened,
    FSInFileCloseMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/../../do/not/exists////---/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.jso"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*("}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidde"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.h"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________._"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"/abc/def/IDoNotExists/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"../../tests/assets/fs/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN),
        std::make_tuple(fs::Path{"/"}, fs::Status::E_CLOSE_FILE_NOT_OPEN)
    )
);

using FSInFileGetExtensionParam = std::tuple<
    fs::Path, // path
    std::optional<std::string> //expected value
>;
class FSInFileGetExtensionMethod : public ::testing::TestWithParam<FSInFileGetExtensionParam> {
    protected:
        fs::InFile _instance;

        FSInFileGetExtensionMethod(void):
        _instance{fs::InFile{std::get<0>(GetParam())}}
        {}
};

TEST_P(FSInFileGetExtensionMethod, ReturnGivenValue) {
    _instance.open();
    EXPECT_EQ(_instance.getExtension(), std::get<1>(GetParam()));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathWithExtension,
    FSInFileGetExtensionMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, std::optional<std::string>{"json"}),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, std::optional<std::string>{"json"}),
        std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, std::optional<std::string>{" *"}),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, std::optional<std::string>{"__"}),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________._"}, std::optional<std::string>{"_"}),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, std::optional<std::string>{"!@#$%^&*()"}),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*().@#$%^&*()"}, std::optional<std::string>{"!@#$%^&*().@#$%^&*()"}),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, std::optional<std::string>{"hidden"}),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.123.456"}, std::optional<std::string>{"123.456"}),
        std::make_tuple(fs::Path{"../../tests/assets/fs/file.txt.json"}, std::optional<std::string>{"txt.json"}),
        std::make_tuple(fs::Path{"../../tests/assets/fs/file. txt"}, std::optional<std::string>{" txt"}),
        std::make_tuple(fs::Path{"../../tests/assets/fs/file.@#$.txt"}, std::optional<std::string>{"@#$.txt"}),
        std::make_tuple(fs::Path{"../../tests/assets/fs/file."}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/fs/file.TXT"}, std::optional<std::string>{"TXT"}),
        std::make_tuple(fs::Path{"../../tests/assets/fs/file.TxT"}, std::optional<std::string>{"TxT"})
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenPathWithOutExtension,
    FSInFileGetExtensionMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/assets/fs/file."}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/../../do/not/exists////---/"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject    .   "}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________."}, std::nullopt),
        std::make_tuple(fs::Path{"/abc/def/IDoNotExists/"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid"}, std::nullopt),
        std::make_tuple(fs::Path{"../../tests/assets/fs/"}, std::nullopt),
        std::make_tuple(fs::Path{"/"}, std::nullopt)
    )
);

using FSInFileIsOpenParam = std::tuple<
    fs::Path, // path
    bool, // whether to call the "close" method
    bool //expected result
>;
class FSInFileIsOpenMethod : public ::testing::TestWithParam<FSInFileIsOpenParam> {
    protected:
        fs::InFile _instance;

        FSInFileIsOpenMethod(void):
        _instance{fs::InFile{std::get<0>(GetParam())}}
        {}
};

TEST_P(FSInFileIsOpenMethod, ReturnGivenValue) {
    _instance.open();
    if ( std::get<1>(GetParam()) ) _instance.close();
    EXPECT_EQ(_instance.isOpen(), std::get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenOpenablePaths,
    FSInFileIsOpenMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/incomplete.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/incomplete.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingClosing.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingClosing.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingOpening.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingOpening.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingClosing.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingClosing.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpening.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpening.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missing.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missing.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooMany.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooMany.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/wrongChar.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/wrongChar.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/misplaced.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/misplaced.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInArray.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInArray.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNumArray.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNumArray.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/tooMuch.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/tooMuch.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/basic.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/basic.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/edgeCases.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/edgeCases.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/large.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/large.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/nested.json"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/nested.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, false, true),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/|||empty|||"},false, true),
        std::make_tuple(fs::Path{"../../tests/assets/fs/|||empty|||"},true, false)
    )
);


INSTANTIATE_TEST_SUITE_P(
    WhenGivenUnopenablePaths,
    FSInFileIsOpenMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/../../do/not/exists////---/"}, true, false),
        std::make_tuple(fs::Path{"../../tests/../../do/not/exists////---/"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.jso"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.jso"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*("}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*("}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidde"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidde"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.h"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.h"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________._"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________._"}, false, false),
        std::make_tuple(fs::Path{"/abc/def/IDoNotExists/"}, true, false),
        std::make_tuple(fs::Path{"/abc/def/IDoNotExists/"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid"}, false, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/"}, true, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/"}, false, false),
        std::make_tuple(fs::Path{"/"}, true, false),
        std::make_tuple(fs::Path{"/"}, false, false)
    )
);

using FSInFileReadParam = std::tuple<
    fs::Path, // path
    bool, // whether to call the "open" method
    fs::Status // 
>;
class FSInFileReadMethod : public ::testing::TestWithParam<FSInFileReadParam> {
    protected:
        fs::InFile _instance;

        FSInFileReadMethod(void):
        _instance{fs::InFile{std::get<0>(GetParam())}}
        {}
};

TEST_P(FSInFileReadMethod, ReturnGivenValue) {
    if ( std::get<1>(GetParam()) ) _instance.open();
    EXPECT_EQ(_instance.read(), std::get<2>(GetParam()));
}


INSTANTIATE_TEST_SUITE_P(
    WhenGivenOpenablePaths,
    FSInFileReadMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/incomplete.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/incomplete.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingClosing.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingClosing.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingOpening.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingOpening.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingClosing.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingClosing.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpening.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpening.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missing.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missing.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooMany.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooMany.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/wrongChar.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/wrongChar.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/misplaced.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/misplaced.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInArray.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInArray.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNumArray.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNumArray.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/tooMuch.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/tooMuch.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/basic.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/basic.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/edgeCases.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/edgeCases.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/large.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/large.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/nested.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/nested.json"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, true, fs::Status::OK),
        std::make_tuple(fs::Path{"../../tests/assets/fs/|||empty|||"},false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/|||empty|||"},true, fs::Status::OK)
    )
);

INSTANTIATE_TEST_SUITE_P(
    WhenGivenUnopenablePaths,
    FSInFileReadMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/../../do/not/exists////---/"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/../../do/not/exists////---/"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.jso"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.jso"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*("}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*("}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidde"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidde"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.h"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.h"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________._"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________._"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"/abc/def/IDoNotExists/"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"/abc/def/IDoNotExists/"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"../../tests/assets/fs/"}, false, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"/"}, true, fs::Status::E_READ_FILE_NOT_OPENED),
        std::make_tuple(fs::Path{"/"}, false, fs::Status::E_READ_FILE_NOT_OPENED)
    )
);

using FSInFileGetContentParam = std::tuple<
    fs::Path, // path
    bool // whether to call the "read" method
>;
class FSInFileGetContentMethod : public ::testing::TestWithParam<FSInFileGetContentParam> {
    protected:
        fs::InFile _instance;

        FSInFileGetContentMethod(void):
        _instance{fs::InFile{std::get<0>(GetParam())}}
        {}
};

TEST_P(FSInFileGetContentMethod, ReturnGivenValue) {
    _instance.open();
    if ( std::get<1>(GetParam()) ) {
        _instance.read();
        std::ifstream file(std::get<0>(GetParam()).toStr());
        std::string cppStyledContent((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
        EXPECT_EQ(_instance.get_content(), cppStyledContent);
    } else {
        EXPECT_EQ(_instance.get_content(), std::string{});
    }
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenOpenablePaths,
    FSInFileGetContentMethod,
    testing::Values(
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/array/wrongFormat.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/incomplete.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bool/incomplete.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingClosing.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingClosing.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingOpening.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/brace/missingOpening.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingClosing.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingClosing.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpening.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpening.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missing.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/missing.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooMany.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooMany.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/wrongChar.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/colon/wrongChar.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/misplaced.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/misplaced.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missing.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInArray.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInArray.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNumArray.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/missingInNumArray.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/tooMuch.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/invalid/comma/tooMuch.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/basic.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/basic.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/edgeCases.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/edgeCases.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/large.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/large.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/nested.json"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/json/valid/nested.json"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/fs/_ _ _ _. *"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/fs/________.__"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/fs/!@#$%^&*().!@#$%^&*()"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/fs/.hidden"}, false),
        std::make_tuple(fs::Path{"../../tests/assets/fs/|||empty|||"}, true),
        std::make_tuple(fs::Path{"../../tests/assets/fs/|||empty|||"}, false)
    )
);
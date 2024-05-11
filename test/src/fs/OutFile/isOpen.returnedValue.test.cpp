/**
 * @file close.returnedStatus.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-08
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

#include <unistd.h>

// TODO : test files with wrong permissions

namespace test {
    namespace fs {
        namespace OutFile {
            using FSOutFileIsOpenParam = std::tuple<
                ::fs::Path, // path
                bool, // whether to previously open the file
                bool //expected result
            >;
            class FSOutFileIsOpenMethod : public ::testing::TestWithParam<FSOutFileIsOpenParam> {
                protected:
                    ::fs::OutFile _instance;

                    FSOutFileIsOpenMethod(void):
                    _instance(::fs::OutFile{std::get<0>(GetParam())})
                    {
                        if (std::get<1>(GetParam())) _instance.open();
                    }

                    ~FSOutFileIsOpenMethod() {
                        _instance.close();
                    }


            };

            TEST_P(FSOutFileIsOpenMethod, ReturnGivenStatus) {
                bool expectedResult = std::get<2>(GetParam());

                EXPECT_EQ(_instance.isOpen(), expectedResult);
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenVariousPath,
                FSOutFileIsOpenMethod,
                testing::Values(
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/array/wrongFormat.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/array/wrongFormat.json"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bool/incomplete.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/brace/missingClosing.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/brace/missingOpening.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bracket/missingClosing.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bracket/missingOpening.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/missing.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/tooMany.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/wrongChar.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/misplaced.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/missing.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/missing.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/missingInArray.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/missingInNestedArray.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/missingInNumArray.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/multipleMissingInArray.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/tooMuch.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/valid/basic.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/valid/edgeCases.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/valid/large.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/json/valid/nested.json"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/_ _ _ _. *"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/_ _ _ _. *"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/________.__"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/!@#$%^&*().!@#$%^&*()"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/!@#$%^&*().!@#$%^&*()"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.hidden"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.hidden"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/|||empty|||"}, true, true),
                    std::make_tuple(::fs::Path{"../../test/../../do/not/exists////---/"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/array/wrongFormat.jso"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/!@#$%^&*().!@#$%^&*("}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.hidde"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.h"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/________._"}, false, false),
                    std::make_tuple(::fs::Path{"/abc/def/IDoNotExists/"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/array"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/array/"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bool"}, true, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bool/"}, true, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/brace"}, true, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/brace/"}, true, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bracket"}, true, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bracket/"}, true, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/json/valid"}, false, false),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/"}, false, false),
                    std::make_tuple(::fs::Path{"/"}, false, false),
                    std::make_tuple(::fs::Path{"/"}, true, false)
                )
            );
            
        } // namespace OutFile
    } // namespace fs
} // namespace test

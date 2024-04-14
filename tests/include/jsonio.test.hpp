/**
 * @file jsonio.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-04
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_TESTS_jsonio_TEST_HPP_
#define LIMINAL_TESTS_jsonio_TEST_HPP_

#include "fs/Path.hpp"

#include <string>
#include <filesystem>

namespace jsonio_test {
    namespace paths {

        const fs::Path VALID__BASIC{"../../tests/assets/json/valid/basic.json"};
        const fs::Path VALID__EDGE_CASES{"../../tests/assets/json/valid/edgeCases.json"};
        const fs::Path VALID__NESTED {"../../tests/assets/json/valid/nested.json"};
        const fs::Path VALID__LARGE{"../../tests/assets/json/valid/large.json"};

        const fs::Path INVALID__ARRAY__WRONG_FORMAT{"../../tests/assets/json/invalid/array/wrongFormat.json"};
        
        const fs::Path INVALID__BOOL__INCOMPLETE{"../../tests/assets/json/invalid/bool/incomplete.json"};

        const fs::Path INVALID__BRACE__MISSING_CLOSING{"../../tests/assets/json/invalid/brace/missingClosing.json"};
        const fs::Path INVALID__BRACE__MISSING_OPENING{"../../tests/assets/json/invalid/brace/missingOpening.json"};
        
        const fs::Path INVALID__BRACKET__MISING_CLOSING{"../../tests/assets/json/invalid/bracket/missingClosing.json"};
        const fs::Path INVALID__BRACKET__MISING_OPENING{"../../tests/assets/json/invalid/bracket/missingOpening.json"};
        const fs::Path INVALID__BRACKET__MISING_OPENING_AT_ROOT{"../../tests/assets/json/invalid/bracket/missingOpeningAtRoot.json"};

        const fs::Path INVALID_COLON__MISSING{"../../tests/assets/json/invalid/colon/missing.json"};
        const fs::Path INVALID_COLON__TOO_MANY{"../../tests/assets/json/invalid/colon/tooMany.json"};
        const fs::Path INVALID_COLON__TOO_MANY_IN_SIMPLE_KEY_VALUE_PAIR{"../../tests/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"};
        const fs::Path INVALID_COLON__WRONG_CHAR{"../../tests/assets/json/invalid/colon/wrongChar.json"};

        const fs::Path INVALID__COMMA__MISPLACED{"../../tests/assets/json/invalid/comma/misplaced.json"};
        const fs::Path INVALID__COMMA__MISSING{"../../tests/assets/json/invalid/comma/missing.json"};
        const fs::Path INVALID__COMMA__MISSING_IN_ARRAY{"../../tests/assets/json/invalid/comma/missingInArray.json"};
        const fs::Path INVALID__COMMA__MISSING_IN_NESTED_ARRAY{"../../tests/assets/json/invalid/comma/missingInNestedArray.json"};
        const fs::Path INVALID__COMMA__MISSING_IN_NUM_ARRAY{"../../tests/assets/json/invalid/comma/missingInNumArray.json"};
        const fs::Path INVALID__COMMA__MULTIPLE_MISSING_IN_ARRAY{"../../tests/assets/json/invalid/comma/multipleMissingInArray.json"};
        const fs::Path INVALID__COMMA__TOO_MUCH{"../../tests/assets/json/invalid/comma/tooMuch.json"};

        const fs::Path INEXISTANT_PATH{"~~~~/**//---IDo|||NotExists&&.json"};
        const fs::Path MISSING_LETTER_IN_FILE_EXT{"../../tests/assets/json/basicNoError.jso"};

    } // namespace jons_file_paths

    namespace json_path {
        const std::string INEXISTANT_PATH = "~~~~~thisPath/Sure----lyDontExists.unkownFileExt123456789";
    }
} // namespace jsonio_test


#endif // LIMINAL_TESTS_jsonio_HPP_
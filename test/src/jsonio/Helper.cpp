/**
 * @file Helper.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-09
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "test/jsonio/Helper.hpp"

namespace test {
    namespace jsonio {
            const fs::Path Helper::VALID__BASIC{"../../test/assets/json/valid/basic.json"};
            const fs::Path Helper::VALID__EDGE_CASES{"../../test/assets/json/valid/edgeCases.json"};
            const fs::Path Helper::VALID__NESTED {"../../test/assets/json/valid/nested.json"};
            const fs::Path Helper::VALID__LARGE{"../../test/assets/json/valid/large.json"};

            const fs::Path Helper::INVALID__ARRAY__WRONG_FORMAT{"../../test/assets/json/invalid/array/wrongFormat.json"};

            const fs::Path Helper::INVALID__BOOL__INCOMPLETE{"../../test/assets/json/invalid/bool/incomplete.json"};

            const fs::Path Helper::INVALID__BRACE__MISSING_CLOSING{"../../test/assets/json/invalid/brace/missingClosing.json"};
            const fs::Path Helper::INVALID__BRACE__MISSING_OPENING{"../../test/assets/json/invalid/brace/missingOpening.json"};

            const fs::Path Helper::INVALID__BRACKET__MISING_CLOSING{"../../test/assets/json/invalid/bracket/missingClosing.json"};
            const fs::Path Helper::INVALID__BRACKET__MISING_OPENING{"../../test/assets/json/invalid/bracket/missingOpening.json"};
            const fs::Path Helper::INVALID__BRACKET__MISING_OPENING_AT_ROOT{"../../test/assets/json/invalid/bracket/missingOpeningAtRoot.json"};

            const fs::Path Helper::INVALID_COLON__MISSING{"../../test/assets/json/invalid/colon/missing.json"};
            const fs::Path Helper::INVALID_COLON__TOO_MANY{"../../test/assets/json/invalid/colon/tooMany.json"};
            const fs::Path Helper::INVALID_COLON__TOO_MANY_IN_SIMPLE_KEY_VALUE_PAIR{"../../test/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"};
            const fs::Path Helper::INVALID_COLON__WRONG_CHAR{"../../test/assets/json/invalid/colon/wrongChar.json"};

            const fs::Path Helper::INVALID__COMMA__MISPLACED{"../../test/assets/json/invalid/comma/misplaced.json"};
            const fs::Path Helper::INVALID__COMMA__MISSING{"../../test/assets/json/invalid/comma/missing.json"};
            const fs::Path Helper::INVALID__COMMA__MISSING_IN_ARRAY{"../../test/assets/json/invalid/comma/missingInArray.json"};
            const fs::Path Helper::INVALID__COMMA__MISSING_IN_NESTED_ARRAY{"../../test/assets/json/invalid/comma/missingInNestedArray.json"};
            const fs::Path Helper::INVALID__COMMA__MISSING_IN_NUM_ARRAY{"../../test/assets/json/invalid/comma/missingInNumArray.json"};
            const fs::Path Helper::INVALID__COMMA__MULTIPLE_MISSING_IN_ARRAY{"../../test/assets/json/invalid/comma/multipleMissingInArray.json"};
            const fs::Path Helper::INVALID__COMMA__TOO_MUCH{"../../test/assets/json/invalid/comma/tooMuch.json"};

            const fs::Path Helper::INEXISTANT_PATH{"~~~~/**//---IDo|||NotExists&&.json"};
            const fs::Path Helper::MISSING_LETTER_IN_FILE_EXT{"../../test/assets/json/basicNoError.jso"};
    } // namespace jsonio
} // namespace test

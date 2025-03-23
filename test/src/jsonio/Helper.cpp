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

            const fs::Path Helper::JSONIO__ASSETS__DIR("../../test/assets/");

            const fs::Path Helper::VALID__BASIC{"../../test/assets/jsonio/valid/basic.json"};
            const fs::Path Helper::VALID__EDGE_CASES{"../../test/assets/jsonio/valid/edgeCases.json"};
            const fs::Path Helper::VALID__NESTED {"../../test/assets/jsonio/valid/nested.json"};
            const fs::Path Helper::VALID__LARGE{"../../test/assets/jsonio/valid/large.json"};
            const fs::Path Helper::VALID__LARGE_WITHOUT_FLOATING_POINT_NUMBERS{"../../test/assets/jsonio/valid/largeWithoutFloatingPointNumbers.json"};
            const fs::Path Helper::VALID__FLOATING_POINT_NUMBERS{"../../test/assets/jsonio/valid/floatingPointNumber.json"};
            const fs::Path Helper::VALID__BASIC_WITHOUT_FLOATING_POINT_NUMBERS{"../../test/assets/jsonio/valid/basicWithoutFloatingPointNumbers.json"};
            const fs::Path Helper::VALID__NESTED_WITHOUT_FLOATING_POINT_NUMBERS{"../../test/assets/jsonio/valid/nestedWithoutFloatingPointNumbers.json"};
            const fs::Path Helper::VALID__EMPTY{"../../test/assets/jsonio/valid/empty.json"};

            const fs::Path Helper::INVALID__ARRAY__WRONG_FORMAT{"../../test/assets/jsonio/invalid/array/wrongFormat.json"};

            const fs::Path Helper::INVALID__BOOL__INCOMPLETE{"../../test/assets/jsonio/invalid/bool/incomplete.json"};

            const fs::Path Helper::INVALID__BRACE__MISSING_CLOSING{"../../test/assets/jsonio/invalid/brace/missingClosing.json"};
            const fs::Path Helper::INVALID__BRACE__MISSING_OPENING{"../../test/assets/jsonio/invalid/brace/missingOpening.json"};

            const fs::Path Helper::INVALID__BRACKET__MISING_CLOSING{"../../test/assets/jsonio/invalid/bracket/missingClosing.json"};
            const fs::Path Helper::INVALID__BRACKET__MISING_OPENING{"../../test/assets/jsonio/invalid/bracket/missingOpening.json"};
            const fs::Path Helper::INVALID__BRACKET__MISING_OPENING_AT_ROOT{"../../test/assets/jsonio/invalid/bracket/missingOpeningAtRoot.json"};

            const fs::Path Helper::INVALID_COLON__MISSING{"../../test/assets/jsonio/invalid/colon/missing.json"};
            const fs::Path Helper::INVALID_COLON__TOO_MANY{"../../test/assets/jsonio/invalid/colon/tooMany.json"};
            const fs::Path Helper::INVALID_COLON__TOO_MANY_IN_SIMPLE_KEY_VALUE_PAIR{"../../test/assets/jsonio/invalid/colon/tooManyInSimpleKeyValuePair.json"};
            const fs::Path Helper::INVALID_COLON__WRONG_CHAR{"../../test/assets/jsonio/invalid/colon/wrongChar.json"};

            const fs::Path Helper::INVALID__COMMA__MISPLACED{"../../test/assets/jsonio/invalid/comma/misplaced.json"};
            const fs::Path Helper::INVALID__COMMA__MISSING{"../../test/assets/jsonio/invalid/comma/missing.json"};
            const fs::Path Helper::INVALID__COMMA__MISSING_IN_ARRAY{"../../test/assets/jsonio/invalid/comma/missingInArray.json"};
            const fs::Path Helper::INVALID__COMMA__MISSING_IN_NESTED_ARRAY{"../../test/assets/jsonio/invalid/comma/missingInNestedArray.json"};
            const fs::Path Helper::INVALID__COMMA__MISSING_IN_NUM_ARRAY{"../../test/assets/jsonio/invalid/comma/missingInNumArray.json"};
            const fs::Path Helper::INVALID__COMMA__MULTIPLE_MISSING_IN_ARRAY{"../../test/assets/jsonio/invalid/comma/multipleMissingInArray.json"};
            const fs::Path Helper::INVALID__COMMA__TOO_MUCH{"../../test/assets/jsonio/invalid/comma/tooMuch.json"};
            
            const fs::Path Helper::INVALID__EMPTY{"../../test/assets/jsonio/invalid/empty.json"};

            const fs::Path Helper::INEXISTANT_PATH{"~~~~/**//---IDo|||NotExists&&.json"};
            const fs::Path Helper::MISSING_LETTER_IN_FILE_EXT{"../../test/assets/jsonio/basicNoError.jso"};
            
            const fs::Path Helper::CORRECTED__BASIC{"../../test/assets/jsonio/corrected/basic.json"};
            const fs::Path Helper::CORRECTED__EDGE_CASES{"../../test/assets/jsonio/corrected/edgeCases.json"};
            const fs::Path Helper::CORRECTED__LARGE{"../../test/assets/jsonio/corrected/large.json"};
            const fs::Path Helper::CORRECTED__LARGE_WITHOUT_FLOATING_POINT_NUMBERS{"../../test/assets/jsonio/corrected/largeWithoutFloatingPointNumbers.json"};
            const fs::Path Helper::CORRECTED__FLOATING_POINT_NUMBERS{"../../test/assets/jsonio/corrected/floatingPointNumber.json"};
            const fs::Path Helper::CORRECTED__BASIC_WITHOUT_FLOATING_POINT_NUMBERS{"../../test/assets/jsonio/corrected/basicWithoutFloatingPointNumbers.json"};
            const fs::Path Helper::CORRECTED__NESTED_WITHOUT_FLOATING_POINT_NUMBERS{"../../test/assets/jsonio/corrected/nestedWithoutFloatingPointNumbers.json"};

    } // namespace jsonio
} // namespace test

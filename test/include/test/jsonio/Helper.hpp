/**
 * @file Helper.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-09
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef TEST_LIMINAL_JSONIO_HELPER_HPP_
#define TEST_LIMINAL_JSONIO_HELPER_HPP_

#include <fs/Path.hpp>

namespace test {
    namespace jsonio {
        class Helper {
            public:

            static const fs::Path JSONIO__ASSETS__DIR;

            static const fs::Path VALID__BASIC;
            static const fs::Path VALID__EDGE_CASES;
            static const fs::Path VALID__NESTED ;
            static const fs::Path VALID__LARGE;
            static const fs::Path VALID__LARGE_WITHOUT_FLOATING_POINT_NUMBERS;
            static const fs::Path VALID__FLOATING_POINT_NUMBERS;
            static const fs::Path VALID__BASIC_WITHOUT_FLOATING_POINT_NUMBERS;
            static const fs::Path VALID__NESTED_WITHOUT_FLOATING_POINT_NUMBERS;
            static const fs::Path VALID__EMPTY;

            static const fs::Path INVALID__ARRAY__WRONG_FORMAT;

            static const fs::Path INVALID__BOOL__INCOMPLETE;

            static const fs::Path INVALID__BRACE__MISSING_CLOSING;
            static const fs::Path INVALID__BRACE__MISSING_OPENING;

            static const fs::Path INVALID__BRACKET__MISING_CLOSING;
            static const fs::Path INVALID__BRACKET__MISING_OPENING;
            static const fs::Path INVALID__BRACKET__MISING_OPENING_AT_ROOT;

            static const fs::Path INVALID_COLON__MISSING;
            static const fs::Path INVALID_COLON__TOO_MANY;
            static const fs::Path INVALID_COLON__TOO_MANY_IN_SIMPLE_KEY_VALUE_PAIR;
            static const fs::Path INVALID_COLON__WRONG_CHAR;

            static const fs::Path INVALID__COMMA__MISPLACED;
            static const fs::Path INVALID__COMMA__MISSING;
            static const fs::Path INVALID__COMMA__MISSING_IN_ARRAY;
            static const fs::Path INVALID__COMMA__MISSING_IN_NESTED_ARRAY;
            static const fs::Path INVALID__COMMA__MISSING_IN_NUM_ARRAY;
            static const fs::Path INVALID__COMMA__MULTIPLE_MISSING_IN_ARRAY;
            static const fs::Path INVALID__COMMA__TOO_MUCH;
            
            static const fs::Path INVALID__EMPTY;
            
            static const fs::Path INEXISTANT_PATH;
            static const fs::Path MISSING_LETTER_IN_FILE_EXT;

            static const fs::Path CORRECTED__BASIC;
            static const fs::Path CORRECTED__EDGE_CASES;
            static const fs::Path CORRECTED__LARGE;
            static const fs::Path CORRECTED__LARGE_WITHOUT_FLOATING_POINT_NUMBERS;
            static const fs::Path CORRECTED__FLOATING_POINT_NUMBERS;
            static const fs::Path CORRECTED__BASIC_WITHOUT_FLOATING_POINT_NUMBERS;
            static const fs::Path CORRECTED__NESTED_WITHOUT_FLOATING_POINT_NUMBERS;
        };     
    } // namespace jsonio
} // namespace test

#endif // TEST_LIMINAL_JSONIO_HELPER_HPP_

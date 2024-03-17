/**
 * @file liminal_json_io.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-04
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_TESTS_LIMINAL_JSON_IO_TEST_HPP_
#define LIMINAL_TESTS_LIMINAL_JSON_IO_TEST_HPP_

#include <string>
#include <filesystem>

namespace liminal_json_io_test {
    namespace paths {

        const std::string VALID__BASIC = "./assets/json/valid/basic.json";
        const std::string VALID__EDGE_CASES = "./assets/json/valid/edgeCases.json";
        const std::string VALID__NESTED  = "./assets/json/valid/nested.json";
        const std::string VALID__LARGE = "./assets/json/valid/large.json";

        const std::string INVALID__ARRAY__WRONG_FORMAT = "./assets/json/array/wrongFormat.json";
        
        const std::string INVALID__BOOL__INCOMPLETE = "./assets/json/bool/incomplete.json";

        const std::string INVALID__BRACE__MISSING_CLOSING = "./assets/json/brace/missingClosing.json";
        const std::string INVALID__BRACE__MISSING_OPENING = "./assets/json/brace/missingOpening.json";
        
        const std::string INVALID__BRACKET__MISING_CLOSING = "./assets/json/bracket/missingClosing.json";
        const std::string INVALID__BRACKET__MISING_OPENING = "./assets/json/bracket/missingOpening.json";
        const std::string INVALID__BRACKET__MISING_OPENING_AT_ROOT = "./assets/json/bracket/missingOpeningAtRoot.json";

        const std::string INVALID_COLON__MISSING = "./assets/json/colon/missing.json";
        const std::string INVALID_COLON__TOO_MANY = "./assets/json/colon/tooMany.json";
        const std::string INVALID_COLON__TOO_MANY_IN_SIMPLE_KEY_VALUE_PAIR = "./assets/json/colon/tooManyInSimpleKeyValuePair.json";
        const std::string INVALID_COLON__WRONG_CHAR = "./assets/json/colon/wrongChar.json";

        const std::string INVALID__COMMA__MISPLACED = "./assets/json/comma/misplaced.json";
        const std::string INVALID__COMMA__MISSING = "./assets/json/comma/missing.json";
        const std::string INVALID__COMMA__MISSING_IN_ARRAY = "./assets/json/comma/missingInArray.json";
        const std::string INVALID__COMMA__MISSING_IN_NESTED_ARRAY = "./assets/json/comma/missingInNestedArray.json";
        const std::string INVALID__COMMA__MISSING_IN_NUM_ARRAY = "./assets/json/comma/missingInNumArray.json";
        const std::string INVALID__COMMA__MULTIPLE_MISSING_IN_ARRAY = "./assets/json/comma/multipleMissingInArray.json";

        const std::string INEXISTANT_PATH = "~~~~/**//---IDo|||NotExists&&.json";
        const std::string MISSING_LETTER_IN_FILE_EXT = "./assets/json/basicNoError.jso";

    } // namespace jons_file_paths

    namespace json_path {
        const std::string INEXISTANT_PATH = "~~~~~thisPath/Sure----lyDontExists.unkownFileExt123456789";
    }
} // namespace liminal_json_io_test


#endif // LIMINAL_TESTS_LIMINAL_JSON_IO_HPP_
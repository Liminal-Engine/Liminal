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

        const std::string BASIC = "./assets/basicNoError.json";
        const std::string NESTED  = "./assets/nestedNoError.json";
        const std::string LARGE = "./assets/largeNoError.json";

        const std::string MISSING_COMMA = "./assets/missingComma.json";
        const std::string MISSING_CLOSING_BRACE = "./assets/missingClosingBrace.json";
        const std::string MISING_CLOSING_BRACKET = "./assets/missingClosingBracket.json";
        const std::string MISSING_COLON = "./assets/missingColon.json";

        const std::string INEXISTANT_PATH = "~~~~/**//---IDo|||NotExists&&.json";
        const std::string MISSING_LETTER_IN_FILE_EXT = "./assets/basicNoError.jso";

    } // namespace jons_file_paths

    namespace json_path {
        const std::string INEXISTANT_PATH = "~~~~~thisPath/Sure----lyDontExists.unkownFileExt123456789";
    }
} // namespace liminal_json_io_test


#endif // LIMINAL_TESTS_LIMINAL_JSON_IO_HPP_
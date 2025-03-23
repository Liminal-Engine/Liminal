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


#ifndef LIMINAL_TEST_HELPER_HPP_
#define LIMINAL_TEST_HELPER_HPP_

#include <string>

namespace test {
    class Helper {
        public:

        static constexpr const char*   TMP_FILE_DEFAULT_DIR       =   "./testTmp/";
        static constexpr long double   EXPECT_NEAR_ABSOLUTE_ERROR  =   0.000'000'1;

        static std::string generateUID(void);
    };
} // namespace test

#endif // LIMINAL_TEST_HELPER_HPP_


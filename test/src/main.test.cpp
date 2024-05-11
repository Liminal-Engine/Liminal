/**
 * @file main.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// class AdditionTest : public testing::Test {
//     protected:
//         int firstDigit;
//         int secondDigit;

//         AdditionTest():
//         firstDigit{4},
//         secondDigit{57}
//         {

//         }

//         ~AdditionTest() {
//             this->firstDigit = 0;
//             this->secondDigit = 0;
//         }

//         // void SetUp(void) override {
//         //     this->firstDigit = 4;
//         //     this->secondDigit = 57;
//         // }

//         // void TearDown(void) override {
//         //     this->firstDigit = 0;
//         //     this->secondDigit = 0;
//         // }

//         int add(void) {
//             return this->firstDigit + this->secondDigit;
//         }
// };

// TEST_F(AdditionTest, withFixture) {
//     EXPECT_EQ(add(), 61);
// }
// // Demonstrate some basic assertions.
// TEST(AdditionSuite, DigitUnder10) {
//     EXPECT_EQ(1+1, 2);
// }

// TEST(AdditionSuite, BigDigits0) {
//     EXPECT_EQ(11+11, 22);
//     EXPECT_EQ(45+9, 54);
//     ASSERT_STRNE("oui", "non");
//     EXPECT_STREQ("yes", "yes");
//     ASSERT_GE(46, 45);

// }

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
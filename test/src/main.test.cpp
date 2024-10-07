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

#include <filesystem>
#include <string>
#include <iostream>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    srand(time(NULL));
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

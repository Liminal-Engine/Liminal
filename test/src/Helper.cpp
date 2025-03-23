/**
 * @file Helper.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "test/Helper.hpp"

#include <chrono>
#include <random>
#include <sstream>

namespace test {
    std::string Helper::generateUID(void) {
        // Get the current time since epoch in nanoseconds
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

        // Create a random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 999999);

        // Generate a random number
        int random_number = dis(gen);

        // Combine the time and random number to create a UID
        std::stringstream ss;
        ss << std::hex << nanos << std::setw(6) << std::setfill('0') << random_number;

        return ss.str();
    }
} // namespace test

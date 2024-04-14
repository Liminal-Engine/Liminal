/**
 * @file getCWD.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-11
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <sysop/sysop.hpp>


#include <filesystem>

namespace sysop {
    fs::Path getCWD(void) { return fs::Path{std::filesystem::current_path().string()}; }
} // namespace sysop

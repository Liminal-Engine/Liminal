/**
 * @file getBinPath.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "sysop/sysop.hpp"

#include <unistd.h>
#include <linux/limits.h>
#include <cstring>
#include <vector>
#include <stdexcept>
#include <libgen.h>
#include <iostream>

#define SYSOP_BIN_LINK_PATH "/proc/self/exe" // # FIXME : linux only

namespace sysop {
    fs::Path getBinPath(void) { // TODO : create custom error types for sysop
        std::vector<char> tmp(SYSOP_BUF_SIZE, '\0');
        if (readlink(SYSOP_BIN_LINK_PATH, tmp.data(), SYSOP_BUF_SIZE) == -1) {
            // FIXME: throw custom error here
            std::cerr << strerror(errno) << std::endl; // readlink set errno, so use it
            throw std::runtime_error("Error while finding binary path");
        }
        return fs::Path{std::string{dirname(tmp.data())}};
    }
} // namespace sysop


// WINDOWS version ?:
/**
 * #include <windows.h>
#include <shlwapi.h>

char path[MAX_PATH];
GetModuleFileName(NULL, path, MAX_PATH);
PathRemoveFileSpec(path);
*/
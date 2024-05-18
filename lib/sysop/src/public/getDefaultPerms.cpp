/**
 * @file getDefaultPerms.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-12
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <fs/Permission.hpp>

#include <sys/types.h>
#include <sys/stat.h>

namespace sysop {

    fs::Permission getDefaultPerms(void) noexcept {
        mode_t c_mask = umask(0);
        umask(c_mask); // immediatly reset umask

        return fs::Permission(static_cast<mode_t>(0666 - c_mask));
    }
} // namespace sysop

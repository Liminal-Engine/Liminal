/**
 * @file sysop.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef _LIMINAL_LIB_SYSOP_HPP_
#define _LIMINAL_LIB_SYSOP_HPP_


#include <fs/Path.hpp>
#include <fs/Permission.hpp>

#define SYSOP_BUF_SIZE 2048

namespace sysop {
    fs::Path getBinPath(void);  // FIXME : precise throw type here
    fs::Path getCWD(void);
    fs::Permission getDefaultPerms(void) noexcept;
} // namespace sysop


#endif // _LIMINAL_LIB_SYSOP_HPP_


/**
 * @file Entry.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-04
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef _LIMINAL_FS_ENTRY_HPP_
#define _LIMINAL_FS_ENTRY_HPP_

#include "fs/Size.hpp"
#include "fs/User.hpp"
#include "fs/Permission.hpp"

#include <time/Date.hpp>

#include <string>
#include <vector>
#include <optional>

namespace fs {

    class Path;
    class Entry {
        public:

            enum class Type {
                REGULAR_FILE,
                DIRECTORY,
                SYM_LINK,
                BLOCK_DEVICE,
                CHARACTER_DEVICE,
                FIFO,
                SOCKET,
                UNKNOWN
            };

            Entry(const Path &path) noexcept;
            Entry(const Entry &other) noexcept;
            Entry(void) noexcept;
            Entry(Entry &&other) noexcept; // move constructor
            ~Entry();

            Entry operator=(const Path &other) noexcept; // TODO : implement and test this
            bool operator==(const Entry &other) const noexcept;

            std::string getName(void) const noexcept;
            Type getType(void) const noexcept;
            Size getSize(void) const noexcept;
            bool isHidden(void) const noexcept;
            time_::Date getLastModif(void) const noexcept; // FIXME : may be only linux
            time_::Date getLastAccess(void) const noexcept; // FIXME : may be only linux
            time_::Date getLastStatusChange(void) const noexcept; // FIXME : may be only linux
            Permission getPermissions(void) const noexcept;
            std::optional<std::string> getExtension(void) const noexcept;
            Entry getParent(void) const noexcept; // TODO : move this to Path and test
            std::vector<Entry> getChildren(void) const noexcept; // TODO : move this to Path and test

        private:
            class _EntryImpl;
            std::unique_ptr<_EntryImpl> _impl;
            friend class Path;
    };
} // namespace fs


#endif // _LIMINAL_FS_ENTRY_HPP_
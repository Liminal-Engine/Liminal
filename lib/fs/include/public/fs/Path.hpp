/**
 * @file Path.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-25
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef LIMINAL_LIB_FS_PATH_HPP_
#define LIMINAL_LIB_FS_PATH_HPP_

#include "Status.hpp"
#include "Entry.hpp"
#include "Permission.hpp"


#include <string>
#include <memory>
#include <optional>
#include <cstdlib>
#include <vector>


//************ FORWARD DECLARATIONS
namespace sysop {
    fs::Permission getDefaultPerms(void) noexcept;
} // namespace sysop

//************

namespace fs {

    class Path {
        public:
            
            enum class Resolution {
                ABSOLUTE,
                RELATIVE
            };

            Path(const std::string &path);
            Path(const Path &path);
            Path(void);
            ~Path();

            // Setters
            Status insert(const std::string &entryName);
            Status insert(const std::string &entryName, const std::size_t &pos);
            Status insert(const Entry &entry);
            Status insert(const Entry &entry, const std::size_t &pos);
            Status clean(void);
            Status toAbsolute(void);
            Status toRelative(void);

            // Getters
            std::string asStr(void) const;
            Entry getEntry(void) const;
            Entry getEntry(const std::size_t &pos) const;
            std::size_t getNEntry(void) const;
            Resolution getResolution(void) const;
            bool isEmpty(void) const;
            bool pointsTo(const Path &target) const;
            bool isRoot(void) const noexcept;
            std::optional<Path> getParent(void) const noexcept;
            std::vector<Path> getChildren(void) const noexcept;

            // TODO : check for path vaiability and wrong chars
            Status create(
                const Entry::Type &type = Entry::Type::REGULAR_FILE,
                const bool &createParents = false,
                const Permission &perms = ::sysop::getDefaultPerms(),
                const Path &symLinkTarget = Path()
            ) const noexcept; // TODO : test this method and add param to send permissions (default must be the same that touch or mkdir would do, test this)
            Status updatePermissions(const Permission &newPerms) const noexcept;
            Status remove(void) const;
            bool exists(void) const;
            Path operator=(const Path &other) const;
            bool operator==(const Path &other) const;
            // TODO : operator + with string ?
            Path operator+(const Path &other) const;

            static bool isPath(const std::string &str) noexcept; // TODO : move this in parseop ?

        private:
            class _PathImpl;
            std::unique_ptr<_PathImpl> _pImpl;

    };
} // namespace fs


#endif // LIMINAL_LIB_FS_PATH_HPP_
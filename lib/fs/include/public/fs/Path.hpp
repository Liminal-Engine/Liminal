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

#include <string>
#include <memory>
#include <optional>
#include <cstdlib>
#include <vector>

namespace fs {
    using Entry_t = std::string;
    
    class Path {

        public:

            enum class Resolution {
                ABSOLUTE,
                RELATIVE
            };

            Path(void);
            Path(const std::string &path);
            Path(const Path &path);
            ~Path();

            // Setters
            Status insert(const Entry_t &entry);
            Status insert(const Entry_t &entry, const std::size_t &pos);
            Status clean(void);
            Status toAbsolute(void);
            Status toRelative(void);

            // Getters
            std::optional<Entry_t> getEntry(void) const;
            std::optional<Entry_t> getEntry(const std::size_t &pos) const;
            std::size_t getNEntry(void) const;
            std::optional<std::string> getExtension(void) const;
            Entry::Type getType(void) const;
            bool isEmpty(void) const;
            Resolution getResolution(void) const;
            std::optional<Path> getParent(void) const;
            bool pointsTo(const Path &target) const;
            Entry_t getDirName(void) const; // TODO : implement this ands test
            std::vector<Entry_t> getChildren(void) const; // TODO implement this ands test

            // FIXME: create a struct create_otps containing all options ? (createParents, symlink_target, perms, ...) and change createParent default value to false then
            Status create(const Entry::Type &type, const bool &createParents = true) const; // TODO : test this method and add param to send permissions (default must be the same that touch or mkdir would do, test this)
            Status remove(void) const;
            bool exists(void) const;
            std::string toStr(void) const;
            Path operator=(const Path &other) const;
            bool operator==(const Path &other) const;
            Path operator+(const Path &other) const;

            static bool isPath(const std::string &str); // TODO : move this in parseop ?
            // TODO : implement chmod, and add chmod in create method
            // TODO : implement remove
            // TODO : implement isHidden, return isHidden of the last entry

        private:
            class _PathImpl;
            std::unique_ptr<_PathImpl> _pImpl;

    };
} // namespace fs


#endif // LIMINAL_LIB_FS_PATH_HPP_
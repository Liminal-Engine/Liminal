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

#include <time/Date.hpp>

#include <string>
#include <memory>
#include <optional>
#include <cstdlib>
#include <vector>


// FIXME : mettre entry, et size en dehors, au niveau de namesapce fs

namespace fs {

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
            Status insert(const std::string &entryName);
            Status insert(const std::string &entryName, const std::size_t &pos);
            Status insert(const Entry &entry);
            Status insert(const Entry &entry, const std::size_t &pos);
            Status clean(void);
            Status toAbsolute(void);
            Status toRelative(void);

            // Getters
            Entry getEntry(void) const;
            Entry getEntry(const std::size_t &pos) const;
            std::size_t getNEntry(void) const;
            std::optional<std::string> getExtension(void) const; // ->
            bool isEmpty(void) const;
            Resolution getResolution(void) const;
            std::optional<Path> getParentPath(void) const;
            std::optional<Entry> getParentEntry(void) const;
            bool pointsTo(const Path &target) const;
            bool isRoot(void) const noexcept;
            std::string getDirName(void) const; // TODO : implement this ands test -->
            std::vector<Path> getChildrenPath(void) const; // TODO implement this ands test ->
            std::vector<Entry> getChildrenEntry(void) const;

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
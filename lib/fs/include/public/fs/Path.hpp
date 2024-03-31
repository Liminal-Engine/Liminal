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

#include <string>
#include <memory>
#include <optional>
#include <cstdlib>

namespace fs {
    using Entry_t = std::string;
    
    class Path {

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

        public:

            Path(void);
            Path(const std::string &path);
            Path(const Path &path);
            ~Path();
            
            // Setters
            Status insert(const Entry_t &entry);
            Status insert(const Entry_t &entry, const std::size_t &pos);
            Status clean(void);

            // Getters
            std::optional<Entry_t> getEntry(void) const;
            std::optional<Entry_t> getEntry(const std::size_t &pos) const;
            std::size_t getNEntry(void) const;
            std::optional<std::string> getExtension(void) const;
            Path getAbsolute(void) const;
            Type getType(void) const;
            bool empty(void) const;
            // TODO getter to know   if is absolute or relative


            bool exists(void) const;
            std::string toStr(void) const;
            Path operator=(const Path &other) const;
            bool operator==(const Path &other) const;


            static bool isPath(const std::string &str);

        private:
            class _PathImpl;
            std::unique_ptr<_PathImpl> _pImpl;

    };
} // namespace fs


#endif // LIMINAL_LIB_FS_PATH_HPP_
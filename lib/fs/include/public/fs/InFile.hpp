/**
 * @file InFile.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-20
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef FS_LIB_IFILE_HPP_
#define FS_LIB_IFILE_HPP_

#include "Status.hpp"
#include "Path.hpp"

#include <fstream>
#include <memory>
#include <optional>

namespace fs {
    class InFile {

        public:

            InFile(const Path &path);
            ~InFile();

            //Common methods for each template class (redefined because template class is hidden)
            Status open(void);
            Status close(void);
            bool has_extension(void) const;
            std::optional<std::string> get_extension(void) const;
            bool isOpen(void) const;

            Status read(void);
            // Getters :
            std::string get_content(void) const;

        private:
            class _InFileImpl; // forward declaration
            const std::unique_ptr<_InFileImpl> _pImpl;
    };
}

#endif // FS_LIB_IFILE_HPP_
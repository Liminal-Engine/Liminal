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

#ifndef _LIMINAL_FS_IFILE_HPP_
#define _LIMINAL_FS_IFILE_HPP_

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

            // FIXME : replace with getPath
            // std::optional<std::string> getExtension(void) const;
            bool isOpen(void) const;

            Status read(void);
            // Getters :
            std::string getContent(void) const;

        private:
            class _InFileImpl; // forward declaration
            const std::unique_ptr<_InFileImpl> _pImpl;
    };
}

#endif // _LIMINAL_FS_IFILE_HPP_

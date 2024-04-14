/**
 * @file OutFile.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-01
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_FS_OUTFILE_HPP_
#define LIMINAL_LIB_FS_OUTFILE_HPP_

#include "Status.hpp"
#include "Path.hpp"

#include <fstream>
#include <memory>
#include <sstream>

namespace fs {
    class OutFile {
        public:

            OutFile(const Path &path);
            ~OutFile();

            // From base class :
            Status open(const bool &clear = false);
            Status close(void);
            std::optional<std::string> getExtension(void) const;
            bool isOpen(void) const;

            Status clear(void);
            Status write(const std::string &data);

        private:
            class _OutFileImpl;
            const std::unique_ptr<_OutFileImpl> _pImpl;
    };
} // namespace fs


#endif // LIMINAL_LIB_FS_OUTFILE_HPP_
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
            bool has_extension(void) const; // TOOD : since get_extension returns an optional, is this stil necessary (I think NO)
            std::optional<std::string> get_extension(void) const;
            bool isOpen(void) const;

            Status write(const std::stringstream &data);
            Status write(const std::string &data);
            Status clear(void);

            static Status create(const Path &path); // TODO : implement full path type and logic first then implement it

        private:
            class _OutFileImpl;
            const std::unique_ptr<_OutFileImpl> _pImpl;
    };
} // namespace fs


#endif // LIMINAL_LIB_FS_OUTFILE_HPP_
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

#ifndef LIMINAL_FS_LIB_IFILE_HPP
#define LIMINAL_FS_LIB_IFILE_HPP

#include <fstream>
#include <memory>
#include <optional>

namespace liminal_fs {

    // Forward declarations :
    enum class Status;
    namespace path {
        using path_t = std::string;
    }

    class InFile { //Using pimpl idiom to hide class template

        public:

            InFile(const path::path_t &path);
            ~InFile();

            //Common methods for each template class (redefined because template class is hidden)
            Status open(void);
            Status close(void);
            bool has_extension(void) const;
            std::optional<std::string> get_extension(void) const;

            Status read(void);
            // Getters :
            std::string get_content(void) const;

        private:
            class _InFileImpl; // forward declaration
            const std::unique_ptr<_InFileImpl> _pImpl;
    };
}

#endif // LIMINAL_FS_LIB_IFILE_HPP
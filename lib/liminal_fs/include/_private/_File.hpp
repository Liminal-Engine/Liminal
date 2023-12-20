/**
 * @file _File.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LIMINAL_LIB_LIMINAL_FS__PRIVATE__FILE_HPP_
#define LIMINAL_LIB_LIMINAL_FS__PRIVATE__FILE_HPP_

#include "Status.hpp"

#include <string>

namespace liminal_fs {
    namespace _private {
        
        /**
         * @brief Base class of all *File classes of liminal fs lib
         * 
         */
        class _File {
            public:
                _File(const std::string &path);
                ~_File() = default;
                virtual Status open(const std::string &path) = 0;
                virtual Status close(void) = 0;

            protected:
                const std::string _name;
                const std::string _registered_path;
                const std::string _absolute_path;
                const std::string _extension;
                // const size_t _size_bytes;

            private:
                /**
                 * @brief Loads the file name from the path
                 * 
                 * @param path 
                 * @throw 
                 * @return const std::string& 
                 */
                const std::string __load_name(const std::string &path);
                /**
                 * @brief Loads the abosulte version of the path
                 * 
                 * @param path 
                 * @return const std::string& 
                 */
                const std::string __load_abolute_path(const std::string &path);
                /**
                 * @brief Loads the extension of the specified path
                 * 
                 * @param path 
                 * @return const std::string& 
                 */
                const std::string __load_extension(const std::string &path);

        };

    }
} // namespace name


#endif // LIMINAL_LIB_LIMINAL_FS__PRIVATE__FILE_HPP_
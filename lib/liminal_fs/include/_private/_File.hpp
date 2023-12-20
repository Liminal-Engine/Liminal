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
#include "path/path.hpp"

#include <string>
#include <stdexcept>

namespace liminal_fs {
    namespace _private {
        
        /**
         * @brief Base class of all *File classes of liminal fs lib
         * 
         */
        template <typename _StreamType>
        class _File {
            public:
                Status open(void) {
                    if (this->_stream_opened == false) {
                        this->_stream = _StreamType(this->_registered_path);

                        if (!this->_stream) {
                            return Status::OPEN_FILE_ERR;
                        }
                        this->_stream_opened = true;
                    }
                    return Status::OK;
                }

                Status close(void) {
                    if (this->_stream_opened == true) {
                        this->_stream.close();
                        if (this->_stream.is_open()) {
                            return Status::CLOSE_FILE_ERR;
                        }
                        this->_stream_opened = false;
                    }
                    return Status::OK;
                }

                // Getters :
                bool has_extension(void) const {
                    return this->_extension != "";
                }

                std::string get_extension(void) const {
                    return this->_extension;
                }

            protected:
                _File(const path::path_t &path) :
                _name{this->__load_name(path)},
                _registered_path{path},
                _absolute_path{this->__load_abolute_path(path)},
                _extension{this->__load_extension(path)},
                _stream_opened{false}
                {
                }
                ~_File() = default;
                const std::string _name;
                const std::string _registered_path;
                const std::string _absolute_path;
                const std::string _extension;
                // const size_t _size_bytes;

                _StreamType _stream;
                bool _stream_opened;

            private:
                /**
                 * @brief Loads the file name from the path
                 * 
                 * @param path 
                 * @throw 
                 * @return const std::string& 
                 */
                const std::string __load_name(const path::path_t &path) {
                    std::string res{""};

                    if (path::get_file_name(res, path) != Status::OK) {
                        throw std::runtime_error("Failed to get file name");
                    }
                    return res;
                }
                /**
                 * @brief Loads the abosulte version of the path
                 * 
                 * @param path 
                 * @return const std::string& 
                 */
                const std::string __load_abolute_path(const path::path_t &path) {
                    std::string res{""};

                    if (path::get_absolute_path(res, path) != Status::OK) {
                        throw std::runtime_error("Failed to get file absolute path");
                    }
                    return res;
                }
                /**
                 * @brief Loads the extension of the specified path
                 * 
                 * @param path 
                 * @return const std::string& 
                 */
                const std::string __load_extension(const path::path_t &path) {
                    std::string res{""};

                    if (path::get_file_extension(res, path) != Status::OK) {
                        throw std::runtime_error("Failed to get file absolute path");
                    }
                    return res;
                }

        };


    }
} // namespace name


#endif // LIMINAL_LIB_LIMINAL_FS__PRIVATE__FILE_HPP_
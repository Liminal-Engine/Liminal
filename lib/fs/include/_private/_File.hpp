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

#ifndef LIMINAL_LIB_FS__PRIVATE__FILE_HPP_
#define LIMINAL_LIB_FS__PRIVATE__FILE_HPP_

#include "Status.hpp"
#include "Path.hpp"

#include <string>
#include <stdexcept>
#include <optional>
#include <variant>
#include <iostream>

namespace fs {
    namespace _private {
        
        /**
         * @brief Base class of all *File classes of liminal fs lib
         * This class must be defined and declared in a header file since it is a template class
         * 
         */
        using _StreamType = std::variant<std::ofstream, std::ifstream>;
        template <typename _StreamType>
        class _File {
            public:
                Status open(const bool &clear = false) {
                    if (this->_stream_opened == false) {
                        this->_stream = clear ? _StreamType(this->_registered_path.toStr(), std::ios::trunc) : _StreamType(this->_registered_path.toStr());

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

                std::optional<std::string> getExtension(void) const {
                    return this->_extension;
                }

                bool isOpen(void) const { return this->_stream_opened; }

            protected:
                _File(const Path &path) :
                _name{this->__loadName(path)},
                _registered_path{path},
                _absolute_path{path.getAbsolute()},
                _extension{path.getExtension()},
                _stream_opened{false}
                {
                }

                ~_File() = default;
                const std::string _name;
                const Path _registered_path;
                const Path _absolute_path;
                const std::optional<std::string> _extension;
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
                const std::string __loadName(const Path &path) {
                    std::optional<std::string> res = path.getEntry();

                    if ( !res.has_value() ) {
                        throw std::runtime_error("Failed to get file name");
                    }
                    return res.value();
                }
        };
    }
} // namespace name


#endif // LIMINAL_LIB_FS__PRIVATE__FILE_HPP_
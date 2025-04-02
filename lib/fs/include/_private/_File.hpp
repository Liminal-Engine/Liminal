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

#ifndef _LIMINAL_LIB_FS__PRIVATE__FILE_HPP_
#define _LIMINAL_LIB_FS__PRIVATE__FILE_HPP_

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
        // FIXME : code this in a cpp file ?
        using _StreamType = std::variant<std::ofstream, std::ifstream>;
        template <typename _StreamType>
        class _File {
            public:
                Status open(const bool &clear = false) {
                    if ( !this->_registered_path.exists() ) return Status::E_PATH_NO_TARGET;
                    if (this->_registered_path.getEntry().getType() == Entry::Type::DIRECTORY) return Status::E_PATH_IS_DIR;
                    if (this->_stream_opened == false) {
                        this->_stream = _StreamType(
                            this->_registered_path.asStr(), 
                            clear ? std::ios::trunc : std::ios::app
                        );
                        if (!this->_stream) {
                            return Status::E_FILE_OPEN;
                        }
                        this->_stream_opened = true;
                    }
                    return Status::OK;
                }

                /**
                 * Return OK even if not opened
                 * 
                 * @return Status 
                 */
                Status close(void) {
                    if (this->_stream_opened == true) {
                        this->_stream.close();
                        if (this->_stream.is_open()) {
                            return Status::E_CANNOT_CLOSE_FILE;
                        }
                        this->_stream_opened = false;
                        return Status::OK;
                    }
                    return Status::E_CLOSE_FILE_NOT_OPEN;
                }

                // std::optional<std::string> getExtension(void) const {
                //     return this->_extension;
                // }

                bool isOpen(void) const { return this->_stream_opened; }

            protected:
                _File(const Path &path) :
                _name{this->__loadName(path)},
                _registered_path{path},
                _absolute_path{__loadAbsolute(path)},
                _extension{path.getEntry().getExtension()},
                _stream_opened{false}
                {}

                ~_File() = default;
                const std::optional<std::string> _name;
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
                const std::optional<std::string> __loadName(const Path &path) {
                    std::optional<fs::Entry> optionalEntry = path.getEntry();
                    if (optionalEntry.has_value()) return optionalEntry.value().getName(); // FIXME : if path is relative and sent "./" or "../../" for example, _name will be empety when in reality it is not (should be taken from absolute path instead of path)
                    return std::optional<std::string>(std::nullopt);
                }

                const fs::Path __loadAbsolute(const Path &path) {
                    fs::Path cpy = path;
                    if (cpy.toAbsolute() != fs::Status::OK) {} // FIXME : do this and handle error if not possible

                    return fs::Path{cpy};
                }
        };
    }
} // namespace name

#endif // _LIMINAL_LIB_FS__PRIVATE__FILE_HPP_
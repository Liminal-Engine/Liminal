/**
 * @file InFile.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-20
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Status.hpp"
#include "Path.hpp"
#include "_private/_File.hpp"

#include "InFile.hpp"

#include <iostream>
#include <memory>

namespace fs {
    class InFile::_InFileImpl : public _private::_File<std::ifstream> {
        public:
            _InFileImpl(const Path &path) :
            _File{path}
            {

            }

            Status read(void) {
                if (this->_stream_opened) {
                    this->_stream.seekg(0, std::ios::beg);
                    this->_buffer = std::string(
                        std::istreambuf_iterator<char>(this->_stream),
                        std::istreambuf_iterator<char>()
                    );
                    this->_stream.seekg(0, std::ios::beg);
                    return Status::OK;
                }
                return Status::CANNOT_READ_FILE_IS_CLOSED;
        }

        std::string get_content(void) const {
            return this->_buffer;
        }

        private:
            std::string _buffer;
    };

    //In File class definition starts here :
    InFile::InFile(const Path &path) :
    _pImpl(std::make_unique<_InFileImpl>(path))
    {

    }

    InFile::~InFile() = default;

    // Redifinition of template class methods:
    Status InFile::open(void) { return this->_pImpl->open(); }
    Status InFile::close(void) { return this->_pImpl->close(); }
    bool InFile::has_extension(void) const { return this->_pImpl->has_extension(); }
    std::optional<std::string> InFile::get_extension(void) const { return this->_pImpl->get_extension(); }
    bool InFile::isOpen(void) const { return this->_pImpl->isOpen(); }

    //Current class methods definition
    Status InFile::read(void) { return this->_pImpl->read(); }
    std::string InFile::get_content(void) const { return this->_pImpl->get_content(); }

}

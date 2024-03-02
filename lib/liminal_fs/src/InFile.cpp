#ifndef LIMINAL_LIB_LIMINAL_FS_IFILE_HPP
#define LIMINAL_LIB_LIMINAL_FS_IFILE_HPP

#include "Status.hpp"
#include "path/path.hpp"
#include "_private/_File.hpp"

#include "InFile.hpp"

#include <iostream>
#include <memory>
namespace liminal_fs {

    class InFile::_InFileImpl : public _private::_File<std::ifstream> {
        public:
            _InFileImpl(const path::path_t &path) :
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
    InFile::InFile(const path::path_t &path) :
    _pImpl(std::make_unique<_InFileImpl>(path))
    {

    }

    InFile::~InFile() = default;

    // Redifinition of template class methods:
    Status InFile::open(void) { return this->_pImpl->open(); }
    Status InFile::close(void) { return this->_pImpl->close(); }
    bool InFile::has_extension(void) const { return this->_pImpl->has_extension(); }
    std::string InFile::get_extension(void) const { return this->_pImpl->get_extension(); }

    //Current class methods definition
    Status InFile::read(void) { return this->_pImpl->read(); }
    std::string InFile::get_content(void) const { return this->_pImpl->get_content(); }

}

#endif // LIMINAL_LIB_LIMINAL_FS_IFILE_HPP
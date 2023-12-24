#ifndef LIMINAL_LIB_LIMINAL_FS_IFILE_HPP
#define LIMINAL_LIB_LIMINAL_FS_IFILE_HPP

#include "InFile.hpp"
#include "Status.hpp"

#include <iostream>

namespace liminal_fs {
    InFile::InFile(const path::path_t &path) :
    _File{path}
    {

    }

    Status InFile::read(void) {
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

    std::string InFile::get_content(void) const {
        return this->_buffer;
    }
    

}

#endif // LIMINAL_LIB_LIMINAL_FS_IFILE_HPP
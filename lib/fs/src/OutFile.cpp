/**
 * @file OutFile.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "Status.hpp"
#include "_private/_File.hpp"
#include "OutFile.hpp"

namespace fs {
    class OutFile::_OutFileImpl : virtual public _private::_File<std::ofstream> {

        public:
            _OutFileImpl(const Path &path) :
            _File{path}
            {

            }

            Status write(const std::string &data) {
                if (this->_stream_opened) {
                    this->_stream << data;
                    return Status::OK;
                }
                return Status::E_WRITE_FILE_CLOSED;
            };

            Status clear(void) {
                Status tmpStatus;

                if (this->_stream_opened)
                    if ( (tmpStatus = this->close()) != Status::OK ) return tmpStatus;          
                return this->open(true);
            };
    };

    // exposed OutFile class :
    OutFile::OutFile(const Path &path) :
    _pImpl{std::make_unique<_OutFileImpl>(path)}
    {

    }

    OutFile::~OutFile() = default;

    // Redefinition of base class methods
    Status OutFile::open(const bool &clear) { return this->_pImpl->open(clear); }
    Status OutFile::close(void) { return this->_pImpl->close(); }
    fs::Path OutFile::getAbsolutePath(void) const { return this->_pImpl->getAbsolutePath(); };
    // std::optional<std::string> OutFile::getExtension(void) const { return this->_pImpl->getExtension(); }
    bool OutFile::isOpen(void) const { return this->_pImpl->isOpen(); }

    // Actual OutFile class methods :
    Status OutFile::clear(void) { return this->_pImpl->clear(); }    
    Status OutFile::write(const std::string &data) { return this->_pImpl->write(data); }

} // namespace fs

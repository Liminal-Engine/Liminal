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
#include "path/path.hpp"
#include "_private/_File.hpp"
#include "OutFile.hpp"


namespace fs {
    class OutFile::_OutFileImpl : public _private::_File<std::ofstream> {

        public:
            _OutFileImpl(const path::path_t &path) :
            _File{path}
            {}

            Status write(const std::stringstream &data) {
                return this->write(data.str());
            }
            
            Status write(const std::string &data) {
                if (this->_stream_opened) {
                    this->_stream << data;
                    return Status::OK;
                }
                return Status::CANNOT_WRITE_FILE_IS_CLOSED;
            }

            Status clear(void) {
                Status tmpStatus;

                if (this->_stream_opened)
                    if ( (tmpStatus = this->close()) != Status::OK ) return tmpStatus;                
                return this->open(true);
            }
    };


    // exposed OutFile class :
    OutFile::OutFile(const path::path_t &path) :
    _pImpl{std::make_unique<_OutFileImpl>(path)}
    {}

    OutFile::~OutFile() = default;

    // Redefinition of base class methods
    Status OutFile::open(const bool &clear) { return this->_pImpl->open(clear); }
    Status OutFile::close(void) { return this->_pImpl->close(); }
    bool OutFile::has_extension(void) const { return this->_pImpl->has_extension(); }
    std::optional<std::string> OutFile::get_extension(void) const { return this->_pImpl->get_extension(); }

    // Actual OutFile class methods :
    Status OutFile::write(const std::stringstream &data) { return this->_pImpl->write(data); }
    Status OutFile::write(const std::string &data) { return this->_pImpl->write(data); }
    Status OutFile::clear(void) { return this->_pImpl->clear(); }

} // namespace fs

/**
 * @file Size.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-04
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "Size.hpp"

namespace fs {

#ifndef _LIMINAL_LIB_FS_SIZE_CLASS_DECLARATION_
#define _LIMINAL_LIB_FS_SIZE_CLASS_DECLARATION_
#define _BYTES_FACTOR_ 1024.0

    class Size::_SizeImpl {
        private:
            const uint64_t _bytes;

        public:
            _SizeImpl(const uint64_t &bytes) noexcept :
            _bytes(bytes)
            {}

            _SizeImpl(const _SizeImpl &other) noexcept :
            _bytes(other._bytes)
            {}

            _SizeImpl(void) noexcept :
            _bytes(0)
            {}

            ~_SizeImpl() noexcept = default;

            uint64_t toBytes(void) const noexcept { return this->_bytes; };
            double toKBytes(void) const noexcept { return this->toBytes() / _BYTES_FACTOR_; };
            double toMBytes(void) const noexcept { return this->toKBytes() / _BYTES_FACTOR_; };
            double toGBytes(void) const noexcept { return this->toMBytes() / _BYTES_FACTOR_; };
            double toTBytes(void) const noexcept { return this->toGBytes() / _BYTES_FACTOR_; };

            bool operator==(const _SizeImpl &other) const noexcept {
                return this->_bytes == other._bytes;
            }
    };

    Size::Size(const uint64_t &bytes) noexcept:
    _impl(std::make_unique<Size::_SizeImpl>(bytes))
    {}

    Size::Size(const Size &other) noexcept :
    _impl(std::make_unique<Size::_SizeImpl>(*other._impl))
    {}

    Size::Size(void) noexcept :
    _impl(std::make_unique<Size::_SizeImpl>())
    {}

    Size::~Size() noexcept = default;

    bool Size::operator==(const Size &other) const noexcept { return this->_impl->operator==(*other._impl); }

    uint64_t Size::toBytes(void) const noexcept { return this->_impl->toBytes(); }
    double Size::toKBytes(void) const noexcept { return this->_impl->toKBytes(); }
    double Size::toMBytes(void) const noexcept { return this->_impl->toMBytes(); }
    double Size::toGBytes(void) const noexcept { return this->_impl->toGBytes(); }
    double Size::toTBytes(void) const noexcept { return this->_impl->toTBytes(); }


#undef _BYTES_FACTOR_
#undef _LIMINAL_LIB_FS_SIZE_CLASS_DECLARATION_
#endif

} // namespace fs

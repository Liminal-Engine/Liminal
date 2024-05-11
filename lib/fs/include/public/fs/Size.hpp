#ifndef LIMINAL_LIB_FS_SIZE_HPP_
#define LIMINAL_LIB_FS_SIZE_HPP_

#include <memory>
#include <cstdint>

namespace fs {
    class Size {
        public:
            explicit Size(const uint64_t &bytes) noexcept;
            Size(const Size &other) noexcept;
            Size(void) noexcept;
            ~Size() noexcept;

            bool operator==(const Size &other) const noexcept;

            //Getters
            uint64_t toBytes(void) const noexcept;
            double toKBytes(void) const noexcept;
            double toMBytes(void) const noexcept;
            double toGBytes(void) const noexcept;
            double toTBytes(void) const noexcept;

        private:
            class _SizeImpl;
            std::unique_ptr<_SizeImpl> _impl;
    };
} // namespace fs

#endif // LIMINAL_LIB_FS_SIZE_HPP_

#ifndef __LIMINAL__RHI__DEF__HANDLE_HPP__
#define __LIMINAL__RHI__DEF__HANDLE_HPP__


#include <cstdint>
#include <limits>

namespace rhi {
    namespace def {
        using Handle = uint32_t;

        static constexpr Handle NULL_HANDLE = std::numeric_limits<Handle>::max();
    } // namespace def
} // namespace rhi


#endif // __LIMINAL__RHI__DEF__HANDLE_HPP__
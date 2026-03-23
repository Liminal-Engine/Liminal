#ifndef __LIMINAL__LIB__RHI__DEF__RHI_HPP__
#define __LIMINAL__LIB__RHI__DEF__RHI_HPP__

#include "Status.hpp"

namespace rhi {
    Status init(void) noexcept;
    Status setViewport(int left, int top, size_t width, size_t height) noexcept;
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__DEF__RHI_HPP__
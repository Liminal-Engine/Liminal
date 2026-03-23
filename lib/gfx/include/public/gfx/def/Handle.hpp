#ifndef __LIMINAL__GFX__DEF__HANDLE_HPP__
#define __LIMINAL__GFX__DEF__HANDLE_HPP__

#include<cstdint>
#include <limits>

namespace gfx {
    namespace def { // FIXME: find a better namespace
        using Handle = uint32_t;
        static constexpr Handle NULL_HANDLE = std::numeric_limits<Handle>::max();
    } // namespace def 
} // namespace gfx


#endif // __LIMINAL__GFX__DEF__HANDLE_HPP__
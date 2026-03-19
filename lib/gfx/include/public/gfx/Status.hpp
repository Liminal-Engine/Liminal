#ifndef __LIMINAL__LIB__GFX__INCLUDE__STATUS_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__STATUS_HPP__


namespace gfx {
    enum class Status {
        OK,
        N_OK,
        E_ALREADY_EXISTS,
        E_FILE_EMPTY,
        E_FILE_CONTENT
    };
} // namespace gfx

#endif // __LIMINAL__LIB__GFX__INCLUDE__STATUS_HPP__
#ifndef __LIMINAL__LIB__GFX__STATUS_HPP__
#define __LIMINAL__LIB__GFX__STATUS_HPP__

#include <string>

namespace gfx {
    enum class Status {
        OK,
        N_OK,
        E_FILE_CONTENT,
        E_INIT,
        E_TYPE,
        E_ALREADY_EXISTS,
        E_GL
    };

    std::string toStr(const Status &status) noexcept;

} // namespace gfx


#endif // __LIMINAL__LIB__GFX__STATUS_HPP__
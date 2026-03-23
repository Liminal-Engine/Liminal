#ifndef __LIMINAL__RHI__STATUS_HPP__
#define __LIMINAL__RHI__STATUS_HPP__

#include <string>

namespace rhi {
    enum class Status {
        OK,
        N_OK,
        E_ALREADY_EXISTS,
        E_GLAD,
        E_OPEN_GL
    };

    std::string toStr(Status status) noexcept;
} // namespace rhi

#endif // __LIMINAL__RHI__STATUS_HPP__
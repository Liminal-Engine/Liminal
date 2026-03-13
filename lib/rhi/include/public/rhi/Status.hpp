#ifndef __LIMINAL__LIB__RHI__INCLUDE__STATUS_HPP__
#define __LIMINAL__LIB__RHI__INCLUDE__STATUS_HPP__

namespace rhi {
    enum class Status {
        OK,
        N_OK,
        E_ALREADY_INIT,
        E_NOT_INIT,
        E_ALREADY_EXISTS
    };
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__INCLUDE__STATUS_HPP__
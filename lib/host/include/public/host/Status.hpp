#ifndef __LIMINAL__LIB__HOST__STATUS_HPP__
#define __LIMINAL__LIB__HOST__STATUS_HPP__

namespace host {
    enum class Status {
        OK,
        N_OK,
        E_ASSET_LOAD,
        E_ASSET_NO_EXISTS,
        E_ASSET_NOT_LOADED
    };
} // namespace host


#endif // __LIMINAL__LIB__HOST__STATUS_HPP__
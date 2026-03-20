#include "Status.hpp"

namespace rhi {
    std::string toStr(const Status &status) noexcept {
        switch (status) {
            case Status::OK: return "OK";
            case Status::N_OK: return "N_OK";
            case Status::E_ALREADY_EXISTS: return "E_ALREADY_EXISTS";
        }
        return "UNKNOWN";
    }
} // namespace rhi

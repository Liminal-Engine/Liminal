#include "Status.hpp"

namespace rhi {
    std::string toStr(Status status) noexcept {
        switch (status) {
            case Status::OK: return "OK";
            case Status::N_OK: return "N_OK";
            case Status::E_ALREADY_EXISTS: return "E_ALREADY_EXISTS";
            case Status::E_GLAD: return "E_GLAD";
            case Status::E_OPEN_GL: return "E_OPEN_GL";
        }
        return "UNKNOWN";
    }
} // namespace rhi

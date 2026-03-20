#include "Status.hpp"

namespace gfx {
    std::string toStr(const Status &status) noexcept {
        switch (status) {
            case Status::OK: return "OK";
            case Status::N_OK: return "N_OK";
            case Status::E_FILE_CONTENT: return "E_FILE_CONTENT";
            case Status::E_INIT: return "E_INIT";
            case Status::E_TYPE: return "E_TYPE";
            case Status::E_ALREADY_EXISTS: return "E_ALREADY_EXISTS";
            case Status::E_UNKNOWN_RESOURCE_TYPE: return "E_UNKNOWN_RESOURCE_TYPE";
            case Status::E_PATH: return "E_PATH";
            case Status::E_LOAD: return "E_LOAD";
        }
        return "UNKNOWN";
    }
} // namespace gfx

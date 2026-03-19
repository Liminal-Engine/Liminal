#include "Status.hpp"

#include <string>

namespace gfx {
    std::string toStr(const Status &status) {
        switch (status) {
            case Status::OK: return "OK";
            case Status::N_OK: return "N_OK";
            case Status::E_ALREADY_EXISTS: return "E_ALREADY_EXISTS";
            case Status::E_FILE_EMPTY: return "E_FILE_EMPTY";
            case Status::E_FILE_CONTENT: return "E_FILE_CONTENT";
        }
        return "UNKNOWN";
    }
} // namespace gfx

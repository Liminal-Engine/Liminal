#include "Status.hpp"

namespace jsonio {
    std::string toStr(const Status &status) {
        switch (status) {
            case Status::OK: return "OK";
            case Status::E_NOK: return "E_NOK";
            case Status::E_PARSING: return "E_PARSING";
            case Status::E_TYPE: return "E_TYPE";
            case Status::E_KEY: return "E_KEY";
            case Status::E_INDEX: return "E_INDEX";
            case Status::E_FILE: return "E_FILE";
            case Status::E_NOT_LOADED: return "E_NOT_LOADED";
            case Status::E_JSON_PATH: return "E_JSON_PATH";
            case Status::E_VALUE_EXISTS: return "E_VALUE_EXISTS";
            case Status::E_KEY_EXISTS: return "E_KEY_EXISTS";
            case Status::E_NO_ROOT_VALUE: return "E_NO_ROOT_VALUE";
        }
        return "UNKNOWN_STATUS";
    }
} // namespace jsonio
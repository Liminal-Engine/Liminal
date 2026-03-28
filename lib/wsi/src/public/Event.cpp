#include "Event.hpp"

namespace wsi {
    bool operator==(const Event &lhs, const Event &rhs) {
        if (lhs.index() != rhs.index()) return false;
        return std::visit([](const auto &a, const auto &b) {
            return a == b;
        }, lhs, rhs);
    }
}
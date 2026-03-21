#include "Axis.hpp"

namespace math {
    std::string toStr(Axis &axis) {
        switch (axis) {
            case Axis::SIDE: return "SIDE";
            case Axis::UP: return "UP";
            case Axis::FRONT: return "FRONT";
            case Axis::ALL: return "ALL";
        }
        return "UNKNOWN";
    }
} // namespace math

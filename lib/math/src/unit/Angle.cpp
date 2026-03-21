#include "unit/Angle.hpp"

namespace math {
    namespace unit {
        std::string toStr(Angle angle) {
            switch (angle) {
                case Angle::RADIANS: return "RADIANS";
                case Angle::DEGREES: return "DEGREES";
            }
            return "UNKNOWN";
        }
    } // namespace unit
} // namespace math
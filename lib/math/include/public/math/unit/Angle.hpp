#ifndef __LIMINAL__LIB__MATH__UNIT__ANGLE_HPP__
#define __LIMINAL__LIB__MATH__UNIT__ANGLE_HPP__

#include <string>

namespace math {
    namespace unit {
        enum class Angle {
            RADIANS,
            DEGREES
        };

        std::string toStr(Angle angle);
    } // namespace unit
} // namespace math


#endif // __LIMINAL__LIB__MATH__UNIT__ANGLE_HPP__
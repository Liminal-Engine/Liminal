#ifndef __LIMINAL__LIB__MATH__AXIS_HPP__
#define __LIMINAL__LIB__MATH__AXIS_HPP__

#include <string>

namespace math {
    enum class Axis {
        SIDE,
        UP,
        FRONT,
        ALL
    };

    std::string toStr(Axis &axis);
} // namespace math


#endif // __LIMINAL__LIB__MATH__AXIS_HPP__
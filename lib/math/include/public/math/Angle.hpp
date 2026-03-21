#ifndef __LIMINAL__LIB__MATH__ANGLE_HPP__
#define __LIMINAL__LIB__MATH__ANGLE_HPP__

#include "unit/Angle.hpp"

#include <memory>

namespace math {
    class Angle {
    public:
        ~Angle();
        static Angle Radians(float value);
        static Angle Degrees(float value);

        float toDegrees(void) const;
        float getValue(void) const;

        Angle operator+(const Angle &other) const;
        Angle operator-(const Angle &other) const;
        Angle operator*(const Angle &other) const;
        Angle operator/(const Angle &other) const;
        Angle operator*(float scalar) const;
        Angle operator/(float scalar) const;

        // Friend operators         
        friend Angle operator*(float scalar, const Angle &angle);
        friend Angle operator/(float scalar, const Angle &angle);

    private:
        explicit Angle(float value);
        class __Impl;
        std::unique_ptr<__Impl> __impl;
    };

} // namespace math


#endif // __LIMINAL__LIB__MATH__ANGLE_HPP__
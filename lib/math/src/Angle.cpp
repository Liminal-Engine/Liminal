#include "Angle.hpp"

#include <cmath>

namespace math {
    class Angle::__Impl {
        private:
            float __value;
        
        public:
            __Impl(float value) : __value(value) {}
            ~__Impl() = default;

            float getValue(void) const { return this->__value; }

            float toDegrees(void) const { return this->__value * (180.0f / M_PI); }
    };

    Angle::Angle(float value) : __impl(std::make_unique<__Impl>(value)) {}
    Angle::~Angle() = default;
    Angle Angle::Radians(float value) { return Angle(value); }
    Angle Angle::Degrees(float value) { return Angle(value * (M_PI / 180.0f)); }

    float Angle::getValue(void) const { return this->__impl->getValue(); }
    float Angle::toDegrees(void) const { return this->__impl->toDegrees(); }

    Angle Angle::operator+(const Angle &other) const { return Angle(this->__impl->getValue() + other.getValue()); }
    Angle Angle::operator-(const Angle &other) const { return Angle(this->__impl->getValue() - other.getValue()); }
    Angle Angle::operator*(const Angle &other) const { return Angle(this->__impl->getValue() * other.getValue()); }
    Angle Angle::operator/(const Angle &other) const { return Angle(this->__impl->getValue() / other.getValue()); }
    Angle Angle::operator*(float scalar) const { return Angle(this->__impl->getValue() * scalar); }
    Angle Angle::operator/(float scalar) const { return Angle(this->__impl->getValue() / scalar); }


    Angle operator*(float scalar, const Angle &angle) { return Angle(angle.getValue() * scalar); }
    Angle operator/(float scalar, const Angle &angle) { return Angle(angle.getValue() / scalar); }
} // namespace math

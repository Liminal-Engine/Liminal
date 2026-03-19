#include "def/Uniform.hpp"

#include <new>

namespace rhi {
    namespace def{
        Uniform::Uniform(const std::string &name, GLint location, GLenum type, const UniformValue &value) :
        name(name), location(location), type(type), value(value)
        {}

        Uniform::Uniform(const Uniform &other) = default;

        Uniform::~Uniform() = default;

        Uniform &Uniform::operator=(const Uniform &other) {
            if (this != &other) {
                this->~Uniform();
                new (this) Uniform(other); // new (ptr) T() allocated to a already allocated memory so no leak possible
            }
            return *this;
        }
    } // namespace def
} // namespace rhi

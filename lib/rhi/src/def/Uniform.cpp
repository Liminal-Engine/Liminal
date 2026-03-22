#include "def/Uniform.hpp"

#include <new>

namespace rhi {
    namespace def{
        Uniform::Uniform(const std::string &name, GLint location, GLenum type, const UniformValue &value) :
        name(name), location(location), type(type), value(value)
        {}
        Uniform::Uniform(const Uniform &other) = default;

        Uniform::~Uniform() = default;

    } // namespace def
} // namespace rhi

#ifndef __LIMINAL__LIB__RHI__DEF__UNIFORM_HPP__
#define __LIMINAL__LIB__RHI__DEF__UNIFORM_HPP__

#include "UniformValue.hpp"

#include <glad/glad.h>

#include <string>

namespace rhi {
    namespace def {
        struct Uniform {
            const std::string name;
            const GLint location;
            const GLenum type;
            UniformValue value;

            Uniform(const std::string &name, GLint location, GLenum type, const UniformValue &value = 0);
            Uniform(const Uniform &other);
            ~Uniform();
        };
    } // namespace def
} // namespace rhi

#endif // __LIMINAL__LIB__RHI__DEF__UNIFORM_HPP__
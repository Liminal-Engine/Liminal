#ifndef __LIMINAL__LIB__RHI__DEF__UNIFORM_HPP__
#define __LIMINAL__LIB__RHI__DEF__UNIFORM_HPP__

#include <string>
#include <cstdint>
#include <glad/glad.h>

namespace rhi {
    namespace def {
        struct Uniform {
            const std::string name;
            const GLint location;
            const GLenum type;

            Uniform(const std::string &name, GLint location, GLenum type);
        };
    } // namespace def
    
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__DEF__UNIFORM_HPP__
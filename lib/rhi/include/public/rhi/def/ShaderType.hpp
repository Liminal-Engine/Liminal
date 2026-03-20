#ifndef __LIMINAL__LIB__RHI__DEF__SHADER_TYPE_HPP__
#define __LIMINAL__LIB__RHI__DEF__SHADER_TYPE_HPP__

#include <glad/glad.h>

#include <string>

namespace rhi {
    namespace def { // FIXME: find a better name for this namespace
        enum class ShaderType {
            VERTEX,
            GEOMETRY,
            FRAGMENT,
            COMPUTE
        };

        std::string toStr(const ShaderType &type) noexcept;
        GLenum toGLenum(const ShaderType &type) noexcept;
    } // namespace def
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__DEF__SHADER_TYPE_HPP__
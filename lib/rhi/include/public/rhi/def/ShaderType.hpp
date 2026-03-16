#ifndef _LIMINAL__LIB__RHI__DEF__SHADER_TYPE_HPP__
#define _LIMINAL__LIB__RHI__DEF__SHADER_TYPE_HPP__

#include <glad/glad.h>

#include <string>


namespace rhi {
    namespace def {
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


#endif // _LIMINAL__LIB__RHI__DEF__SHADER_TYPE_HPP__
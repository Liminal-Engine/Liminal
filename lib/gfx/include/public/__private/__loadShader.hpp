#ifndef __LIMINAL__GFX__PRIVATE__LOAD_SHADER_HPP__
#define __LIMINAL__GFX__PRIVATE__LOAD_SHADER_HPP__

#include "Status.hpp"

#include <fs/Path.hpp>
#include <rhi/def/ShaderType.hpp>

namespace gfx {
    namespace __private {

        std::string __readGLSLSource(const fs::Path &path);

        std::string __findVersionDefinitionLine(const std::vector<std::string> &tokenizedSource);

        std::string __readTypedShaderSource(
            const std::vector<std::string> &tokenizedSource,
            rhi::def::ShaderType shaderType,
            const std::string &versionDefinition
        );

        Status __loadShader(const fs::Path &path);
    } // namespace __private
} // namespace gfx


#endif // __LIMINAL__GFX__PRIVATE__LOAD_SHADER_HPP__
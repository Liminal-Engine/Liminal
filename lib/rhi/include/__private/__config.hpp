#ifndef __LIMINAL__RHI__PRIVATE__CONFIG_HPP__
#define __LIMINAL__RHI__PRIVATE__CONFIG_HPP__

#include <glad/glad.h>
#include <fs/Path.hpp>

namespace rhi {
    namespace __private {
        namespace __config {
            inline constexpr GLsizei OPENGL_INFO_LOG_LENGTH = 2048;
            inline const fs::Path DEFAULT_SHADER_PATH("../assets/shaders");
            inline const fs::Path DEFAULT_TEXTURE_PATH("../assets/textures");
        }
    } // namespace __private
} // namespace rhi


#endif // __LIMINAL__RHI__PRIVATE__CONFIG_HPP__
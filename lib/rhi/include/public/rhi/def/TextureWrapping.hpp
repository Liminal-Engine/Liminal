#ifndef __LIMINAL__RHI__DEF__TEXTURE_WRAPPING_HPP__
#define __LIMINAL__RHI__DEF__TEXTURE_WRAPPING_HPP__

#include <string>

namespace rhi {
    namespace def {
        enum class TextureWrapping {
            REPEAT,
            MIRRORED_REPEAT,
            CLAMP_TO_EDGE,
            CLAMP_TO_BORDER
        };

        std::string toStr(const TextureWrapping &wrapping) noexcept;

    } // namespace def
} // namespace rhi


#endif // __LIMINAL__RHI__DEF__TEXTURE_WRAPPING_HPP__
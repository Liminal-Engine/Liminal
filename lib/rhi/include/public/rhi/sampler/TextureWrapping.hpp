#ifndef __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__SAMPLER__TEXTURE_WRAPPING_HPP__
#define __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__SAMPLER__TEXTURE_WRAPPING_HPP__

namespace rhi {
    namespace sampler {
        enum class TextureWrapping {
            REPEAT,
            MIRRORED_REPEAT,
            CLAMP_TO_EDGE,
            CLAMP_TO_BORDER
        };
    } // namespace sampler
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__SAMPLER__TEXTURE_WRAPPING_HPP__
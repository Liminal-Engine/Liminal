#ifndef __LIMINAL__LIB__RHI__DEF__TEXTURE_FILTERING_HPP__
#define __LIMINAL__LIB__RHI__DEF__TEXTURE_FILTERING_HPP__

#include <string>

namespace rhi {
    namespace def {
        enum class TextureFiltering {
            NEAREST,
            LINEAR
        };

        std::string toStr(const TextureFiltering &filtering) noexcept;

    } // namespace def
} // namespace rhi

#endif // __LIMINAL__LIB__RHI__DEF__TEXTURE_FILTERING_HPP__
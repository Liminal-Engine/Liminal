#ifndef __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__TEXTURE_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__TEXTURE_HPP__

#include "Status.hpp"

#include <fs/Path.hpp>
#include <rhi/def/Handle.hpp>
#include <rhi/resource/Texture.hpp>

#include <glm/glm.hpp>

#include <memory>

namespace gfx {
    namespace __private {
        namespace __asset {
            class __Texture {
                public:
                    __Texture(void);
                    ~__Texture();

                    __Texture(const __Texture&) = delete;            // No copy
                    __Texture& operator=(const __Texture&) = delete; // No affectation
                    __Texture(__Texture&&) noexcept;                 // No move
                    __Texture& operator=(__Texture&&) noexcept;      // No affectation by moving

                    Status load(const fs::Path &path);
                    const fs::Path &getPath(void) const;

                    const unsigned char *getData(void) const;
                    const glm::ivec2 &getSize(void) const;
                    int getNChannels(void) const;

                    void bind(const rhi::resource::Texture *rhiTexture);
                    rhi::def::Handle getRHIHandle(void) const;

                    Status copy(const __Texture &other);

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;   
            };     
        } // namespace __asset
    } // namespace __private
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__TEXTURE_HPP__
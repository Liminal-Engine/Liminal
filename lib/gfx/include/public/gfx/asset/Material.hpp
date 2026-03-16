#ifndef __LIMINAL__LIB__GFX__INCLUDE__PUBLIC__ASSET__MATERIAL_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__PUBLIC__ASSET__MATERIAL_HPP__

#include "../Status.hpp" // FIXME

#include <fs/Path.hpp>
#include <rhi/def/Handle.hpp>
#include <rhi/def/ShaderType.hpp> // FIXME : not expose rhi here, use forward declaration instead

#include <memory>

#include <glm/glm.hpp>

namespace gfx {
    namespace asset {
        class Material {
            public:
                Material(void);
                ~Material();

                Material(const Material &) = delete;
                Material &operator=(const Material &) = delete;
                Material(Material &&) noexcept;
                Material &operator=(Material &&) noexcept;

                [[nodiscard]] Status setColor(const glm::vec3 &color);
                const std::string &getRessourceKey(void) const;
                Status copy(const Material &other);

                Status load(const fs::Path &texturePath);

                const unsigned char *getTextureData(void) const;
                const glm::ivec2 &getTextureSize(void) const;
                int getTextureNChannels(void) const;

                Status setTextureRHIHandle(rhi::def::Handle RHIHandle);
                Status setShaderRHIHandle(rhi::def::Handle RHIHandle);

                rhi::def::Handle getTextureRHIHandle(void) const;
                rhi::def::Handle getShaderRHIHandle(void) const;

                const std::string &getShaderSource(rhi::def::ShaderType type) const;

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };     
    } // namespace asset
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__INCLUDE__PUBLIC__ASSET__MATERIAL_HPP__

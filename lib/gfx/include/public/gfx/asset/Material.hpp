#ifndef __LIMINAL__LIB__GFX__INCLUDE__PUBLIC__ASSET__MATERIAL_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__PUBLIC__ASSET__MATERIAL_HPP__

#include "../Status.hpp" // FIXME

#include <fs/Path.hpp>
#include <rhi/def/Handle.hpp>
#include <rhi/def/ShaderType.hpp> // FIXME : not expose rhi here, use forward declaration instead
#include <rhi/resource/Texture.hpp>
#include <rhi/resource/Shader.hpp>

#include <memory>

#include <glm/glm.hpp>

// forward declarations

namespace gfx {
    namespace __private {
        namespace __asset {
            class __Texture;
            class __Shader;
        }
    }
}


//

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

                Status copy(const Material &other);

                Status load(const fs::Path &path);
                const fs::Path &getPath(void) const;

                const unsigned char *getTextureData(void) const;
                const glm::ivec2 &getTextureSize(void) const;
                int getTextureNChannels(void) const;

                // fixme: GET SHADER and getResouce instead
                rhi::def::Handle getTextureRHIHandle(void) const;
                rhi::def::Handle getShaderRHIHandle(void) const;

                bool mustHaveTexture(void) const;
                const fs::Path &getTexturePath(void) const;

                void bind(__private::__asset::__Texture *texture, __private::__asset::__Shader *shader);

                // void setTexture(const __private::__asset::__Texture *texture);
                // void setShader(const __private::__asset::__Shader *shader);

                const std::vector<rhi::def::Uniform> &apply(void) const;



            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };     
    } // namespace asset
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__INCLUDE__PUBLIC__ASSET__MATERIAL_HPP__

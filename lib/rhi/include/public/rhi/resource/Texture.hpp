#ifndef __LIMINAL__LIB_RHI__INCLUDE__PUBLIC__RESOURCE__TEXTURE_HPP__
#define __LIMINAL__LIB_RHI__INCLUDE__PUBLIC__RESOURCE__TEXTURE_HPP__

#include <fs/Path.hpp>

#include <rhi/def/Handle.hpp>

#include <memory>

#include <glm/glm.hpp>

namespace rhi {
    namespace resource {
        class Texture {
            public:
                Texture(                    
                    const unsigned char *data,
                    const glm::ivec2 &size,
                    int nChannels,
                    def::Handle handle
                );
                ~Texture();

                Texture(const Texture&) = delete;            // No copy
                Texture& operator=(const Texture&) = delete; // No affectation
                Texture(Texture&&) = delete;                 // No move
                Texture& operator=(Texture&&) = delete;      // No affectation by moving

                def::Handle getRHIHandle(void) const;
    
            private:
    
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace resource
    
} // namespace rhi


#endif // __LIMINAL__LIB_RHI__INCLUDE__PUBLIC__RESOURCE__TEXTURE_HPP__
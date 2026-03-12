#ifndef __LIMINAL__LIB_RHI__INCLUDE__PUBLIC__RESOURCE__TEXTURE_HPP__
#define __LIMINAL__LIB_RHI__INCLUDE__PUBLIC__RESOURCE__TEXTURE_HPP__

#include <fs/Path.hpp>

#include <memory>

namespace rhi {
    namespace resource {
        class Texture {
            public:
                Texture(const fs::Path &path);
                ~Texture();

                Texture(const Texture&) = delete;            // No copy
                Texture& operator=(const Texture&) = delete; // No affectation
                Texture(Texture&&) = delete;                 // No move
                Texture& operator=(Texture&&) = delete;      // No affectation by moving
    
            private:
    
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace resource
    
} // namespace rhi


#endif // __LIMINAL__LIB_RHI__INCLUDE__PUBLIC__RESOURCE__TEXTURE_HPP__
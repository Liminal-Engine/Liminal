#ifndef __LIMINAL__LIB__GFX__TEXTURE_HPP__
#define __LIMINAL__LIB__GFX__TEXTURE_HPP__

#include "gfx/Status.hpp"
#include "IAsset.hpp"

#include <fs/Path.hpp>

#include <memory>

namespace gfx {
    namespace asset {
        class Texture : public IAsset {
            public:
                Texture(void);
                ~Texture();
    
                Status load(const fs::Path &path);
                bool isLoaded(void) const;
    
            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace asset
    
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__TEXTURE_HPP__
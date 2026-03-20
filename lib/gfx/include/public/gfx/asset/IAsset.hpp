#ifndef __LIMINAL__LIB__GFX__ASSET__I_ASSET_HPP__
#define __LIMINAL__LIB__GFX__ASSET__I_ASSET_HPP__

#include "gfx/Status.hpp"

#include <fs/Path.hpp>

namespace gfx {
    namespace asset {
        class IAsset {
            public:
                IAsset(void);
                virtual ~IAsset();
    
                virtual Status load(const fs::Path &path) = 0;
                virtual bool isLoaded(void) const = 0;
    
        };
    } // namespace asset
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__ASSET__I_ASSET_HPP__
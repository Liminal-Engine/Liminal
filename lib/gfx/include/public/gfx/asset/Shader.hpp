#ifndef __LIMINAL__LIB__GFX__SHADER_HPP__
#define __LIMINAL__LIB__GFX__SHADER_HPP__

#include "gfx/Status.hpp"
#include "IAsset.hpp"

#include <fs/Path.hpp>

#include <memory>

namespace gfx {
    namespace asset {
        class Shader : public IAsset {
            public:
                Shader(void);
                ~Shader();
    
                Status load(const fs::Path &path);
                bool isLoaded(void) const;
                void use(void) const;
    
            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace asset
    
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__SHADER_HPP__
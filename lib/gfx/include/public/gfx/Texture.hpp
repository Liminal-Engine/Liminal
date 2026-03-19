#ifndef __LIMINAL__LIB__GFX__TEXTURE_HPP__
#define __LIMINAL__LIB__GFX__TEXTURE_HPP__

#include <fs/Path.hpp>

#include <memory>

namespace gfx {
    class Texture {
        public:
            Texture(const fs::Path &path);
            ~Texture();
        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__TEXTURE_HPP__
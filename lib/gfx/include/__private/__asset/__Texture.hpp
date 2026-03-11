#ifndef __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__TEXTURE_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__TEXTURE_HPP__

#include <memory>

namespace gfx {
    namespace __private {
        namespace __asset {
            class __Texture {
                public:
                    __Texture(void);
                    ~__Texture();

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;   
            };     
        } // namespace __asset
    } // namespace __private
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__TEXTURE_HPP__
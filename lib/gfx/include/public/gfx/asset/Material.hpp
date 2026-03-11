#ifndef __LIMINAL__LIB__GFX__INCLUDE__PUBLIC__ASSET__MATERIAL_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__PUBLIC__ASSET__MATERIAL_HPP__

#include <memory>

namespace gfx {
    namespace asset {
        class Material {
            public:
                Material(void);
                ~Material();

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };     
    } // namespace asset
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__INCLUDE__PUBLIC__ASSET__MATERIAL_HPP__
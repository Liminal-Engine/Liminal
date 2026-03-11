#ifndef __LIMINAL__LIB__GFX__INCLUDE__ASSET__MESH_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__ASSET__MESH_HPP__

#include <memory>

namespace gfx {
    namespace asset {
        class Mesh {
            public:
                Mesh(void);
                ~Mesh();
            
            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace asset
} // namespace gfx

#endif // __LIMINAL__LIB__GFX__INCLUDE__ASSET__MESH_HPP__
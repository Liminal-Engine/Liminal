#ifndef __LIMINAL__LIB__GFX__MESH_HPP__
#define __LIMINAL__LIB__GFX__MESH_HPP__

#include <fs/Path.hpp>

#include <memory>

namespace gfx {
    class Mesh {
        public:
            Mesh(const fs::Path &path);
            ~Mesh();

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__MESH_HPP__
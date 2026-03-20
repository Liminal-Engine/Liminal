#ifndef __LIMINAL__GFX__PRIVATE__LOAD_MESH_HPP__
#define __LIMINAL__GFX__PRIVATE__LOAD_MESH_HPP__

#include "Status.hpp"

#include <fs/Path.hpp>

namespace gfx {
    namespace __private {
        Status __loadMesh(const fs::Path &path);
    } // namespace __private
} // namespace gfx


#endif // __LIMINAL__GFX__PRIVATE__LOAD_MESH_HPP__
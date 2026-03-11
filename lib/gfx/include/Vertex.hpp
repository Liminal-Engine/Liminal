#ifndef __LIMINAL__LIB__GFX__INCLUDE__VERTEX_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__VERTEX_HPP__

#include <glm/glm.hpp>

namespace gfx {
    struct Vertex {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
    };
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__INCLUDE__VERTEX_HPP__
#ifndef __LIMINAL__LIB__RHI__DEF__VERTEX_HPP__
#define __LIMINAL__LIB__RHI__DEF__VERTEX_HPP__

#include <glm/glm.hpp>

namespace rhi {
    namespace def {
        struct Vertex {
            glm::vec3 position;
            glm::vec2 uv;
            glm::vec3 normal;
        };     
    } // namespace def
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__DEF__VERTEX_HPP__
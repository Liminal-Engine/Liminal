#ifndef __LIMINAL__LIB__RHI__DEF__VERTEX_HPP__
#define __LIMINAL__LIB__RHI__DEF__VERTEX_HPP__

#include <glm/glm.hpp>

namespace rhi {
    namespace def {
        struct Vertex {
            glm::vec3 position;
            glm::vec3 normal;
            glm::vec2 uv;
            Vertex(
                const glm::vec3 &position,
                const glm::vec3 &normal = glm::vec3(0.0f),
                const glm::vec2 &uv = glm::vec2(0.0f)
            );
        };
    } // namespace def
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__DEF__VERTEX_HPP__
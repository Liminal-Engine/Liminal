#ifndef __LIMINAL__LIB__ENTITY__COMPONENT__TRANSFORM_HPP__
#define __LIMINAL__LIB__ENTITY__COMPONENT__TRANSFORM_HPP__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace entity {
    namespace component {
        struct Transform {
            Transform(void);

            glm::vec3 position;
            glm::vec3 orientation;
            glm::vec3 scale;
            glm::mat4 model;
        };     
    } // namespace component
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__COMPONENT__TRANSFORM_HPP__
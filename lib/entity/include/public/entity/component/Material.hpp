#ifndef __LIMINAL__LIB__ENTITY__COMPONENT__MATERIAL_HPP__
#define __LIMINAL__LIB__ENTITY__COMPONENT__MATERIAL_HPP__

#include <glm/glm.hpp>

namespace entity {
    namespace component {
        struct Material {
            Material(void);

            glm::vec3 color;
        };
    } // namespace component
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__COMPONENT__MATERIAL_HPP__
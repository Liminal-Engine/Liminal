#ifndef __LIMINAL__LIB__ENTITY__COMPONENT__CAMERA_HPP__
#define __LIMINAL__LIB__ENTITY__COMPONENT__CAMERA_HPP__

#include "entity/component/Transform.hpp"

#include <math/Angle.hpp>

#include <glm/glm.hpp>

namespace entity {
    namespace component {
        struct CameraSettings {
            CameraSettings(void);

            struct AspectRatio {
                AspectRatio(void);
                float getCoefficient(void) const;
                float width;
                float height;
            };

            enum class ProjectionMode {
                PERSPECTTIVE,
                ORTOGRAPHIC
            };

            glm::vec3 target;
            glm::vec3 direction;
            glm::vec3 right;
            glm::vec3 up;
            float translationSpeed;
            float rotationSpeed;
            math::Angle FOV;
            AspectRatio aspectRatio;
            float nearPlane;
            float farPlane;
            ProjectionMode projectionMode;
            glm::mat4 viewMatrix;
            glm::mat4 projectionMatrix;

            void update(const component::Transform &relatedTransform);
        };
    } // namespace component
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__COMPONENT__CAMERA_HPP__
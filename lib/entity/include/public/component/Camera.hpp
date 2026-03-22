#ifndef __LIMINAL__LIB__ENTITY__COMPONENT__CAMERA_HPP__
#define __LIMINAL__LIB__ENTITY__COMPONENT__CAMERA_HPP__

#include "component/Transform.hpp"

#include <memory>
#include <string>

namespace entity {
    namespace component {
        class Camera {
            public:

                struct AspectRatio {
                    float width;
                    float height;
                    AspectRatio(float width, float height);
                    float getCoefficient(void) const;
                };

                enum class ProjectionMode {
                    PERSPECTTIVE,
                    ORTOGRAPHIC
                };

                Camera(const Transform &transformComponent);
                ~Camera();

                const glm::mat4 &getViewMatrix(void) const;
                const glm::mat4 &getProjectionMatrix(void) const;

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };     
    } // namespace component

    std::string toStr(component::Camera::ProjectionMode projectionMode) noexcept;

} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__COMPONENT__CAMERA_HPP__
#include "component/Camera.hpp"

#include <math/Angle.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace entity {
    namespace component {
        class Camera::__Impl {
            private:
                const Transform &__transform;

                glm::vec3 __target;
                glm::vec3 __direction;
                glm::vec3 __right;
                glm::vec3 __up;
                float __translationSpeed;
                float __rotationSpeed;
                math::Angle __yaw; // FIXME: must be in transform
                math::Angle __pitch; // FIXME: must be in transform
                math::Angle __roll; // FIXME: must be in transform
                math::Angle __FOV;
                AspectRatio __aspectRatio;
                float __nearPlane;
                float __farPlane;
                ProjectionMode __projectionMode;
                mutable glm::mat4 __viewMatrix;
                mutable glm::mat4 __projectionMatrix;


            public:
                __Impl(const Transform &transformComponent) :
                __transform(transformComponent),
                __target(0.0f),
                __direction(glm::normalize(this->__transform.getPosition() - this->__target)),
                __right(glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), this->__direction))),
                __up(glm::cross(this->__direction, this->__right)),
                __translationSpeed(10.0f),
                __rotationSpeed(0.5f),
                __yaw(math::Angle::Degrees(-90.0f)),
                __pitch(math::Angle::Degrees(0.0f)),
                __roll(math::Angle::Degrees(0.0f)),
                __FOV(math::Angle::Degrees(45.0f)),
                __aspectRatio(AspectRatio(16, 9)),
                __nearPlane(0.1f),
                __farPlane(1'000.0f),
                __projectionMode(ProjectionMode::PERSPECTTIVE),
                __viewMatrix(glm::lookAt(this->__transform.getPosition(), this->__target, this->__up)),
                __projectionMatrix(glm::perspective(this->__FOV.getValue(), this->__aspectRatio.getCoefficient(), this->__nearPlane, this->__farPlane))
                {}

                ~__Impl() = default;

                const glm::mat4 &getViewMatrix(void) const {
                    return (this->__viewMatrix = glm::lookAt(this->__transform.getPosition(), this->__target, this->__up));
                }

                const glm::mat4 &getProjectionMatrix(void) const { // FIXME: use other projection mode as well
                    return (this->__projectionMatrix = glm::perspective(this->__FOV.getValue(), this->__aspectRatio.getCoefficient(), this->__nearPlane, this->__farPlane));
                }

        };

        Camera::AspectRatio::AspectRatio(float width, float height) : width(width), height(height) {}
        float Camera::AspectRatio::getCoefficient(void) const { return this->width / this->height; }

        Camera::Camera(const Transform &transformComponent) : __impl(std::make_unique<__Impl>(transformComponent)) {}
        Camera::~Camera() = default;
    } // namespace component

    std::string toStr(component::Camera::ProjectionMode projectionMode) noexcept {
        switch (projectionMode) {
            case component::Camera::ProjectionMode::PERSPECTTIVE: return "PERSPECTTIVE";
            case component::Camera::ProjectionMode::ORTOGRAPHIC: return "ORTOGRAPHIC";
        }
        return "UNKNOWN";
    };

} // namespace entity

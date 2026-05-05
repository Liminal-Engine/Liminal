#include "bundle/Camera.hpp"

namespace entity {
    namespace bundle {
        Camera::Camera(
            entt::entity id,
            component::Transform &transform,
            component::CameraSettings &settings
        ) :
        id(id),
        transform(transform),
        settings(settings),
        cameraTag()
        {}

        bool Camera::isNull(void) { return this->id == entt::null; }

        Camera Camera::Null(void) {
            static entity::component::Transform nullTransform;
            static entity::component::CameraSettings nullCameraSettings;
            return Camera(
                entt::null,
                nullTransform,
                nullCameraSettings
            );
        }

    } // namespace bundle
} // namespace entity

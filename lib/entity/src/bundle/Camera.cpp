#include "bundle/Camera.hpp"

namespace entity {
    namespace bundle {
        Camera::Camera(
            component::Transform &transfom,
            component::CameraSettings &settings
        ) :
        transfom(transfom),
        settings(settings),
        cameraTag()
        {}

    } // namespace bundle
} // namespace entity

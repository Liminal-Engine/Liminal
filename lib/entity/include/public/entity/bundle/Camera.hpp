#ifndef __LIMINAL__LIB__ENTITY__BUNDLE__CAMERA_HPP__
#define __LIMINAL__LIB__ENTITY__BUNDLE__CAMERA_HPP__

#include "entity/component/Transform.hpp"
#include "entity/component/CameraSettings.hpp"
#include "entity/component/tag/Camera.hpp"

#include <entt/entt.hpp>

namespace entity {
    namespace bundle {
        struct Camera {
            Camera(
                entt::entity id,
                component::Transform &transform,
                component::CameraSettings &settings
            );

            static Camera Null(void);
            bool isNull(void);

            entt::entity id;
            component::Transform &transform;
            component::CameraSettings &settings;
            component::tag::Camera cameraTag;
        };
    } // namespace bundle
} // namespace entity

#endif // __LIMINAL__LIB__ENTITY__BUNDLE__CAMERA_HPP__
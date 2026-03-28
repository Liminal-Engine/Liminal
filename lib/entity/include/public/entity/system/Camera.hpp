#ifndef __LIMINAL__LIB__ENTITY__SYSTEM__CAMERA_HPP__
#define __LIMINAL__LIB__ENTITY__SYSTEM__CAMERA_HPP__

#include <math/Axis.hpp>
#include <math/Angle.hpp>

#include <entt/entt.hpp>

namespace entity {
    namespace system {
        class Camera {
            public:
                static void update(void);
                static void activate(entt::entity id);
                static void translate(math::Axis axis, float delta);
                static void rotate(math::Axis axis, const math::Angle &angle);
        };      
    } // namespace system
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__SYSTEM__CAMERA_HPP__
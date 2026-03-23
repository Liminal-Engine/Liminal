#ifndef __LIMINAL__LIB__ENTITY__BUNDLE__OBJECT_HPP__
#define __LIMINAL__LIB__ENTITY__BUNDLE__OBJECT_HPP__

#include "entity/component/Geometry.hpp"
#include "entity/component/Material.hpp"
#include "entity/component/Transform.hpp"
#include "entity/component/tag/Object.hpp"

namespace entity {
    namespace bundle {
        struct Object {
            Object(
                component::Geometry &geometry,
                component::Material &material,
                component::Transform &transform
            );

            component::Geometry &geometry;
            component::Material &material;
            component::Transform &transform;
            component::tag::Object objectTag;
        };     
    } // namespace bundle
} // namespace entity

#endif // __LIMINAL__LIB__ENTITY__BUNDLE__OBJECT_HPP__
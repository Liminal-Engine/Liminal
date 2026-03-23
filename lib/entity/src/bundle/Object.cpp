#include "bundle/Object.hpp"

namespace entity {
    namespace bundle {
        Object::Object(
            component::Geometry &geometry,
            component::Material &material,
            component::Transform &transform
        ) :
        geometry(geometry),
        material(material),
        transform(transform)
        {}
    } // namespace bundle
} // namespace entity

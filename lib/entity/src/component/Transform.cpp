#include "entity/component/Transform.hpp"


namespace entity {
    namespace component {
        Transform::Transform(void) :
        position(0.0f), orientation(0.0f), scale(1.0f), model(1.0f)
        {}
    } // namespace component
} // namespace entity

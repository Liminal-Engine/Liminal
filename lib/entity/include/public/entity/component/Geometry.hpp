#ifndef __LIMINAL__LIB__ENTITY__COMPONENT__GEOMETRY_HPP__
#define __LIMINAL__LIB__ENTITY__COMPONENT__GEOMETRY_HPP__

#include <gfx/def/Handle.hpp>

namespace entity {
    namespace component {
        struct Geometry {
            Geometry(void);

            gfx::def::Handle meshHandle;
        };
    } // namespace component
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__COMPONENT__GEOMETRY_HPP__
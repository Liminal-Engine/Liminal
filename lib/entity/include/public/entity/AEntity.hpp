#ifndef __LIMINAL__LIB__ENTITY__A_ENTITY_HPP__
#define __LIMINAL__LIB__ENTITY__A_ENTITY_HPP__

#include "Status.hpp"
#include "component/Geometry.hpp"
#include "gfx/def/Handle.hpp"

#include <string>
#include <cstdint>

namespace entity {

    using RessourceHandle = uint32_t;

    class AEntity {
        public:
            AEntity(gfx::def::Handle geometryHandle);
            virtual ~AEntity();
            AEntity(const AEntity &) = delete;
            AEntity &operator=(const AEntity &) = delete;
            AEntity(AEntity &&other) noexcept;
            AEntity &operator=(AEntity &&other) noexcept;

            component::Geometry geometry;
    };
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__A_ENTITY_HPP__
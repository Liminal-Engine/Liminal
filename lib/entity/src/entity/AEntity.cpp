#include "AEntity.hpp"

#include <logger/logger.hpp>

#include <type_traits>

namespace entity {

    AEntity::AEntity(AEntity &&other) noexcept = default;
    AEntity &AEntity::operator=(AEntity &&other) noexcept = default;

    AEntity::AEntity(gfx::def::Handle geometryHandle) :
    geometry(geometryHandle),
    transform(),
    material()
    {}
    
    AEntity::~AEntity() = default;
} // namespace entity

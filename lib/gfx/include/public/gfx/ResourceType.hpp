#ifndef __LIMINAL__GFX__RESOURCE_TYPE_HPP__
#define __LIMINAL__GFX__RESOURCE_TYPE_HPP__

#include "Status.hpp"
#include "ResourceType.hpp"

#include <string>

namespace gfx {
    enum class ResourceType { // fixme: move to def namespace
        MESH,
        SHADER
    };

    std::string toStr(const ResourceType &resourceType) noexcept;
} // namespace gfx


#endif // __LIMINAL__GFX__RESOURCE_TYPE_HPP__
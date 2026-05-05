#ifndef __LIMINAL__GFX__DEF__RESOURCE_TYPE_HPP__
#define __LIMINAL__GFX__DEF__RESOURCE_TYPE_HPP__

#include "Status.hpp"
#include "ResourceType.hpp"

#include <string>

namespace gfx {
    namespace def {
        enum class ResourceType {
            MESH,
            SHADER
        };        
    } // namespace def
    

    std::string toStr(def::ResourceType resourceType) noexcept;
} // namespace gfx


#endif // __LIMINAL__GFX__DEF__RESOURCE_TYPE_HPP__
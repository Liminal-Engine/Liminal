#ifndef __LIMINAL__RHI__RESOURCE__RESOURCE_TYPE_HPP__
#define __LIMINAL__RHI__RESOURCE__RESOURCE_TYPE_HPP__

#include "resource/Mesh.hpp"
#include "resource/Shader.hpp"

#include <variant>

namespace rhi {
    namespace resource {
        using ResourceType = std::variant<
            resource::Mesh,
            resource::Shader
        >;
    } // namespace resource
} // namespace rhi


#endif // __LIMINAL__RHI__RESOURCE__RESOURCE_TYPE_HPP__
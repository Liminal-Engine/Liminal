#ifndef __LIMINAL__LIB__RHI__DEF__UNIFORM_VALUE_HPP__
#define __LIMINAL__LIB__RHI__DEF__UNIFORM_VALUE_HPP__

#include <variant>

#include <glm/glm.hpp>

namespace rhi {
    namespace def {
        using UniformValue = std::variant<
            int,
            float,
            glm::vec3
        >;
    } // namespace def
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__DEF__UNIFORM_VALUE_HPP__
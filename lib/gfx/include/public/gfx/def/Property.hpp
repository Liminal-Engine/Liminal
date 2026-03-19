#ifndef __LIMINAL__LIB__GFX__DEF__PROPERTY_HPP__
#define __LIMINAL__LIB__GFX__DEF__PROPERTY_HPP__

#include <variant>

#include <glm/glm.hpp>

namespace gfx {
    namespace def {
        using Property = std::variant<
            glm::vec3
        >;
    } // namespace def
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__DEF__PROPERTY_HPP__
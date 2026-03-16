#ifndef __LIMINAL_LIB__GFX__DEF__MANAGED_ASSET_HPP__
#define __LIMINAL_LIB__GFX__DEF__MANAGED_ASSET_HPP__

#include "../asset/Mesh.hpp" // FIXME
#include "../asset/Material.hpp" // FIXME

#include <type_traits>

namespace gfx {
    namespace def {
        template<typename T>
        concept ManagedAsset = std::is_same_v<T, asset::Mesh> || std::is_same_v<T, asset::Material>;
    } // namespace def
} // namespace gfx


#endif // __LIMINAL_LIB__GFX__DEF__MANAGED_ASSET_HPP__
#ifndef __LIMINAL__GFX__ASSET__ASSET_TYPE_HPP__
#define __LIMINAL__GFX__ASSET__ASSET_TYPE_HPP__

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

#include <concepts>

namespace gfx {
    namespace asset {
        template<typename T>
        concept AssetType = 
            std::same_as<T, asset::Mesh> ||
            std::same_as<T, asset::Shader> ||
            std::same_as<T, asset::Texture>;

    } // namespace asset
} // namespace gfx

#endif // __LIMINAL__GFX__ASSET__ASSET_TYPE_HPP__
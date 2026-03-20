#ifndef __LIMINALL_LIB__GFX__ASSET_REGISTRY_HPP__
#define __LIMINALL_LIB__GFX__ASSET_REGISTRY_HPP__

#include "Status.hpp"
#include "asset/AssetType.hpp"

#include <fs/Path.hpp>

#include <memory>

namespace gfx {
    class AssetRegistry {
        public:
            AssetRegistry(const AssetRegistry&) = delete;
            AssetRegistry(AssetRegistry&&) = delete;
            AssetRegistry &operator=(const AssetRegistry&) = delete;
            AssetRegistry &operator=(AssetRegistry&&) = delete;

            template<asset::AssetType T>
            static Status load(const fs::Path &path);
            template<asset::AssetType T>
            static bool exists(const std::string &name);
            template<asset::AssetType T>
            static const T *get(const std::string &name);

        private:
            AssetRegistry(void);
            ~AssetRegistry();
            static AssetRegistry &__instance(void);
        

            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace gfx


#endif // __LIMINALL_LIB__GFX__ASSET_REGISTRY_HPP__
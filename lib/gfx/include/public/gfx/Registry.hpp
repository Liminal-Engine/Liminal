#ifndef __LIMINAL__LB__GFX__REGISTRY_HPP__
#define __LIMINAL__LB__GFX__REGISTRY_HPP__

#include "Status.hpp"
#include "asset/Mesh.hpp"
#include "asset/Material.hpp"
#include "def/ManagedAsset.hpp"
#include "def/Property.hpp"

#include <rhi/Registry.hpp>
#include <fs/Path.hpp>

#include <memory>

namespace gfx {
    class Registry {
        public:
            Registry(rhi::Registry &rhiRegistry);
            ~Registry();

            template<def::ManagedAsset T>
            [[nodiscard]] Status load(const std::string &name, const fs::Path &path);

            template<def::ManagedAsset T>
            [[nodiscard]] bool exists(const std::string &name) const;

            template<def::ManagedAsset T>
            [[nodiscard]] const T *get(const std::string &name) const;

            template<def::ManagedAsset T>
            [[nodiscard]] Status set(const std::string &asset, const std::string &property, const def::Property &value);

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace gfx

#endif // __LIMINAL__LB__GFX__REGISTRY_HPP__
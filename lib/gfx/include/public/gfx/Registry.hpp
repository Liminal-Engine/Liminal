#ifndef __LIMINAL__LB__GFX__REGISTRY_HPP__
#define __LIMINAL__LB__GFX__REGISTRY_HPP__

#include "Status.hpp"
#include "asset/Mesh.hpp"
#include "asset/Material.hpp"

#include <rhi/Registry.hpp>
#include <fs/Path.hpp>

#include <memory>

namespace gfx {
    class Registry {
        public:
            Registry(rhi::Registry &rhiRegistry);
            ~Registry();

            [[nodiscard]] Status loadMesh(const std::string &name, const fs::Path &path);
            // [[nodiscard]] Status add(const std::string &name, asset::Mesh &&mesh);
            // [[nodiscard]] Status add(const std::string &name, asset::Material &&material);

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace gfx

#endif // __LIMINAL__LB__GFX__REGISTRY_HPP__
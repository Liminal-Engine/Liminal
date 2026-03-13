#include "Registry.hpp"
#include "__private/__registry/__Mesh.hpp"
#include "__private/__registry/__Material.hpp"

#include <logger/logger.hpp>

#include <utility>

namespace gfx {

    class Registry::__Impl {
        private:
            rhi::Registry &__rhiRegistry;
            __private::__registry::__Mesh __meshRegistry;
            __private::__registry::__Material __materialRegistry;

        public:
            __Impl(rhi::Registry &rhiRegistry) :
            __rhiRegistry(rhiRegistry),
            __meshRegistry(),
            __materialRegistry()
            {}

            ~__Impl() = default;

            // Status add(const std::string &name, asset::Mesh &&mesh) {
            //     return this->__meshRegistry.add(name, std::move(mesh));
            // }

            // Status add(const std::string &name, asset::Material &&material) {
            //     return this->__materialRegistry.add(name, std::move(material));
            // }

            Status loadMesh(const std::string &name, const fs::Path &path) {
                // 1. If already exists, do nothing
                if (this->__meshRegistry.exists(name)) {
                    logger::error << "Failed to load new mesh: name\"" << name << "\" already exists" << std::endl;
                    return Status::E_ALREADY_EXISTS;
                }
                logger::debug << "Loading mesh asset with name: " << name << ", path: " << path.asStr() << std::endl;
                // 2. We always identify the resource by it's key, which is the path's string:
                std::string resourceKey(path.asStr());
                // 3. We create the new asset
                gfx::asset::Mesh newMeshAsset;
                // 4. We check if the asset already exists
                const gfx::asset::Mesh *existingMeshAsset = this->__meshRegistry.getByPath(path);
                // 5. If it exists, then we must create a new asset but copy it's data
                if (existingMeshAsset != nullptr) {
                    newMeshAsset.copy(*existingMeshAsset);
                } else { // If 6. it don't exists, then we must load it from a file and add it to the gfx mesh registry
                    // 6.1 Load from file
                    newMeshAsset.load(path);
                    // 6.2 Create the corresponding rhi resource if it don't exists
                    const rhi::resource::Mesh *rhiMeshResource = this->__rhiRegistry.getMesh(resourceKey);
                    if (rhiMeshResource == nullptr) { // if the rhi mesh resource don't exists, create it
                        this->__rhiRegistry.addMesh(resourceKey, newMeshAsset.getVertices(), newMeshAsset.getIndices());                        
                        // 6.3 Update the local rhi mesh resource by retrieving it again
                        rhiMeshResource = this->__rhiRegistry.getMesh(resourceKey);
                    }
                    // 6.4 Update the new mesh asset by setting it's rhi resource
                    newMeshAsset.setResource(rhiMeshResource);
                }
                // 7. Add the gfx mesh asset to the gfx mesh asset registry
                this->__meshRegistry.add(name, std::move(newMeshAsset));
                return Status::OK;
            }
    };

    Registry::Registry(rhi::Registry &rhiRegistry) :
    __impl(std::make_unique<__Impl>(rhiRegistry))
    {}

    Registry::~Registry() = default;

    // Status Registry::add(const std::string &name, asset::Mesh &&mesh) { return this->__impl->add(name, std::move(mesh)); }
    // Status Registry::add(const std::string &name, asset::Material &&material) { return this->__impl->add(name, std::move(material)); }
    Status Registry::loadMesh(const std::string &name, const fs::Path &path) { return this->__impl->loadMesh(name, path); }
} // namespace gfx

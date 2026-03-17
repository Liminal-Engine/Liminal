#include "Registry.hpp"
#include "__private/__registry/__Mesh.hpp"
#include "__private/__registry/__Material.hpp"

#include <logger/logger.hpp>
#include <rhi/def/ShaderType.hpp>

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

            template<def::ManagedAsset T>
            Status load(const std::string &name, const fs::Path &path);
            
            template<def::ManagedAsset T>
            bool exists(const std::string &name) const;

            template<def::ManagedAsset T>
            const T *get(const std::string &name) const;

    };

    template<>
    Status Registry::__Impl::load<asset::Mesh>(const std::string &name, const fs::Path &path) {
        // 1. If already exists, do nothing
        if (this->__meshRegistry.exists(name)) {
            logger::error << "Failed to load new mesh: name\"" << name << "\" already exists" << std::endl;
            return Status::E_ALREADY_EXISTS;
        }
        logger::debug << "Loading mesh asset with name: " << name << ", path: " << path.asStr() << std::endl;
        // 2. We always identify the resource by it's key, which is the path's string:
        std::string resourceKey(path.asStr()); // FIXME : serialize resource keys for all kinds of resource
        // 3. We create the new asset
        gfx::asset::Mesh newMeshAsset;
        // 4. We check if the asset already exists
        const gfx::asset::Mesh *existingMeshAsset = this->__meshRegistry.getByPath(path);
        // 5. If it exists, then we must create a new asset but copy it's data
        if (existingMeshAsset != nullptr) {
            newMeshAsset.copy(*existingMeshAsset);
        } else { // If 6. it don't exists, then we must load it from a file and add it to the gfx mesh registry and also add resources to the rhi registry
            // 6.1 Load from file
            newMeshAsset.load(path);
            // 6.2 Create the corresponding rhi resource if it don't exists
            rhi::def::Handle rhiMeshHandle = this->__rhiRegistry.getMeshHandle(resourceKey);
            if (rhiMeshHandle == rhi::def::NULL_HANDLE) { // if the rhi mesh resource don't exists, create it
                this->__rhiRegistry.addMesh(resourceKey, newMeshAsset.getVertices(), newMeshAsset.getIndices());                        
                // 6.3 Update the local rhi mesh resource by retrieving it again now that it is created
                rhiMeshHandle = this->__rhiRegistry.getMeshHandle(resourceKey);
            }
            // 6.4 Update the new mesh asset by setting it's rhi resource
            newMeshAsset.setRHIHandle(rhiMeshHandle);
        }
        // 7. Add the gfx mesh asset to the gfx mesh asset registry
        this->__meshRegistry.add(name, std::move(newMeshAsset));
        return Status::OK;
    }

    template<>
    Status Registry::__Impl::load<asset::Material>(const std::string &name, const fs::Path &path) {
        // 1. If already exists, do nothing
        if (this->__materialRegistry.exists(name)) {
            logger::error << "Failed to load new material: name\"" << name << "\" already exists" << std::endl;
            return Status::E_ALREADY_EXISTS;
        }
        logger::debug << "Loading material asset with name: \"" << name << "\", texture path: " << path.asStr() << std::endl;
        // 2. We always identify resources by their keys, since material has a shader and a texture resrouce, the resource key is the 2 combined
        fs::Path shaderPath("/home/matteo/Projects/Liminal/assets/shaders/core/textured.glsl");
        std::string resourceKey = shaderPath.asStr() + "|" + path.asStr();
        // 3. We create the new asset
        gfx::asset::Material newMaterialAsset;
        // 4. We check if the asset already exists
        const gfx::asset::Material *existingMaterialAsset = this->__materialRegistry.getByResourceKey(resourceKey);
        // 5. If it exists, then we must create a new asset but copy it's data
        if (existingMaterialAsset != nullptr) {
            newMaterialAsset.copy(*existingMaterialAsset);
        } else { // 6. If it don't exists, then we must load it from files and add data to gfx and resource registries
            // 6.1 Load from file
            newMaterialAsset.load(path);
            // --- TEXTURE ---
            // 6.2 Create the corresponding rhi resource if it don't exists
            rhi::def::Handle rhiTextureHandle = this->__rhiRegistry.getTextureHandle(path.asStr());
            if (rhiTextureHandle == rhi::def::NULL_HANDLE) { // if the texture rhi resource does not exist, create it
                this->__rhiRegistry.addTexture(path.asStr(), newMaterialAsset.getTextureData(), newMaterialAsset.getTextureSize(), newMaterialAsset.getTextureNChannels());
                // 6.3 update the local rhi texture resource by retrieving it again now that it is created
                rhiTextureHandle = this->__rhiRegistry.getTextureHandle(path.asStr());
            }
            // 6.4 Update the new material asset by setting it's rhi resource
            newMaterialAsset.setTextureRHIHandle(rhiTextureHandle);
            // --- SHADER ---
            rhi::def::Handle rhiShaderHandle = this->__rhiRegistry.getShaderHandle(shaderPath.asStr());
            if (rhiShaderHandle == rhi::def::NULL_HANDLE) { // if the shader rhi resource does not exist, create it
                this->__rhiRegistry.addShader(shaderPath.asStr(), newMaterialAsset.getShaderSource(rhi::def::ShaderType::VERTEX), newMaterialAsset.getShaderSource(rhi::def::ShaderType::GEOMETRY), newMaterialAsset.getShaderSource(rhi::def::ShaderType::FRAGMENT), newMaterialAsset.getShaderSource(rhi::def::ShaderType::COMPUTE));
                // update the local rhi shader by retreiving it
                rhiShaderHandle = this->__rhiRegistry.getShaderHandle(shaderPath.asStr());
            }
            // Update new material asset with shader
            newMaterialAsset.setShaderRHIHandle(rhiShaderHandle);
        }
        //7. Add the new material to the gfx registry
        this->__materialRegistry.add(name, std::move(newMaterialAsset));
        return Status::OK;
    }

    template<>
    bool Registry::__Impl::exists<asset::Mesh>(const std::string &name) const { return this->__meshRegistry.exists(name); }
    
    template<>
    bool Registry::__Impl::exists<asset::Material>(const std::string &name) const { return this->__materialRegistry.exists(name); }

    template<>
    const asset::Mesh *Registry::__Impl::get(const std::string &name) const {
        if (this->exists<asset::Mesh>(name) == false) {
            logger::error << "Failed to find mesh asset \"" << name << "\"" << std::endl;
            return nullptr;
        }
        return this->__meshRegistry.get(name);
    }

    template<>
    const asset::Material *Registry::__Impl::get(const std::string &name) const {
        if (this->exists<asset::Material>(name) == false) {
            logger::error << "Failed to find material asset \"" << name << "\"" << std::endl;
            return nullptr;
        }
        return this->__materialRegistry.get(name);
    }

    Registry::Registry(rhi::Registry &rhiRegistry) :
    __impl(std::make_unique<__Impl>(rhiRegistry))
    {}

    Registry::~Registry() = default;

    template<>
    bool Registry::exists<asset::Mesh>(const std::string &name) const { return this->__impl->exists<asset::Mesh>(name); }

    template<>
    bool Registry::exists<asset::Material>(const std::string &name) const { return this->__impl->exists<asset::Material>(name); }

    template<>
    Status Registry::load<asset::Mesh>(const std::string &name, const fs::Path &path) { return this->__impl->load<asset::Mesh>(name, path); }
    
    template<>
    Status Registry::load<asset::Material>(const std::string &name, const fs::Path &path) { return this->__impl->load<asset::Material>(name, path); }

    template<>
    const asset::Mesh *Registry::get(const std::string &name) const { return this->__impl->get<asset::Mesh>(name); }

    template<>
    const asset::Material *Registry::get(const std::string &name) const { return this->__impl->get<asset::Material>(name); } 

} // namespace gfx

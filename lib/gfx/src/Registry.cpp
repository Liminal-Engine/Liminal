#include "Registry.hpp"
#include "__private/__registry/__AssetRegistry.hpp"
#include "__private/__asset/__Shader.hpp"
#include "__private/__asset/__Texture.hpp"

#include "jsonio/InJson.hpp"

// #include "__private/__registry/__Mesh.hpp"
// #include "__private/__registry/__Material.hpp"


#include <logger/logger.hpp>
#include <rhi/def/ShaderType.hpp>

#include <utility>

namespace gfx {

    class Registry::__Impl {
        private:
            rhi::Registry &__rhiRegistry;
            __private::__registry::__AssetRegistry<asset::Mesh> __meshRegistry;
            __private::__registry::__AssetRegistry<__private::__asset::__Shader> __shaderRegistry;
            __private::__registry::__AssetRegistry<__private::__asset::__Texture> __textureRegistry;
            __private::__registry::__AssetRegistry<asset::Material> __materialRegistry;
            // __private::__registry::__Mesh __meshRegistry;
            // __private::__registry::__Material __materialRegistry;

        public:
            __Impl(rhi::Registry &rhiRegistry) :
            __rhiRegistry(rhiRegistry),
            __meshRegistry(),
            __shaderRegistry(),
            __textureRegistry(),
            __materialRegistry()
            // __materialRegistry()
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
        // 2. We always identify the resource by it's key, which is the path's absolute cleaned string:
        fs::Path absolutePath(path);
        absolutePath.toAbsolute();
        absolutePath.clean();
        std::string key(absolutePath.asStr());
        // 3. We create the new asset
        logger::debug << "Loading mesh asset with name: " << name << ", path: " << absolutePath.asStr() << std::endl;
        gfx::asset::Mesh newMeshAsset;
        // 3.1 If the asset already exists for this path, just copy it, otherwise, load it
        if (this->__meshRegistry.exists(absolutePath)) newMeshAsset.copy(*this->__meshRegistry.get(absolutePath));
        else newMeshAsset.load(absolutePath);
        // 4. If the rhi resource exists for this path (key), just use it, otherwise, create it FIXME : create and use exits for this instead of get
        rhi::def::Handle rhiMeshHandle = this->__rhiRegistry.getMeshHandle(key); // FIXME: create and use rhiRegistry.get<rhi::resource::Mesh>(key) instead
        if (rhiMeshHandle == rhi::def::NULL_HANDLE) {
            this->__rhiRegistry.addMesh(key, newMeshAsset.getVertices(), newMeshAsset.getIndices());
            rhiMeshHandle = this->__rhiRegistry.getMeshHandle(key);
        }
        // 5. Set rhi handle and add to asset registry
        newMeshAsset.bind(this->__rhiRegistry.getMeshResource(rhiMeshHandle));
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
        // 2. We always identify the resource by it's key, which is the path's absolute cleaned string
        fs::Path absolutePath(path);
        absolutePath.toAbsolute();
        absolutePath.clean();
        std::string key(absolutePath.asStr());
        // 3. We create the new asset
        logger::debug << "Loading material asset with name: " << name << ", path: " << absolutePath.asStr() << std::endl;
        gfx::asset::Material newMaterialAsset;
        // 3.1 If the asset already exists for this path, just copy it, otherwise, load it // FIXME: decide if I shluld create another with the new name or just throw an error
        if (this->__materialRegistry.exists(absolutePath)) {
            newMaterialAsset.copy(*this->__materialRegistry.get(absolutePath));
            return Status::OK;
        } 
        else newMaterialAsset.load(absolutePath);
        // 4. Set the material asset texture if required
        std::string textureName("");
        if (newMaterialAsset.mustHaveTexture()) {
            fs::Path texturePath(newMaterialAsset.getTexturePath());
            textureName = texturePath.asStr();
            // 4.1 If the texture does not exists, create it, it's name is the path as string
            if (this->__textureRegistry.exists(textureName) == false) {
                gfx::__private::__asset::__Texture textureAsset;
                textureAsset.load(texturePath);
                // 4.2 Set the texture RHI resource handle, create it if does not exists
                rhi::def::Handle rhiTextureHandle = this->__rhiRegistry.getTextureHandle(textureName);
                if (rhiTextureHandle == rhi::def::NULL_HANDLE) {
                    this->__rhiRegistry.addTexture(textureName, textureAsset.getData(), textureAsset.getSize(), textureAsset.getNChannels());
                    rhiTextureHandle = this->__rhiRegistry.getTextureHandle(textureName);
                }
                textureAsset.bind(this->__rhiRegistry.getTextureResource(rhiTextureHandle));
                this->__textureRegistry.add(textureName, std::move(textureAsset));
            }
        }
        __private::__asset::__Texture *relatedTextureAsset = this->__textureRegistry.get(textureName); // will be NULL if textureName is not defined
        // 5. Set the shader
        // const __private::__asset::__Shader *relatedShaderAsset = __findShader(newMaterialAsset);
        fs::Path shaderPath("/home/matteo/Projects/Liminal/assets/shaders/core/textured.glsl");
        std::string shaderName(shaderPath.asStr());
        // 5.1 If the shader asset does not exists, create it, it's name is the shader path as string
        if (this->__shaderRegistry.exists(shaderName) == false) {
            gfx::__private::__asset::__Shader shaderAsset;
            shaderAsset.load(shaderPath);
            // 5.2 Set the shader rhi Handle, create it if it does not exists
            rhi::def::Handle rhiShaderHandle = this->__rhiRegistry.getShaderHandle(shaderName);
            if (rhiShaderHandle == rhi::def::NULL_HANDLE) {
                this->__rhiRegistry.addShader(shaderName, shaderAsset.getSource(rhi::def::ShaderType::VERTEX), shaderAsset.getSource(rhi::def::ShaderType::GEOMETRY), shaderAsset.getSource(rhi::def::ShaderType::FRAGMENT), shaderAsset.getSource(rhi::def::ShaderType::COMPUTE));
                rhiShaderHandle = this->__rhiRegistry.getShaderHandle(shaderName);
            }
            shaderAsset.bind(this->__rhiRegistry.getShaderResource(rhiShaderHandle));
            this->__shaderRegistry.add(shaderName, std::move(shaderAsset));
        }
        __private::__asset::__Shader *relatedShaderAsset = this->__shaderRegistry.get(shaderName);
        // 6. Bind material and add to registry
        newMaterialAsset.bind(relatedTextureAsset, relatedShaderAsset);
        this->__materialRegistry.add(name, std::move(newMaterialAsset));
        return Status::OK;


        // // 1. If already exists, do nothing
        // if (this->__materialRegistry.exists(name)) {
        //     logger::error << "Failed to load new material: name\"" << name << "\" already exists" << std::endl;
        //     return Status::E_ALREADY_EXISTS;
        // }
        // fs::Path absolutePath(path);
        // absolutePath.toAbsolute();
        // absolutePath.clean();
        // logger::debug << "Loading material asset with name: \"" << name << "\", path: " << absolutePath.asStr() << std::endl;
        // // 2. We always identify resources by their keys, since material has a shader and a texture resrouce, the resource key is the 2 combined
        // fs::Path shaderPath("/home/matteo/Projects/Liminal/assets/shaders/core/textured.glsl");
        // std::string resourceKey = shaderPath.asStr() + "|" + absolutePath.asStr();
        // // 3. We create the new asset
        // gfx::asset::Material newMaterialAsset;
        // // 4. We check if the asset already exists
        // const gfx::asset::Material *existingMaterialAsset = this->__materialRegistry.getByResourceKey(resourceKey);
        // // 5. If it exists, then we must create a new asset but copy it's data
        // if (existingMaterialAsset != nullptr) {
        //     newMaterialAsset.copy(*existingMaterialAsset);
        // } else { // 6. If it don't exists, then we must load it from files and add data to gfx and resource registries
        //     // 6.1 Load from file
        //     newMaterialAsset.load(absolutePath);
        //     // --- TEXTURE ---
        //     // 6.2 Create the corresponding rhi resource if it don't exists
        //     rhi::def::Handle rhiTextureHandle = this->__rhiRegistry.getTextureHandle(absolutePath.asStr());
        //     if (rhiTextureHandle == rhi::def::NULL_HANDLE) { // if the texture rhi resource does not exist, create it
        //         this->__rhiRegistry.addTexture(absolutePath.asStr(), newMaterialAsset.getTextureData(), newMaterialAsset.getTextureSize(), newMaterialAsset.getTextureNChannels());
        //         // 6.3 update the local rhi texture resource by retrieving it again now that it is created
        //         rhiTextureHandle = this->__rhiRegistry.getTextureHandle(absolutePath.asStr());
        //     }
        //     // 6.4 Update the new material asset by setting it's rhi resource
        //     newMaterialAsset.setTextureRHIHandle(rhiTextureHandle);
        //     // --- SHADER ---
        //     rhi::def::Handle rhiShaderHandle = this->__rhiRegistry.getShaderHandle(shaderPath.asStr());
        //     if (rhiShaderHandle == rhi::def::NULL_HANDLE) { // if the shader rhi resource does not exist, create it
        //         this->__rhiRegistry.addShader(shaderPath.asStr(), newMaterialAsset.getShaderSource(rhi::def::ShaderType::VERTEX), newMaterialAsset.getShaderSource(rhi::def::ShaderType::GEOMETRY), newMaterialAsset.getShaderSource(rhi::def::ShaderType::FRAGMENT), newMaterialAsset.getShaderSource(rhi::def::ShaderType::COMPUTE));
        //         // update the local rhi shader by retreiving it
        //         rhiShaderHandle = this->__rhiRegistry.getShaderHandle(shaderPath.asStr());
        //     }
        //     // Update new material asset with shader
        //     newMaterialAsset.setShaderRHIHandle(rhiShaderHandle);
        // }
        // //7. Add the new material to the gfx registry
        // this->__materialRegistry.add(name, std::move(newMaterialAsset));
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

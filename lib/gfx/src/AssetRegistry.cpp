#include "AssetRegistry.hpp"
#include "asset/Mesh.hpp"
#include "asset/Shader.hpp"
#include "asset/Texture.hpp"

#include <logger/logger.hpp>

#include <unordered_map>
#include <string>
#include <type_traits>

#define __GET_MAP_BODY \
    if constexpr (std::is_same_v<T, asset::Mesh>) return this->__meshes; \
    else if constexpr (std::is_same_v<T, asset::Shader>) return this->__shaders; \
    else if constexpr (std::is_same_v<T, asset::Texture>) return this->__textures; \
    else static_assert(false, "Unsupported GFX type");

namespace gfx {
    class AssetRegistry::__Impl {
        private:
            std::unordered_map<std::string, std::unique_ptr<asset::Mesh>> __meshes;
            std::unordered_map<std::string, std::unique_ptr<asset::Shader>> __shaders;
            std::unordered_map<std::string, std::unique_ptr<asset::Texture>> __textures;

            template<asset::AssetType T>
            auto &__getMap(void) const;
            template<asset::AssetType T>
            auto &__getMap(void);

        public:
            __Impl(void) : __meshes{}, __shaders{}, __textures{} {}

            ~__Impl() {
                this->__meshes.clear();
                this->__shaders.clear();
                this->__textures.clear();
            }

            template<asset::AssetType T>
            Status load(const fs::Path &path);
            template<asset::AssetType T>
            bool exists(const std::string &name) const;
            template<asset::AssetType T>
            const T *get(const std::string &name) const;

    };

    template<asset::AssetType T>
    auto &AssetRegistry::__Impl::__getMap(void) const { __GET_MAP_BODY }

    template<asset::AssetType T>
    auto &AssetRegistry::__Impl::__getMap(void) { __GET_MAP_BODY }

    template<asset::AssetType T>
    Status AssetRegistry::__Impl::load(const fs::Path &path) {
        // The name is the relative path in str
        std::string name(path.asStr()); // The name is the filename without the extension (it secures the asset duplication avoidance)
        auto &map = this->__getMap<T>();
        if (map.contains(name)) {
            logger::error << "Failed to load new GFX, name already exists: " << name << std::endl;
            return Status::E_ALREADY_EXISTS;
        }
        auto object = std::make_unique<T>();
        if (Status assetLoadStatus = Status::N_OK; (assetLoadStatus = object->load(path)) != Status::OK) {
            logger::error << "Failed to load object for path: " << name << ", status=" << toStr(assetLoadStatus) << std::endl;
            return assetLoadStatus;
        }
        map.emplace(name, std::move(object));
        return Status::OK;
    }

    template<asset::AssetType T>
    bool AssetRegistry::__Impl::exists(const std::string &name) const {
        return __getMap<T>().contains(name);
    }

    template<asset::AssetType T>
    const T *AssetRegistry::__Impl::get(const std::string &name) const {
        auto &map = __getMap<T>();
        if (map.contains(name) == false) {
            logger::error << "Failed to find an asset with name: " << name << std::endl;
            return nullptr;
        }
        return map.at(name).get();
    }


    AssetRegistry::AssetRegistry(void) : __impl(std::make_unique<__Impl>()) {}
    AssetRegistry::~AssetRegistry() = default;
    AssetRegistry &AssetRegistry::__instance(void) {
        static AssetRegistry instance;
        return instance;
    }

    template <asset::AssetType T>
    Status AssetRegistry::load(const fs::Path &path) { return __instance().__impl->load<T>(path); }
    template <asset::AssetType T>
    bool AssetRegistry::exists(const std::string &name) { return __instance().__impl->exists<T>(name); }
    template<asset::AssetType T>
    const T *AssetRegistry::get(const std::string &name) { return __instance().__impl->get<T>(name); }


    /// template instanciation
    template Status AssetRegistry::load<asset::Mesh>(const fs::Path &path);
    template Status AssetRegistry::load<asset::Shader>(const fs::Path &path);
    template Status AssetRegistry::load<asset::Texture>(const fs::Path &path);

    template bool AssetRegistry::exists<asset::Mesh>(const std::string &name);
    template bool AssetRegistry::exists<asset::Shader>(const std::string &name);
    template bool AssetRegistry::exists<asset::Texture>(const std::string &name);

    template const asset::Mesh *AssetRegistry::get<asset::Mesh>(const std::string &name);
    template const asset::Shader *AssetRegistry::get<asset::Shader>(const std::string &name);
    template const asset::Texture *AssetRegistry::get<asset::Texture>(const std::string &name);
} // namespace gfx

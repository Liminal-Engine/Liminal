#include "Application.hpp"

#include <logger/logger.hpp>
#include <fs/Path.hpp>
#include <entity/AEntity.hpp>
#include <gfx/AssetRegistry.hpp>
#include <entity/Registry.hpp>

#include <vector>

namespace host {
    class Application::__Impl {
        private:
            template<gfx::asset::AssetType T>
            static Status __loadAsset(const std::string &path); // FIXME use macros instead ?
            template<gfx::asset::AssetType T>
            static Status __setAssetToEntity(entity::AEntity &entity, const std::string &name);


        public:
            __Impl() {}
            ~__Impl() {}

            Status init(void) const {
                // 1. Load all needed assets
                Status tmpStatus = Status::N_OK;
                if ((tmpStatus = __loadAsset<gfx::asset::Mesh>("toto.obj")) != Status::OK) return tmpStatus;
                if ((tmpStatus = __loadAsset<gfx::asset::Shader>("assets/shaders/core/textured.glsl")) != Status::OK) return tmpStatus;
                if ((tmpStatus = __loadAsset<gfx::asset::Texture>("assets/textures/platform_0_2K.jpg")) != Status::OK) return tmpStatus;
                // 2. Create entities and set their assets
                entity::AEntity entity;
                if ((tmpStatus = this->__setAssetToEntity<gfx::asset::Mesh>(entity, "toto.obj")) != Status::OK) return tmpStatus;
                if ((tmpStatus = this->__setAssetToEntity<gfx::asset::Shader>(entity, "assets/shaders/core/textured.glsl")) != Status::OK) return tmpStatus;
                if ((tmpStatus = this->__setAssetToEntity<gfx::asset::Texture>(entity, "assets/textures/platform_0_2K.jpg")) != Status::OK) return tmpStatus;
                // 3. Add entities to entity registry
                entity::Registry::add(std::move(entity));
                return Status::OK;
            }
    };


    template<gfx::asset::AssetType T>
    Status Application::__Impl::__loadAsset(const std::string &path) {
        logger::debug << "Loading asset " << path << std::endl;
        if (gfx::Status loadStatus = gfx::Status::N_OK; (loadStatus = gfx::AssetRegistry::load<T>(fs::Path(path))) != gfx::Status::OK) {
            logger::error << "Failed to load asset " << path << ", status=" << gfx::toStr(loadStatus) << std::endl;
            return Status::E_ASSET_LOAD;
        }
        return Status::OK;
    }

    template<gfx::asset::AssetType T>
    Status Application::__Impl::__setAssetToEntity(entity::AEntity &entity, const std::string &name) {
        if (gfx::AssetRegistry::exists<T>(name) == false) {                        
            logger::error << "Failed to asign asset: " << name << ", this asset is not loaded" << std::endl;
            return Status::E_ASSET_NO_EXISTS;
        }
        const T *asset = gfx::AssetRegistry::get<T>(name);
        if (asset->isLoaded() == false) [[unlikely]] {
            logger::error << "Failed to asign asset: " << name << ", this asset is not loaded" << std::endl;
            return Status::E_ASSET_NOT_LOADED;
        }
        entity.set(gfx::AssetRegistry::get<T>(name));
        return Status::OK;
    }

    Application::Application(void) : __impl(std::make_unique<__Impl>()) {}
    Application::~Application() = default;

    Status Application::init(void) const { return this->__impl->init(); }

    // template instanciation
    template Status Application::__Impl::__loadAsset<gfx::asset::Mesh>(const std::string &name);
    template Status Application::__Impl::__loadAsset<gfx::asset::Shader>(const std::string &name);
    template Status Application::__Impl::__loadAsset<gfx::asset::Texture>(const std::string &name);

    template Status Application::__Impl::__setAssetToEntity<gfx::asset::Mesh>(entity::AEntity &entity, const std::string &name);
    template Status Application::__Impl::__setAssetToEntity<gfx::asset::Shader>(entity::AEntity &entity, const std::string &name);
    template Status Application::__Impl::__setAssetToEntity<gfx::asset::Texture>(entity::AEntity &entity, const std::string &name);
} // namespace host

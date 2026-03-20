#include "AEntity.hpp"

#include <logger/logger.hpp>

#include <type_traits>

#define __TYPE_TO_ASSET \
    ([&]() -> auto& { \
    if constexpr (std::is_same_v<T, gfx::asset::Mesh>) return this->__mesh; \
    else if constexpr (std::is_same_v<T, gfx::asset::Shader>) return this->__shader; \
    else if constexpr (std::is_same_v<T, gfx::asset::Texture>) return this->__texture; \
    else static_assert(!sizeof(T), "Unsupported asset type"); \
    }())

namespace entity {
    class AEntity::__Impl {
        private:
            const gfx::asset::Mesh *__mesh;
            const gfx::asset::Shader *__shader;
            const gfx::asset::Texture *__texture;
           
        public:
            __Impl(void) : __mesh(nullptr), __shader(nullptr), __texture(nullptr) {}
            ~__Impl() = default;            

            template<gfx::asset::AssetType T>
            void set(const T *asset);
            template<gfx::asset::AssetType T>
            const T *get(void) const;
    };

    template<gfx::asset::AssetType T>
    void AEntity::__Impl::set(const T *asset) { 
        if (asset == nullptr) logger::warn << "Setting new asset with NULL value" << std::endl;
        __TYPE_TO_ASSET = asset;
    }
    template<gfx::asset::AssetType T>
    const T *AEntity::__Impl::get(void) const { return __TYPE_TO_ASSET; }

    AEntity::AEntity(void) : __impl(std::make_unique<__Impl>()) {}
    AEntity::AEntity(AEntity &&other) noexcept = default;
    AEntity &AEntity::operator=(AEntity &&other) noexcept = default;
    AEntity::~AEntity() =  default;

    template<gfx::asset::AssetType T>
    void AEntity::set(const T *asset) { this->__impl->set<T>(asset); }
    template<gfx::asset::AssetType T>
    const T *AEntity::get(void) const { return this->__impl->get<T>(); }

    template void AEntity::set<gfx::asset::Mesh>(const gfx::asset::Mesh *asset);
    template void AEntity::set<gfx::asset::Shader>(const gfx::asset::Shader *asset);
    template void AEntity::set<gfx::asset::Texture>(const gfx::asset::Texture *asset);

    template const gfx::asset::Mesh *AEntity::get<gfx::asset::Mesh>(void) const;
    template const gfx::asset::Shader *AEntity::get<gfx::asset::Shader>(void) const;
    template const gfx::asset::Texture *AEntity::get<gfx::asset::Texture>(void) const;

} // namespace entity

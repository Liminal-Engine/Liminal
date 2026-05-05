#include "Registry.hpp"


namespace entity {
    class Registry::__Impl {
        private:
            entt::registry __data;
        
        public:
            __Impl() {}
            ~__Impl() {
                this->__data.clear();
            }

            entt::registry &getRaw(void) { return this->__data; }
            
            template<def::BundleType T>
            T add(void);
            
    };
    

    template<>
    bundle::Object Registry::__Impl::add<bundle::Object>(void) {
        entt::entity entity = this->__data.create();
        this->__data.emplace<entity::component::tag::Object>(entity);

        return bundle::Object(
            this->__data.emplace<entity::component::Geometry>(entity),
            this->__data.emplace<entity::component::Material>(entity),
            this->__data.emplace<entity::component::Transform>(entity)
        );
    }

    template<>
    bundle::Camera Registry::__Impl::add<bundle::Camera>(void) {
        entt::entity entity = this->__data.create();
        this->__data.emplace<entity::component::tag::Camera>(entity);
        bundle::Camera camera(
            entity,
            this->__data.emplace<entity::component::Transform>(entity),
            this->__data.emplace<entity::component::CameraSettings>(entity)
        );
        return camera;
    }

    Registry::Registry(void) : __impl(std::make_unique<__Impl>()) {}    
    Registry::~Registry() = default;
    Registry &Registry::__instance(void) {
        static Registry instance;
        return instance;
    }

    entt::registry &Registry::getRaw(void) { return __instance().__impl->getRaw(); }
    template<def::BundleType T>
    T Registry::add(void) { return __instance().__impl->add<T>(); }

    
    template bundle::Object Registry::add(void);
    template bundle::Camera Registry::add(void);

} // namespace entity

#include "Application.hpp"

#include <logger/logger.hpp>

#include <vector>

namespace host {
    class Application::__Impl {
        private:

        public:
            __Impl(void)
            {
                // entity::AEntity entity;
                // entity.setMesh("toto");
                // entity.setMaterial("tata");
            }

            Status init(gfx::Registry &assetRegistry, entity::Registry &entityRegistry) const {
                // 1. On load les assets qu'il faut pour faire tourner le jeu
                assetRegistry.loadMesh("famous_triangle", fs::Path("./assets/this_is_the_famous_triangle_path.obj"));                
                assetRegistry.loadMaterial("brick", fs::Path("/home/matteo/Projects/Liminal/assets/textures/platform_0_2K.jpg"));
                entity::AEntity myTriangle;
                myTriangle.setMesh("famous_triangle");
                entityRegistry.add("triangleEntity", std::move(myTriangle));
                
                return Status::OK;
            }
    };

    Application::Application(void) :
    __impl(std::make_unique<__Impl>())
    {

    }

    Application::~Application() = default;

    Status Application::init(gfx::Registry &assetRegistry, entity::Registry &entityRegistry) const { return this->__impl->init(assetRegistry, entityRegistry); }
} // namespace host

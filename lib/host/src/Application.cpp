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
                assetRegistry.load<gfx::asset::Mesh>("famous_triangle", fs::Path("./assets/this_is_the_famous_triangle_path.obj"));
                assetRegistry.load<gfx::asset::Material>("brick", fs::Path("/home/matteo/Projects/Liminal/assets/materials/brick.mat.json"));

                // 2. On créer les entities (qui utilisent les assets)
                entity::AEntity myTriangle;
                myTriangle.setMesh(assetRegistry.get<gfx::asset::Mesh>("famous_triangle")); // FIXME: shoudl'nt this 2 be in the constructor of AEntity instead ?
                myTriangle.setMaterial(assetRegistry.get<gfx::asset::Material>("brick")); // FIXME: shoudl'nt this 2 be in the constructor of AEntity instead ?
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

#include "Renderer.hpp"
#include "resource/Shader.hpp"

#include <logger/logger.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace rhi {

    Renderer *Renderer::__instance = nullptr;

    class Renderer::__Impl {
        private:

        public:
            __Impl(void) {
                glViewport(0, 0, 1280, 720);
                glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }
    };

    void Renderer::init(void) {
        logger::info << "Initializing renderer" << std::endl;        
        if (__instance != nullptr) {
            logger::warn << "Renderer already intialized, nothing to do" << std::endl;
            return;
        }
        if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) != 1) {
            logger::fatal << "Failed to initialize GLAD" << std::endl;
            return;
        }
        __instance = new Renderer();
    }

    void Renderer::destroy(void) {
        logger::debug << "Destroying renderer" << std::endl;
        if (__instance == nullptr) {
            logger::warn << "Renderer not initialized or already destroyed, nothing to do" << std::endl;
            return;
        }
        delete __instance;
        __instance = nullptr;
    }

    Renderer *Renderer::get(void) {
        if (__instance == nullptr) {
            logger::fatal << "Renderer required but not initialized" << std::endl;
        }
        return __instance;
    }

    void Renderer::draw(const entity::Registry &entityRegistry) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // logger::info << "DRAWING" << std::endl;
        // const resource::Shader *shader = registry.getShader(ShaderCategory::CORE, "textured");
        // const resource::Texture *texture = registry.getTexture("ground_2K");
        // const resource::Mesh *mesh = registry.getMesh("TRIANGLE");
        // shader->use();
        // mesh->draw_DELETE_ME_I_AM_NOT_SUPPOSED_TO_DRAW_MYSELF();
    }

    Renderer::Renderer(void) :
    __impl(std::make_unique<__Impl>())
    {
    }

    Renderer::~Renderer() = default;
} // namespace rhi

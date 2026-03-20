#include "Renderer.hpp"
#include "resource/Shader.hpp"

#include <logger/logger.hpp>
#include <entity/Registry.hpp>


#include <glad/glad.h>
#include <EGL/egl.h>

namespace rhi {
    class Renderer::__Impl {
        private:
            def::Handle __deduceShaderHandle(const entity::AEntity &entity) const {
                (void)entity;
                return rhi::Registry::getHandle("assets/shaders/core/textured.glsl");
            }

        public:
            __Impl(void)
            {
                if (gladLoadGLLoader((GLADloadproc)eglGetProcAddress) == 0) {
                    logger::fatal << "Failed to initialize GLAD" << std::endl;
                    return;
                }
                glViewport(0, 0, 1280, 720);
                glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            }
            ~__Impl() {

            }


            void draw(void) const {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                auto &allEntities = entity::Registry::getAll();
                for (const auto &entity : allEntities) {
                    const resource::Mesh *mesh = Registry::getMesh(entity.geometry.getMeshHandle());
                    def::Handle shaderHandle = __deduceShaderHandle(entity);
                    if (shaderHandle != def::NULL_HANDLE) {
                        const resource::Shader *shader = rhi::Registry::getShader(shaderHandle);
                        if (shader) shader->use();
                    }
                    if (mesh) mesh->draw();
                }
            }
    };

    Renderer::Renderer(void) : __impl(std::make_unique<__Impl>()) {}
    Renderer::~Renderer() = default;
    void Renderer::draw(void) const { this->__impl->draw(); }
} // namespace rhi

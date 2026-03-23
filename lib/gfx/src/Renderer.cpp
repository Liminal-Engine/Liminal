#include "Renderer.hpp"

#include <logger/logger.hpp>
#include <rhi/Context.hpp>
#include <rhi/Registry.hpp>
#include <rhi/def/Handle.hpp>
#include <entity/Registry.hpp>
#include <entity/components.hpp>

namespace gfx {
    class Renderer::__Impl {
        private:
            rhi::def::Handle __deduceShaderHandle(const entt::entity &entity) const {
                (void)entity;
                return rhi::Registry::getHandle("assets/shaders/core/textured.glsl");
            }

            void __applyMaterial(const rhi::resource::Shader *shader, const entity::component::Material &material) const {
                shader->setUniform("uColor", material.color);
            }


            const rhi::Context &__rhiContext;

        public:
            __Impl(const rhi::Context &rhiContext) :
            __rhiContext(rhiContext)
            {
                if (this->__rhiContext.isInit() == false) {
                    logger::fatal << "RHI context attached to renderer is not initialized" << std::endl;
                    return;
                }
                rhi::Status tmpStatus = rhi::Status::N_OK;
                if ( (tmpStatus = this->__rhiContext.setViewport(0, 0, 1280, 720)) != rhi::Status::OK) {
                    logger::error << "Renderer failed to set viewport, RHI status=" << rhi::toStr(tmpStatus) << std::endl;
                }
                if ( (tmpStatus = this->__rhiContext.setClearColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f))) != rhi::Status::OK) {
                    logger::error << "Renderer failed to set clear color, RHI status=" << rhi::toStr(tmpStatus) << std::endl;
                }
                if ( (tmpStatus = this->__rhiContext.enableDepthTesting()) != rhi::Status::OK ) {
                    logger::error << "Renderer failed to enable depth testing, RHI status=" << rhi::toStr(tmpStatus) << std::endl;
                }
                if ( (tmpStatus = this->__rhiContext.enableBlending()) != rhi::Status::OK ) {
                    logger::error << "Renderer failed to enable blending, RHI status=" << rhi::toStr(tmpStatus) << std::endl;
                }
            }

            ~__Impl() {

            }

            void draw(void) const {
                this->__rhiContext.clear();

                auto view = entity::Registry::getRaw().view<
                    entity::component::Geometry,
                    entity::component::Transform,
                    entity::component::Material
                >();
                for (entt::entity entity : view) {
                    auto &geometry = view.get<entity::component::Geometry>(entity);
                    auto &transform = view.get<entity::component::Transform>(entity);
                    auto &material = view.get<entity::component::Material>(entity);

                    const rhi::resource::Mesh *meshResource = rhi::Registry::getMesh(geometry.meshHandle);
                    const rhi::def::Handle shaderHandle = __deduceShaderHandle(entity);
                    if (shaderHandle != def::NULL_HANDLE) {
                        const rhi::resource::Shader *shaderResource = rhi::Registry::getShader(shaderHandle);
                        if (shaderResource)  shaderResource->use();
                        __applyMaterial(shaderResource, material);
                        if (meshResource) meshResource->draw();
                    }
                }
            }
    };

    Renderer::Renderer(const rhi::Context &rhiContext) : __impl(std::make_unique<__Impl>(rhiContext)) {}
    Renderer::~Renderer() = default;
    void Renderer::draw(void) const { this->__impl->draw(); }
} // namespace gfx

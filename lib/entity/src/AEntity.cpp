#include "AEntity.hpp"

#include <gfx/asset/Material.hpp>
#include <gfx/asset/Mesh.hpp>
#include <logger/logger.hpp>

namespace entity {
    class AEntity::__Impl {
        private:
            const gfx::asset::Mesh *__mesh;
            const gfx::asset::Material *__material;

            
        public:
            __Impl(void) :
            __mesh(nullptr),
            __material(nullptr)
            {
                
            }

            ~__Impl() = default;

            Status setMesh(const gfx::asset::Mesh *mesh) {
                if (mesh == nullptr) {
                    logger::error << "Failed to assign mesh to entity: mesh is NULL" << std::endl;
                    return Status::E_NO_EXISTS;
                }
                this->__mesh = mesh;
                return Status::OK;
            }

            Status setMaterial(const gfx::asset::Material *material) {
                if (material == nullptr) {
                    logger::error << "Failed to assign material to entity: material is NULL" << std::endl;
                    return Status::E_NO_EXISTS;
                }
                this->__material = material;
                return Status::OK;
            }

            RessourceHandle getShaderHandle(void) const { return this->__material->getShaderRHIHandle(); }

            RessourceHandle getTexureHandle(void) const { return this->__material->getTextureRHIHandle(); }

            RessourceHandle getMeshHandle(void) const { return this->__mesh->getRHIHandle(); }

            const gfx::asset::Material *getMaterial(void) const { return this->__material; }

    };

    AEntity::AEntity(void) :
    __impl(std::make_unique<__Impl>())
    {}

    AEntity::AEntity(AEntity &&other) noexcept = default;

    AEntity &AEntity::operator=(AEntity &&other) noexcept = default;

    AEntity::~AEntity() =  default;

    Status AEntity::setMesh(const gfx::asset::Mesh *mesh) { return this->__impl->setMesh(mesh); }
    Status AEntity::setMaterial(const gfx::asset::Material *material) { return this->__impl->setMaterial(material); }

    RessourceHandle AEntity::getShaderHandle(void) const { return this->__impl->getShaderHandle(); }
    RessourceHandle AEntity::getTexureHandle(void) const { return this->__impl->getTexureHandle(); }
    RessourceHandle AEntity::getMeshHandle(void) const { return this->__impl->getMeshHandle(); }
    const gfx::asset::Material *AEntity::getMaterial(void) const { return this->__impl->getMaterial(); }


} // namespace entity

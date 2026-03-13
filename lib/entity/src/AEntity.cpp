#include "AEntity.hpp"

namespace entity {
    class AEntity::__Impl {
        private:
            
        public:
            __Impl(void)
            {
                
            }

            ~__Impl() = default;

            Status setMesh(const std::string &name) {
                (void)name;
                return Status::OK;
            }

            Status setMaterial(const std::string &name) {
                (void)name;
                return Status::OK;
            }
    };

    AEntity::AEntity(void) :
    __impl(std::make_unique<__Impl>())
    {}

    AEntity::AEntity(AEntity &&other) noexcept = default;

    AEntity &AEntity::operator=(AEntity &&other) noexcept = default;

    AEntity::~AEntity() =  default;

    Status AEntity::setMesh(const std::string &name) { return this->__impl->setMesh(name); }
    Status AEntity::setMaterial(const std::string &name) { return this->__impl->setMaterial(name); }


} // namespace entity

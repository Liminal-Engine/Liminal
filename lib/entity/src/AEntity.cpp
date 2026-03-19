#include "AEntity.hpp"

#include <logger/logger.hpp>

namespace entity {
    class AEntity::__Impl {
        private:
           
        public:
            __Impl(void)
            {
                
            }

            ~__Impl() = default;

    };

    AEntity::AEntity(void) :
    __impl(std::make_unique<__Impl>())
    {}

    AEntity::AEntity(AEntity &&other) noexcept = default;

    AEntity &AEntity::operator=(AEntity &&other) noexcept = default;

    AEntity::~AEntity() =  default;

} // namespace entity

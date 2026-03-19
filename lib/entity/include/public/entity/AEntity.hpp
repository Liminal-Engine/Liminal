#ifndef __LIMINAL__LIB__ENTITY__A_ENTITY_HPP__
#define __LIMINAL__LIB__ENTITY__A_ENTITY_HPP__

#include "Status.hpp"

#include <string>
#include <memory>
#include <cstdint>

namespace entity {

    using RessourceHandle = uint32_t;

    class AEntity {
        public:
            AEntity(void);
            virtual ~AEntity();

            AEntity(const AEntity &) = delete;
            AEntity &operator=(const AEntity &) = delete;
            AEntity(AEntity &&other) noexcept;
            AEntity &operator=(AEntity &&other) noexcept;
            
        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__A_ENTITY_HPP__
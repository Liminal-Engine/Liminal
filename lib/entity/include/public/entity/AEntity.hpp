#ifndef __LIMINAL__LIB__ENTITY__A_ENTITY_HPP__
#define __LIMINAL__LIB__ENTITY__A_ENTITY_HPP__

#include "Status.hpp"

#include <string>
#include <memory>

namespace entity {
    class AEntity {
        public:
            AEntity(void);
            virtual ~AEntity();

            AEntity(const AEntity &) = delete;
            AEntity &operator=(const AEntity &) = delete;
            AEntity(AEntity &&other) noexcept;
            AEntity &operator=(AEntity &&other) noexcept;

            
            [[nodiscard]] Status setMesh(const std::string &name);
            [[nodiscard]] Status setMaterial(const std::string &name);


        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__A_ENTITY_HPP__
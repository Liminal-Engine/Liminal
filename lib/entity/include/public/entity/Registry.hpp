#ifndef __LIMINAL__LIB__ENTITY__REGISTRY_HPP__
#define __LIMINAL__LIB__ENTITY__REGISTRY_HPP__

#include "Status.hpp"

#include "AEntity.hpp"

#include <memory>

namespace entity {
    class Registry {
        public:
            Registry(const Registry&) = delete;
            Registry(Registry&&) = delete;
            Registry &operator=(const Registry&) = delete;
            Registry &operator=(Registry&&) = delete;

            static void add(AEntity &&entity);
            static const std::vector<AEntity> &getAll(void);

        private:
            Registry(void);
            ~Registry();
            static Registry &__instance(void);

            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__REGISTRY_HPP__
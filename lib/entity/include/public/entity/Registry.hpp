#ifndef __LIMINAL__LIB__ENTITY__REGISTRY_HPP__
#define __LIMINAL__LIB__ENTITY__REGISTRY_HPP__

#include "entity/def/BundleType.hpp"

#include <entt/entt.hpp>

#include <memory>

namespace entity {
    class Registry {
        public:
            Registry(const Registry&) = delete;
            Registry(Registry&&) = delete;
            Registry &operator=(const Registry&) = delete;
            Registry &operator=(Registry&&) = delete;

            static entt::registry &getRaw(void);

            template<def::BundleType T>
            static T add(void);
        
        private:
            Registry(void);
            ~Registry();
            class __Impl;
            std::unique_ptr<__Impl> __impl;
            static Registry &__instance(void);

    };
//     class Registry {
//         public:

//         private:

//             class __Impl;
//             std::unique_ptr<__Impl> __impl;
//     };
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__REGISTRY_HPP__
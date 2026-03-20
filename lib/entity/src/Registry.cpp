#include "Registry.hpp"

#include <vector>

namespace entity {
    class Registry::__Impl {
        private:
            std::vector<AEntity> __data;
        
        public:
            __Impl() {}
            ~__Impl() {
                this->__data.clear();
            }

            void add(AEntity &&entity) { this->__data.push_back(std::move(entity)); }
            const std::vector<AEntity> &getAll(void) const { return this->__data; }
    };

    Registry::Registry(void) : __impl(std::make_unique<__Impl>()) {}
    Registry::~Registry() = default;
    Registry &Registry::__instance(void) {
        static Registry instance;
        return instance;
    }

    void Registry::add(AEntity &&entity) { __instance().__impl->add(std::move(entity)); }
    const std::vector<AEntity> &Registry::getAll(void) { return __instance().__impl->getAll(); }
} // namespace entity

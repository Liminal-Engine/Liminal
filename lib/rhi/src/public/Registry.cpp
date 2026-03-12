#include "Registry.hpp"
#include "__private/__registry/Shader.hpp"


namespace rhi {
    class Registry::__Impl {
        private:
            __private::__registry::Shader __shaderRegistry;

        public:
            __Impl(void) {

            }

            ~__Impl() = default;
            
            Status init(void) {
                this->__shaderRegistry.init();
            }
    };

    Registry::Registry(void) :
    __impl(std::make_unique<__Impl>())
    {}

    Registry::~Registry() = default;

    Status Registry::init(void) { return this->__impl->init(); }
} // namespace rhi

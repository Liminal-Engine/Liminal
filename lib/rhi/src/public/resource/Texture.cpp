#include "resource/Texture.hpp"

#include <logger/logger.hpp>

namespace rhi {
    namespace resource {
        
        class Texture::__Impl {
            private:
                uint32_t __handle;
    
            public:
                __Impl(void) :
                __handle(0)
                {
                    
                }
        };
    
        Texture::Texture(void) :
        __impl(std::make_unique<__Impl>())
        {
    
        }
    
        Texture::~Texture() = default;
    } // namespace resource
} // namespace rhi

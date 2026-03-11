#include "resource/Texture.hpp"

#include <logger/logger.hpp>

namespace rhi {
    namespace resource {
        
        Texture *Texture::__instance = nullptr;
    
        class Texture::__Impl {
            private:
                uint32_t __handle;
    
            public:
                __Impl(void) :
                __handle(0)
                {
                    
                }
        };
    
        void Texture::init(void) {
            if (__instance != nullptr) {
                logger::error << "Texture resource already intialized, nothing to do" << std::endl;
                return;
            }
            __instance = new Texture();
        }
    
        void Texture::destroy(void) {
            if (__instance == nullptr) {
                logger::error << "Texture resource not initialized or already destroyed, nothing to do" << std::endl;
                return;
            }
            delete __instance;
            __instance = nullptr;
        }
    
        Texture *Texture::get(void) {
            if (__instance == nullptr) {
                logger::fatal << "Texture resource required but not initialized" << std::endl;
            }
            return __instance;
        }
    
        Texture::Texture(void) :
        __impl(std::make_unique<__Impl>())
        {
    
        }
    
        Texture::~Texture() = default;
    } // namespace resource
} // namespace rhi

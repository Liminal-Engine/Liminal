#include "Registry.hpp"
#include "__private/__registry/__Shader.hpp"
#include "__private/__registry/__Texture.hpp"
#include "__private/__registry/__Mesh.hpp"

#include <logger/logger.hpp>

namespace rhi {
    class Registry::__Impl {
        private:
            __private::__registry::__Shader __shaderRegistry;
            __private::__registry::__Texture __textureRegistry;
            __private::__registry::__Mesh __meshRegistry;

        public:
            __Impl(void) {

            }

            ~__Impl() = default;
            
            Status init(void) {
                Status tmpStatus = Status::OK;

                tmpStatus = this->__shaderRegistry.init();
                if (tmpStatus != Status::OK) {
                    logger::error << "Failed to initialize shader registry" << std::endl;
                    return tmpStatus;
                }
                tmpStatus = this->__textureRegistry.init();
                if (tmpStatus != Status::OK) {
                    logger::error << "Failed to initialize texture registry" << std::endl;
                    return tmpStatus;
                }
                tmpStatus = this->__meshRegistry.init();
                if (tmpStatus != Status::OK) {
                    logger::error << "Failed to initialize mesh registry" << std::endl;
                    return tmpStatus;
                }
                return Status::OK;
            }
    };

    Registry::Registry(void) :
    __impl(std::make_unique<__Impl>())
    {}

    Registry::~Registry() = default;

    Status Registry::init(void) { return this->__impl->init(); }
} // namespace rhi

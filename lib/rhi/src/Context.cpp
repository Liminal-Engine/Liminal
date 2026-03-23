#include "Context.hpp"

#include <glad/glad.h>
#include <EGL/egl.h>

#include <logger/logger.hpp>

namespace rhi {
    class Context::__Impl {
        private:
            static std::string __glErrorToStr(GLenum error) {
                switch (error) {
                    case GL_NO_ERROR: return "GL_NO_ERROR";
                    case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
                    case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
                    case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
                    case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
                    case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
                    case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
                    case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
                }
                return "UNKNOWN_OPENGL_ERROR";
            }

            bool __isInit;
            mutable GLbitfield __clearBitMask;
        public:
            __Impl(void) :
            __isInit(false),
            __clearBitMask(GL_COLOR_BUFFER_BIT)
            {}
            ~__Impl() = default;

            Status init(void) noexcept {
                if (gladLoadGLLoader((GLADloadproc)eglGetProcAddress) == 0) {
                    logger::fatal << "Failed to initialize GLAD" << std::endl;
                    return Status::E_GLAD;
                }
                this->__isInit = true;
                return Status::OK;
            };

            bool isInit(void) const noexcept {{ return this->__isInit; }}
            
            Status setViewport(int left, int top, size_t width, size_t height) const noexcept {
                glViewport(left, top, width, height);
                GLenum error(glGetError());
                if (error != GL_NO_ERROR) {
                    logger::error << "OpenGL error when setting viewport: " << __glErrorToStr(error) << std::endl;
                    return Status::E_OPEN_GL;
                }
                return Status::OK;
            }

            Status setClearColor(const glm::vec4 &color) const noexcept {
                glClearColor(color.x, color.y, color.z, color.w);
                GLenum error(glGetError());
                if (error != GL_NO_ERROR) {
                    logger::error << "OpenGL error when setting clear color: " << __glErrorToStr(error) << std::endl;
                    return Status::E_OPEN_GL;
                }
                return Status::OK;
            }

            Status enableDepthTesting(void) const noexcept {
                glEnable(GL_DEPTH_TEST);
                GLenum error(glGetError());
                if (error != GL_NO_ERROR) {
                    logger::error << "OpenGL error when enabling depth testing: " << __glErrorToStr(error) << std::endl;
                    return Status::E_OPEN_GL;
                }
                this->__clearBitMask |= GL_DEPTH_BUFFER_BIT;
                return Status::OK;
            }

            Status enableBlending(void) const noexcept {
                glEnable(GL_BLEND);
                GLenum error(glGetError());
                if (error != GL_NO_ERROR) {
                    logger::error << "OpenGL error when enabling blending: " << __glErrorToStr(error) << std::endl;
                    return Status::E_OPEN_GL;
                }
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                error = glGetError();
                if (error != GL_NO_ERROR) {
                    logger::error << "OpenGL error when setting blending function: " << __glErrorToStr(error) << std::endl;
                    return Status::E_OPEN_GL;
                }
                return Status::OK;
            }

            void clear(void) const noexcept { glClear(this->__clearBitMask); }
    };

    Context::Context(void) : __impl(std::make_unique<__Impl>()) {}
    Context::~Context() = default;

    Status Context::init(void) noexcept { return this->__impl->init(); }
    bool Context::isInit(void) const noexcept { return this->__impl->isInit(); }
    Status Context::setViewport(int left, int top, size_t width, size_t height) const noexcept { return this->__impl->setViewport(left, top, width, height); }
    Status Context::setClearColor(const glm::vec4 &color) const noexcept { return this->__impl->setClearColor(color); }
    Status Context::enableDepthTesting(void) const noexcept { return this->__impl->enableDepthTesting(); }
    Status Context::enableBlending(void) const noexcept { return this->__impl->enableBlending(); }
    void Context::clear(void) const noexcept { this->__impl->clear(); }
} // namespace rhi

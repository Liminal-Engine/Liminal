#include "__private/__EGLResource.hpp"

extern "C" {
    #include <wayland-egl.h>
    #include <EGL/egl.h>
}

#include <logger/logger.hpp>

namespace wsi {
    namespace __private {
        class __EGLResource::__Impl {
            private:
                wl_egl_window   *__window;
                EGLDisplay      __display;
                EGLConfig       __config;
                EGLContext      __context;
                EGLSurface      __surface;

            public:
                __Impl(wl_display *wlDisplay, wl_surface *wlSurface, int width, int height) :
                __window(nullptr),
                __display(EGL_NO_DISPLAY),
                __config(nullptr),
                __context(EGL_NO_CONTEXT),
                __surface(EGL_NO_SURFACE)
                {
                    if ((this->__display = eglGetDisplay((EGLNativeDisplayType)wlDisplay)) == EGL_NO_DISPLAY) {
                        logger::fatal << "Failed to create an EGL display" << std::endl;
                        return;
                    }
                    if (eglInitialize(this->__display, nullptr, nullptr) == EGL_FALSE) {
                        logger::fatal << "Failed to initialize EGL" << std::endl;
                        return;
                    }
                    EGLint attributes[] = {
                        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
                        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                        EGL_RED_SIZE, 8,
                        EGL_GREEN_SIZE, 8,
                        EGL_BLUE_SIZE, 8,
                        EGL_ALPHA_SIZE, 8,
                        EGL_NONE
                    };
                    EGLint contextAttributes[] = {
                        EGL_CONTEXT_MAJOR_VERSION, 4,
                        EGL_CONTEXT_MINOR_VERSION, 5,
                        EGL_NONE
                    };
                    EGLint numConfig;
                    if (
                        eglChooseConfig(this->__display, attributes, &this->__config, 1, &numConfig) == EGL_FALSE ||
                        numConfig < 1 || this->__config == nullptr
                    ) {
                        logger::fatal << "Failed to find an EGL configuration" << std::endl;
                    }
                    if (eglBindAPI(EGL_OPENGL_API) == EGL_FALSE) {
                        logger::fatal << "Failed to bin an OpenLGL API" << std::endl;
                        return;
                    }
                    if ((this->__context = eglCreateContext(this->__display, this->__config, EGL_NO_CONTEXT, contextAttributes)) == EGL_NO_CONTEXT) {
                        logger::fatal << "Failed to create an EGL context" << std::endl;
                    }
                    if ((this->__window = wl_egl_window_create(wlSurface, width, height)) == nullptr) {
                        logger::fatal << "Failed to create an EGL window" << std::endl;
                    }
                    if ((this->__surface = eglCreateWindowSurface(this->__display, this->__config, (EGLNativeWindowType)this->__window, NULL)) == EGL_NO_SURFACE) {
                        logger::fatal << "Failed to create an EGL surface" << std::endl;
                    }
                    if (eglMakeCurrent(this->__display, this->__surface, this->__surface, this->__context) == EGL_FALSE) {
                        logger::fatal << "Failed to make egl current " << std::endl;
                    }
                }

                ~__Impl() {
                    if (this->__display != EGL_NO_DISPLAY) {
                        eglMakeCurrent(this->__display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
                        if (this->__surface != EGL_NO_SURFACE) eglDestroySurface(this->__display, this->__surface);
                        if (this->__context != EGL_NO_CONTEXT) eglDestroyContext(this->__display, this->__context);
                        eglTerminate(this->__display);
                    }
                }

                void swapBuffers(void) const {
                    eglSwapBuffers(this->__display, this->__surface);
                }
        };

        __EGLResource::__EGLResource(wl_display *wlDisplay, wl_surface *wlSurface, int width, int height) : __impl(std::make_unique<__Impl>(wlDisplay, wlSurface, width, height)) {}
        __EGLResource::~__EGLResource() = default;

        void __EGLResource::swapBuffers(void) const { this->__impl->swapBuffers(); }
    } // namespace __private
} // namespace wsi

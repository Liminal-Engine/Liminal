#include "Window.hpp"

extern "C" {
    #include <wayland-egl.h>
    #include <EGL/egl.h>
    #include "__private/__xdg-shell-client-protocol.h"
    #include <wayland-client.h>
}

#include <logger/logger.hpp>

#include <string.h>

namespace wsi {
    class Window::__Impl {
        private:
            // Wayland resources
            wl_display *__display;
            wl_registry *__registry;
            wl_compositor *__compositor;
            wl_surface *__surface;

            // XDG shell
            xdg_wm_base *__xdgWMBase;
            xdg_surface *__xdgSurface;
            xdg_toplevel *__xdgTopLevel;

            // EGL
            wl_egl_window *__eglWindow;
            EGLDisplay __eglDisplay;
            EGLConfig __eglConfig;
            EGLContext __eglContext;
            EGLSurface __eglSurface;

            bool __shouldClose;

            static void __handlePing(void *data, xdg_wm_base *shell, uint32_t serial) {
                xdg_wm_base_pong(shell, serial);
            }

            inline static const xdg_wm_base_listener __baseListener = {
                .ping = __handlePing
            };

            static void __bindRegistryGlobal(
                void *data,
                wl_registry *registry,
                uint32_t id,
                const char *interface,
                uint32_t version
            ) {
                __Impl *window = static_cast<__Impl *>(data);
                if (strcmp(interface, "wl_compositor") == 0) { // compositor is mandatory, it handle surfaces and send data to GPU
                    window->__compositor = (wl_compositor *)wl_registry_bind(registry, id, &wl_compositor_interface, 4);
                } else if (strcmp(interface, "xdg_wm_base") == 0) { // xdg_wm_base stands for cross desktop group windom manager (it is the capacity to have a linux in gnome)
                    window->__xdgWMBase = (xdg_wm_base*)wl_registry_bind(registry, id, &xdg_wm_base_interface, 1);
                    xdg_wm_base_add_listener(window->__xdgWMBase, &__baseListener, window);
                }
            }

            inline static wl_registry_listener __registryListener = {
                .global = __bindRegistryGlobal,
                .global_remove = nullptr
            };

            static wl_display *__loadWaylandDisplay(void) {
                wl_display *display = wl_display_connect(nullptr);
                if (display == nullptr) {
                    logger::fatal << "Cannot find a wayland server, please make sure wayland is installed" << std::endl;
                }
                return display;
            }

            static wl_registry *__loadWaylandRegistry(wl_display *waylandDisplay) {
                if (waylandDisplay == nullptr) {
                    logger::fatal << "Wayland display is NULL, cannot find a wayland registry" << std::endl;
                    return nullptr;
                }
                wl_registry *waylandRegistry = wl_display_get_registry(waylandDisplay);
                if (waylandRegistry == nullptr) {
                    logger::fatal << "Cannot find a wayland registry" << std::endl;
                }
                return waylandRegistry;
            }

        public:
            __Impl(int width, int height, const std::string &name) :
            __display(__loadWaylandDisplay()),
            __registry(__loadWaylandRegistry(this->__display)),
            __compositor(nullptr),
            __surface(nullptr),
            __xdgWMBase(nullptr),
            __xdgSurface(nullptr),
            __xdgTopLevel(nullptr),
            __eglWindow(nullptr),
            __eglDisplay(EGL_NO_DISPLAY),
            __eglConfig(nullptr),
            __eglContext(EGL_NO_CONTEXT),
            __eglSurface(EGL_NO_SURFACE),
            __shouldClose(false)
            {
                // 1. start registry biding
                wl_registry_add_listener(this->__registry, &__registryListener, this);
                wl_display_roundtrip(this->__display); // this init __compositor and ____xdgWMBase
                if (this->__compositor == nullptr) logger::fatal << "Failed to initialize Wayland compositor" << std::endl;
                if (this->__xdgWMBase == nullptr) logger::fatal << "Failed to initialize XDG WM base" << std::endl;
                // 2. Other init
                if ((this->__surface = wl_compositor_create_surface(this->__compositor)) == nullptr) {
                    logger::fatal << "Failed to initialize Wayland surface" << std::endl;
                }
                if ((this->__xdgSurface = xdg_wm_base_get_xdg_surface(this->__xdgWMBase, this->__surface)) == nullptr) {
                    logger::fatal << "Failed to initialize XDG WM surface" << std::endl;
                }
                if ((this->__xdgTopLevel = xdg_surface_get_toplevel(this->__xdgSurface)) == nullptr) {
                    logger::fatal << "Failed to initialize XDG top level" << std::endl;
                }
                xdg_toplevel_set_title(this->__xdgTopLevel, name.c_str());
                wl_surface_commit(this->__surface);
                // end of Wayland and XDG init, start of EGL init
                // first find a connection (e.g. display)...
                if ((this->__eglDisplay = eglGetDisplay((EGLNativeDisplayType)this->__display)) == EGL_NO_DISPLAY) {
                    logger::fatal << "Failed to create an EGL display" << std::endl;
                }
                // ...then init EGL
                if (eglInitialize(this->__eglDisplay, nullptr, nullptr) == EGL_FALSE) {
                    logger::fatal << "Failed to initialize EGL" << std::endl;
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
                    eglChooseConfig(this->__eglDisplay, attributes, &this->__eglConfig, 1, &numConfig) == EGL_FALSE ||
                    numConfig < 1 || this->__eglConfig == nullptr
                ) {
                    logger::fatal << "Failed to find an EGL configuration" << std::endl;
                }
                if (eglBindAPI(EGL_OPENGL_API) == EGL_FALSE) {
                    logger::fatal << "Failed to bind an OpenGL API" << std::endl;
                }
                if ((this->__eglContext = eglCreateContext(this->__eglDisplay, this->__eglConfig, EGL_NO_CONTEXT, contextAttributes)) == EGL_NO_CONTEXT) {
                    logger::fatal << "Failed to create an EGL context" << std::endl;
                }
                if ((this->__eglWindow = wl_egl_window_create(this->__surface, width, height)) == nullptr) {
                    logger::fatal << "Failed to create an EGL window" << std::endl;
                }
                if ((this->__eglSurface = eglCreateWindowSurface(this->__eglDisplay, this->__eglConfig, (EGLNativeWindowType)this->__eglWindow, NULL)) == EGL_NO_SURFACE) {
                    logger::fatal << "Failed to create an EGL surface" << std::endl;
                }
                if (eglMakeCurrent(this->__eglDisplay, this->__eglSurface, this->__eglSurface, this->__eglContext) == EGL_FALSE) {
                    logger::fatal << "Failed to make egl current " << std::endl;
                }
            }

            ~__Impl() {
                // EGL
                if (this->__eglDisplay != EGL_NO_DISPLAY) {
                    eglMakeCurrent(this->__eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
                    if (this->__eglSurface != EGL_NO_SURFACE) eglDestroySurface(this->__eglDisplay, this->__eglSurface);
                    if (this->__eglContext != EGL_NO_CONTEXT) eglDestroyContext(this->__eglDisplay, this->__eglContext);
                    eglTerminate(this->__eglDisplay);
                }
                if (this->__eglWindow) wl_egl_window_destroy(this->__eglWindow);
                // XDG shell
                if (this->__xdgTopLevel) xdg_toplevel_destroy(this->__xdgTopLevel);
                if (this->__xdgSurface) xdg_surface_destroy(this->__xdgSurface);
                if (this->__xdgWMBase) xdg_wm_base_destroy(this->__xdgWMBase);
                // Wayland resources
                if (this->__display) {
                    wl_display_flush(this->__display);
                    wl_display_disconnect(this->__display);
                }
            }

            bool shouldClose(void) const { return this->__shouldClose; }

            void pollEvents(void) {
                wl_display_dispatch_pending(this->__display);
            }

            void display(void) {
                eglSwapBuffers(this->__eglDisplay, this->__eglSurface);
            }
    };

    Window::Window(int width, int height, const std::string &name) :
    __impl(std::make_unique<__Impl>(width, height, name))
    {}

    Window::~Window() = default;

    bool Window::shouldClose(void) const { return this->__impl->shouldClose(); }
    void Window::pollEvents(void) { this->__impl->pollEvents(); }
    void Window::display(void) {  this->__impl->display(); }

} // namespace wsi

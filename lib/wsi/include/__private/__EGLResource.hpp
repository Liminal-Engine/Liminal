#ifndef __LIMINAL__LIB__WSI__PRIVATE__EGL_RESOURCE_HPP__
#define __LIMINAL__LIB__WSI__PRIVATE__EGL_RESOURCE_HPP__

#include "__WaylandResource.hpp"

extern "C" {
    #include <wayland-client.h>
}

#include <memory>

namespace wsi {
    namespace __private {
        class __EGLResource {
            public:
                __EGLResource(
                    wl_display *wlDisplay,
                    wl_surface *wlSurface,
                    int width,
                    int height
                );
                ~__EGLResource();

                void swapBuffers(void) const;

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };     
    } // namespace __private
} // namespace wsi

#endif // __LIMINAL__LIB__WSI__PRIVATE__EGL_RESOURCE_HPP__
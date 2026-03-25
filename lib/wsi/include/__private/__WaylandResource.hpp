#ifndef __LIMINAL__LIB__WSI__PRIVATE__WAYLAND_RESOURCE_HPP__
#define __LIMINAL__LIB__WSI__PRIVATE__WAYLAND_RESOURCE_HPP__

extern "C" {
    #include <wayland-client.h>
}

#include <memory>

namespace wsi {
    namespace __private {
        class __WaylandResource {
            public:
                __WaylandResource(
                    wl_display *display,
                    wl_compositor *compositor);
                ~__WaylandResource();

                wl_display *getDisplay(void) const;
                wl_surface *getSurface(void) const;

                void pollEvents(void) const;

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;                
        };
    } // namespace __private
} // namespace wsi

#endif // __LIMINAL__LIB__WSI__PRIVATE__WAYLAND_RESOURCES_HPP__
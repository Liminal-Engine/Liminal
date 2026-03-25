#ifndef __LIMINAL__LIB__WSI__PRIVATE__CONTEXT_HPP__
#define __LIMINAL__LIB__WSI__PRIVATE__CONTEXT_HPP__

extern "C" {
    #include <wayland-client.h>
    #include "__xdg-shell-client-protocol.h"
}

namespace wsi {
    namespace __private {
        struct __Context {
            wl_registry     *registry;
            wl_compositor   *compositor;
            xdg_wm_base     *xdgBase;
            wl_seat         *seat;

            __Context(wl_display *display);
            ~__Context();
        };     
    } // namespace __private
} // namespace wsi

#endif // __LIMINAL__LIB__WSI__PRIVATE__CONTEXT_HPP__
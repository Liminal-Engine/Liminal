#ifndef __LIMINAL__LIB__WSI__PRIVATE__XDG_SHELL_HPP__
#define __LIMINAL__LIB__WSI__PRIVATE__XDG_SHELL_HPP__

extern "C" {
    #include <wayland-client.h>
    #include "__xdg-shell-client-protocol.h"
}


#include <memory>

namespace wsi {
    namespace __private {
        class __XDGShell {
            public:
                __XDGShell(
                    xdg_wm_base *xdgBase,
                    wl_surface *surface,
                    const std::string &title
                );
                ~__XDGShell();

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace __private
} // namespace wsi


#endif // __LIMINAL__LIB__WSI__PRIVATE__XDG_SHELL_HPP__
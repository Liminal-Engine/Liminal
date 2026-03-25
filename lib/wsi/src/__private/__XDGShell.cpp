#include "__private/__XDGShell.hpp"

extern "C" {
    #include "__private/__xdg-shell-client-protocol.h"
}

#include <logger/logger.hpp>

#include <string.h>

namespace wsi {
    namespace __private {
        class __XDGShell::__Impl {
            private:

                static void __handlePing(void *data, xdg_wm_base *shell, uint32_t serial) {
                    xdg_wm_base_pong(shell, serial);
                }

                inline static const xdg_wm_base_listener __baseListener = { .ping = __handlePing };

                xdg_wm_base     *__base;
                xdg_surface     *__surface;
                xdg_toplevel    *__topLevel;

            public:
                __Impl(
                    xdg_wm_base *xdgBase,
                    wl_surface *surface,
                    const std::string &title
                ) :
                __base(xdgBase), // __XDGShell takes ownership of xdgBase
                __surface(nullptr),
                __topLevel(nullptr)
                {
                    // 1. Check if base is NULL
                    if (this->__base == nullptr) {
                        logger::fatal << "XDG base is NULL, aborting..." << std::endl;
                        return;
                    }
                    // 2. Add pong listener to XDG base
                    const xdg_wm_base_listener baseListener = { .ping = __handlePing };
                    if (xdg_wm_base_add_listener(this->__base, &this->__baseListener, this) != 0) {
                        logger::fatal << "XDG shell failed to add base listener" << std::endl;
                        return;
                    }
                    // 3. Create XDG surface
                    if ((this->__surface = xdg_wm_base_get_xdg_surface(this->__base, surface)) == nullptr) {
                        logger::fatal << "XDG shell failed to create XDG surface" << std::endl;
                        return;
                    }
                    // 4. Create top level
                    if ( (this->__topLevel = xdg_surface_get_toplevel(this->__surface)) == nullptr ) {
                        logger::fatal << "XDG shell failed to create top level" << std::endl;
                        return;
                    }
                    // 5. Set top surface title and commit
                    xdg_toplevel_set_title(this->__topLevel, title.c_str());
                    wl_surface_commit(surface);
                }

                ~__Impl() {
                    if (this->__topLevel) xdg_toplevel_destroy(this->__topLevel);
                    if (this->__surface) xdg_surface_destroy(this->__surface);
                    if (this->__base) xdg_wm_base_destroy(this->__base);
                }
        };

        __XDGShell::__XDGShell(xdg_wm_base *xdgBase, wl_surface *surface, const std::string &title) : __impl(std::make_unique<__Impl>(xdgBase, surface, title)) {}
        __XDGShell::~__XDGShell() = default;

    } // namespace __private
} // namespace wsi

#include "__private/__Context.hpp"

#include <logger/logger.hpp>

#include <string.h>

namespace wsi {
    namespace __private {

        void __registryGlobalBinder(void *data, wl_registry *wlRegistry, uint32_t id, const char *interface, uint32_t version) {
            __Context *context = static_cast<__Context *>(data);

            if (strcmp(interface, "wl_compositor") == 0) {
                context->compositor = (wl_compositor *)wl_registry_bind(wlRegistry, id, &wl_compositor_interface, 4);
            } else if (strcmp(interface, "xdg_wm_base") == 0) {
                context->xdgBase = (xdg_wm_base *)wl_registry_bind(wlRegistry, id, &xdg_wm_base_interface, 1);
            } else if (strcmp(interface, "wl_seat") == 0) {
                context->seat = (wl_seat *)wl_registry_bind(wlRegistry, id, &wl_seat_interface, 1);
            }
        }

        static inline const wl_registry_listener __registryListener { .global = __registryGlobalBinder, .global_remove = nullptr };

        __Context::__Context(wl_display *display) :
        registry(nullptr),
        compositor(nullptr),
        xdgBase(nullptr),
        seat(nullptr)
        {
            // 1. If display is NULL, abort
            if (display == nullptr) {
                logger::fatal << "Failed to initialize wayland context : display is NULL" << std::endl;
                return;
            }
            // 2. Create wlRegistry
            if ((this->registry = wl_display_get_registry(display)) == nullptr) {
                logger::error << "Failed to create wayland registry" << std::endl;
                return;
            }
            // 3. Add listener to registry
            if (wl_registry_add_listener(this->registry, &__registryListener, this) != 0) {
                logger::error << "Failed to add listener to wayland registry" << std::endl;
                return;
            }
            // 4. roundtrip (actual creation)
            if (wl_display_roundtrip(display) == -1) {
                logger::fatal << "Wayland resource failed to run roundtrip on registry" << std::endl;
                return;
            }
            // 5. Check creations
            if (this->compositor == nullptr) logger::fatal << "Failed to create compositor" << std::endl;
            if (this->xdgBase == nullptr) logger::fatal << "Failed to create XDG shell base" << std::endl;
            if (this->seat == nullptr) logger::fatal << "Failed to create seat" << std::endl;
        }
        
        __Context::~__Context() {
            if (this->registry) wl_registry_destroy(this->registry);
        }
    } // namespace __private
} // namespace wsi

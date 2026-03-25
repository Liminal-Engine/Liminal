#include "__private/__WaylandResource.hpp"

#include <logger/logger.hpp>

#include <string.h>

namespace wsi {
    namespace __private {
        class __WaylandResource::__Impl {
            private:

                wl_display      *__display;
                wl_compositor   *__compositor;
                wl_surface      *__surface;

            public:
                __Impl(wl_display *display, wl_compositor *compositor) :
                __display(display), // __WaylandResource takes ownership of display
                __compositor(compositor), // __WaylandResource takes ownership of compositor
                __surface(nullptr)
                {
                    
                    // 1. Surface creation
                    if ( (this->__surface = wl_compositor_create_surface(this->__compositor)) == nullptr ) {
                        logger::fatal << "Wayland resource failed to create surface" << std::endl;
                        return;
                    }
                }

                ~__Impl() {
                    if (this->__surface) wl_surface_destroy(this->__surface);
                    if (this->__compositor) wl_compositor_destroy(this->__compositor);
                    if (this->__display) {
                        wl_display_flush(this->__display);
                        wl_display_disconnect(this->__display);
                    }
                }

                wl_display *getDisplay(void) const { return this->__display; }
                wl_surface *getSurface(void) const { return this->__surface; }

                void pollEvents(void) const { wl_display_dispatch_pending(this->__display); }
        };

        __WaylandResource::__WaylandResource(wl_display *display, wl_compositor *compositor) : __impl(std::make_unique<__Impl>(display, compositor)) {}
        __WaylandResource::~__WaylandResource() = default;

        wl_display *__WaylandResource::getDisplay(void) const { return this->__impl->getDisplay(); }
        wl_surface *__WaylandResource::getSurface(void) const { return this->__impl->getSurface(); }
        void __WaylandResource::pollEvents(void) const { this->__impl->pollEvents(); }
    } // namespace __private
} // namespace wsi 

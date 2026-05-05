#ifndef __LIMINAL__LIB__WSI__PRIVATE__WAYLAND__SEAT__HPP__
#define __LIMINAL__LIB__WSI__PRIVATE__WAYLAND__SEAT__HPP__

#include "Event.hpp"
#include "EventQueue.hpp"

extern "C" {
    #include <wayland-client.h>
}

#include <memory>
#include <vector>

namespace wsi {
    namespace __private {
        class __WaylandSeat {
            public:
                __WaylandSeat(wl_seat *seat, EventQueue &eventQueue);
                ~__WaylandSeat();

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };     
    } // namespace __private
} // namespace wsi


#endif // __LIMINAL__LIB__WSI__PRIVATE__WAYLAND__SEAT__HPP__
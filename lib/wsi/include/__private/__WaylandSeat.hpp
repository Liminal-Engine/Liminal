#ifndef __LIMINAL__LIB__WSI__PRIVATE__WAYLAND__SEAT__HPP__
#define __LIMINAL__LIB__WSI__PRIVATE__WAYLAND__SEAT__HPP__

extern "C" {
    #include <wayland-client.h>
}

#include <memory>

namespace wsi {
    namespace __private {
        class __WaylandSeat {
            public:
                __WaylandSeat(wl_seat *seat);
                ~__WaylandSeat();

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };     
    } // namespace __private
} // namespace wsi


#endif // __LIMINAL__LIB__WSI__PRIVATE__WAYLAND__SEAT__HPP__
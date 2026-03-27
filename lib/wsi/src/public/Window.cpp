#include "Window.hpp"
#include "__private/__Context.hpp"
#include "__private/__WaylandResource.hpp"
#include "__private/__XDGShell.hpp"
#include "__private/__EGLResource.hpp"
#include "__private/__WaylandSeat.hpp"


#include <logger/logger.hpp>

#include <string.h>
#include <functional>

namespace wsi {
    class Window::__Impl {
        private:

            static wl_display *__loadDisplay(void) {
                wl_display *display = wl_display_connect(nullptr);
                if (display == nullptr) {
                    logger::fatal << "Cannot find a wayland server, please make sure wayland is installed" << std::endl;
                }
                return display;
            }
        
            wl_display *                        __display;
            __private::__Context                __registry;
            __private::__WaylandResource        __waylandResource;
            __private::__XDGShell               __xdgShell;
            __private::__EGLResource            __eglResource;
            __private::__WaylandSeat            __waylandSeat;
            std::vector<Event>                  __eventQueue;

        public:
            __Impl(int width, int height, const std::string &title) :
            __display(__loadDisplay()),
            __registry(this->__display),
            __waylandResource(this->__display, this->__registry.compositor),
            __xdgShell(this->__registry.xdgBase, this->__waylandResource.getSurface(), title),
            __eglResource(this->__display, this->__waylandResource.getSurface(), width, height),
            __waylandSeat(this->__registry.seat, this->__eventQueue)
            {
               
            }

            ~__Impl() {
               
            }
            // FIXME: get rid of this method, use event == close, window.close instead
            bool shouldClose(void) const { return false; }

            std::vector<Event> pollEvents(void) {
                this->__waylandResource.pollEvents();
                return this->__eventQueue;
            }

            void display(void) {
                this->__eglResource.swapBuffers();
            }
    };

    Window::Window(int width, int height, const std::string &title) :
    __impl(std::make_unique<__Impl>(width, height, title))
    {}

    Window::~Window() = default;

    bool Window::shouldClose(void) const { return this->__impl->shouldClose(); }
    std::vector<Event> Window::pollEvents(void) { return this->__impl->pollEvents(); }
    void Window::display(void) {  this->__impl->display(); }

} // namespace wsi

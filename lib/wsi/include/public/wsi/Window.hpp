#ifndef __LIMINAL__LIB__WSI__WINDOW_HPP__
#define __LIMINAL__LIB__WSI__WINDOW_HPP__

#include <cstdint>
#include <string>
#include <memory>

namespace wsi {
    class Window {
        public:
            Window(int width, int height, const std::string &name);
            ~Window();

            Window(const Window&) = delete;            // No copy
            Window& operator=(const Window&) = delete; // No affectation
            Window(Window&&) = delete;                 // No move
            Window& operator=(Window&&) = delete;      // No affectation by moving

            bool shouldClose() const;
            void pollEvents();
            void display();

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;

    };
} // namespace wsi


#endif // __LIMINAL__LIB__WSI__WINDOW_HPP__
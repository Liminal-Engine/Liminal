#include "Application.hpp"

namespace host {
    class Application::__Impl {
        private:

        public:
            __Impl(void) {

            }
    };

    Application::Application(void) :
    __impl(std::make_unique<__Impl>())
    {

    }

    Application::~Application() = default;
} // namespace host

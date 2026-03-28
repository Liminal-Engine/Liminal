#include "EventHandler.hpp"


#include <vector>

namespace leh {
    class EventHandler::__Impl {
        private:

            struct __Binding {
                wsi::Event event;
                std::function<void()> action;
                __Binding(const wsi::Event &event, const std::function<void()> &action) :
                event(event), action(action) {}
            };

            std::vector<__Binding> __bindings;

        public:
            __Impl(void) : __bindings{} {}
            ~__Impl() {}

            void add(const wsi::Event &event, const std::function<void()> &action) {
                this->__bindings.push_back(__Binding(event, std::move(action)));
            }

            void process(const std::vector<wsi::Event> &eventQueue) const {
                for (const wsi::Event &queuedEvent : eventQueue) {
                    for (const __Binding &binding: this->__bindings) {
                        if (binding.event == queuedEvent) {
                            binding.action();
                        }
                    }
                }
            }
    };

    EventHandler::EventHandler(void) : __impl(std::make_unique<__Impl>()) {}
    EventHandler::~EventHandler() = default;
    EventHandler &EventHandler::__instance(void) {
        static EventHandler instance;
        return instance;
    }

    void EventHandler::add(const wsi::Event &event, const std::function<void()> &action) { __instance().__impl->add(event, std::move(action)); }
    void EventHandler::process(const std::vector<wsi::Event> &eventQueue) { __instance().__impl->process(eventQueue); }
} // namespace leh

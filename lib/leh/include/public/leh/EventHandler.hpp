#ifndef __LIMINAL__LIB__LEH__EVENT_HANDLER_HPP__
#define __LIMINAL__LIB__LEH__EVENT_HANDLER_HPP__

#include <wsi/Event.hpp>
#include <wsi/EventQueue.hpp>

#include <memory>
#include <functional>

namespace leh {
    class EventHandler {
        public:
            EventHandler(const EventHandler&) = delete;
            EventHandler(EventHandler&&) = delete;
            EventHandler &operator=(const EventHandler&) = delete;
            EventHandler &operator=(EventHandler&&) = delete;

            template<typename Action, typename... Args>
            static void add(const wsi::Event &event, Action A, Args... a) { add(event, std::function<void()>([=]() { A(a...); })); };

            static void add(const wsi::Event &event, const std::function<void()> &action);

            static void process(const wsi::EventQueue &eventQueue);

        private:
            EventHandler(void);
            ~EventHandler();
            static EventHandler &__instance(void);

            class __Impl;
            std::unique_ptr<__Impl> __impl;

    };
} // namespace leh


#endif // __LIMINAL__LIB__LEH__EVENT_HANDLER_HPP__
#include "__private/__WaylandSeat.hpp"

#include <logger/logger.hpp>
#include <unistd.h>

namespace wsi {
    namespace __private {
        class __WaylandSeat::__Impl {
            private:

                static void __handleKeyboardKeymap(void *data, wl_keyboard *kb, uint32_t format, int32_t fd, uint32_t size) {
                    // Wayland envoie ici la disposition du clavier (AZERTY/QWERTY) via un file descriptor
                    // Pour l'instant, on ferme juste le FD pour éviter les fuites de ressources
                    close(fd);
                }

                static void __handleKeyboardKey(void *data, wl_keyboard *keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state) {
                    logger::info << "key: " << key << std::endl;
                }

                static void __handleKeyboardEnter(void *data, wl_keyboard *kb, uint32_t serial, wl_surface *surf, wl_array *keys) {}
                static void __handleKeyboardLeave(void *data, wl_keyboard *kb, uint32_t serial, wl_surface *surf) {}
                static void __handleKeyboardModifiers(void *data, wl_keyboard *kb, uint32_t serial, uint32_t dep, uint32_t lat, uint32_t lock, uint32_t group) {}
                static void __handleKeyboardRepeat(void *data, wl_keyboard *kb, int32_t rate, int32_t delay) {}

                inline static const wl_keyboard_listener __keyboardListener = {
                    .keymap = __handleKeyboardKeymap,
                    .enter = __handleKeyboardEnter,
                    .leave = __handleKeyboardLeave,
                    .key = __handleKeyboardKey,
                    .modifiers = __handleKeyboardModifiers,
                    .repeat_info = __handleKeyboardRepeat
                };

                wl_seat *__seat;
                wl_keyboard *__keyboard;

            public:
                __Impl(wl_seat *seat) :
                __seat(seat), // takes ownership of seat
                __keyboard(nullptr)
                {
                    // 1. Check seat
                    if (this->__seat == nullptr) {
                        logger::fatal << "Failed to initialize wayland seat, seat is NULL" << std::endl;
                        return;
                    }
                    // 2. Create keyboard
                    if ( (this->__keyboard = wl_seat_get_keyboard(this->__seat)) == nullptr ) {
                        logger::fatal << "Wayland seat faled to create keyboard" << std::endl;
                        return;
                    }
                    // 3. Add listener
                    if (wl_keyboard_add_listener(this->__keyboard, &__keyboardListener, this) != 0) {
                        logger::fatal << "Wayland seat failed to add keyboard listener" << std::endl;
                        return;
                    }

                }

                ~__Impl() {
                    // if (this->__keyboard) wl_keyboard_release(this->__keyboard);
                    // if (this->__seat) wl_seat_release(this->__seat);
                }
        };

        __WaylandSeat::__WaylandSeat(wl_seat *seat) : __impl(std::make_unique<__Impl>(seat)) {}
        __WaylandSeat::~__WaylandSeat() = default;
    } // namespace __private
} // namespace wsi

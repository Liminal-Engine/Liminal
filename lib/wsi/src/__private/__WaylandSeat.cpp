#include "__private/__WaylandSeat.hpp"
#include "KeyboardEvent.hpp"

#include <xkbcommon/xkbcommon.h>
#include <sys/mman.h>

#include <logger/logger.hpp>
#include <unistd.h>

namespace wsi {
    namespace __private {
        class __WaylandSeat::__Impl {
            private:

                static Key __xkbKeySymToKey(xkb_keysym_t xkbKeySym) {
                    switch (xkbKeySym) {
                        case XKB_KEY_A: case XKB_KEY_a: return Key::A;
                        case XKB_KEY_B: case XKB_KEY_b: return Key::B;
                        case XKB_KEY_C: case XKB_KEY_c: return Key::C;
                        case XKB_KEY_D: case XKB_KEY_d: return Key::D;
                        case XKB_KEY_E: case XKB_KEY_e: return Key::E;
                        case XKB_KEY_F: case XKB_KEY_f: return Key::F;
                        case XKB_KEY_G: case XKB_KEY_g: return Key::G;
                        case XKB_KEY_H: case XKB_KEY_h: return Key::H;
                        case XKB_KEY_I: case XKB_KEY_i: return Key::I;
                        case XKB_KEY_J: case XKB_KEY_j: return Key::J;
                        case XKB_KEY_K: case XKB_KEY_k: return Key::K;
                        case XKB_KEY_L: case XKB_KEY_l: return Key::L;
                        case XKB_KEY_M: case XKB_KEY_m: return Key::M;
                        case XKB_KEY_N: case XKB_KEY_n: return Key::N;
                        case XKB_KEY_O: case XKB_KEY_o: return Key::O;
                        case XKB_KEY_P: case XKB_KEY_p: return Key::P;
                        case XKB_KEY_Q: case XKB_KEY_q: return Key::Q;
                        case XKB_KEY_R: case XKB_KEY_r: return Key::R;
                        case XKB_KEY_S: case XKB_KEY_s: return Key::S;
                        case XKB_KEY_T: case XKB_KEY_t: return Key::T;
                        case XKB_KEY_U: case XKB_KEY_u: return Key::U;
                        case XKB_KEY_V: case XKB_KEY_v: return Key::V;
                        case XKB_KEY_W: case XKB_KEY_w: return Key::W;
                        case XKB_KEY_X: case XKB_KEY_x: return Key::X;
                        case XKB_KEY_Y: case XKB_KEY_y: return Key::Y;
                        case XKB_KEY_Z: case XKB_KEY_z: return Key::Z;
                        case XKB_KEY_0: return Key::NUM_0; case XKB_KEY_1: return Key::NUM_1; case XKB_KEY_2: return Key::NUM_2;
                        case XKB_KEY_3: return Key::NUM_3; case XKB_KEY_4: return Key::NUM_4; case XKB_KEY_5: return Key::NUM_5;
                        case XKB_KEY_6: return Key::NUM_6; case XKB_KEY_7: return Key::NUM_7; case XKB_KEY_8: return Key::NUM_8;
                        case XKB_KEY_9: return Key::NUM_9;
                        case XKB_KEY_Return: return Key::ENTER;
                        case XKB_KEY_Escape: return Key::ESCAPE;
                        case XKB_KEY_BackSpace: return Key::BACKSPACE;
                        case XKB_KEY_Tab: return Key::TAB;
                        case XKB_KEY_space: return Key::SPACE;
                        case XKB_KEY_Shift_L: return Key::SHIFT_LEFT;
                        case XKB_KEY_Shift_R: return Key::SHIFT_RIGHT;
                        case XKB_KEY_Control_L: return Key::CTRL_LEFT;
                        case XKB_KEY_Control_R: return Key::CTRL_RIGHT;
                        case XKB_KEY_Alt_L: return Key::ALT_LEFT;
                        case XKB_KEY_Alt_R: return Key::ALT_RIGHT;
                        case XKB_KEY_Caps_Lock: return Key::CAPS_LOCK;
                        case XKB_KEY_Num_Lock: return Key::NUM_LOCK;
                        case XKB_KEY_Super_L: return Key::LOGO_LEFT;
                        case XKB_KEY_Super_R: return Key::LOGO_RIGHT;
                        case XKB_KEY_Up: return Key::ARROW_UP;
                        case XKB_KEY_Down: return Key::ARROW_DOWN;
                        case XKB_KEY_Left: return Key::ARROW_LEFT;
                        case XKB_KEY_Right: return Key::ARROW_RIGHT;
                        case XKB_KEY_F1: return Key::F1; case XKB_KEY_F2: return Key::F2; case XKB_KEY_F3: return Key::F3;
                        case XKB_KEY_F4: return Key::F4; case XKB_KEY_F5: return Key::F5; case XKB_KEY_F6: return Key::F6;
                        case XKB_KEY_F7: return Key::F7; case XKB_KEY_F8: return Key::F8; case XKB_KEY_F9: return Key::F9;
                        case XKB_KEY_F10: return Key::F10; case XKB_KEY_F11: return Key::F11; case XKB_KEY_F12: return Key::F12;
                    }
                    return Key::UNKNOWN;
                }
            
                static void __handleKeyboardKeymap(void *data, wl_keyboard *kb, uint32_t format, int32_t fd, uint32_t size) {
                    __Impl *seat = static_cast<__Impl*>(data);
                    // 1. Map file in RAM
                    char *mappedData = (char *)mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
                    if (mappedData == MAP_FAILED) {
                        logger::fatal << "Wayland seat failed to map keyboard map file to RAM" << std::endl;
                        close(fd);
                        return;
                    }
                    // 2. Create XKB keymap
                    seat->__xkbMap = xkb_keymap_new_from_string(seat->__xkbContext, mappedData, XKB_KEYMAP_FORMAT_TEXT_V1, XKB_KEYMAP_COMPILE_NO_FLAGS);
                    if (seat->__xkbMap == nullptr) {
                        logger::fatal << "Wayland seat failed to compile XKB keymap" << std::endl;
                        close(fd);
                        return;
                    }
                    munmap(mappedData, size);
                    close(fd);
                    // 3. Create the state (the brain) which will follow the Shifts/Caps lock, etc...
                    xkb_state_unref(seat->__xkbState);
                    seat->__xkbState = xkb_state_new(seat->__xkbMap);
                    if (seat->__xkbState == nullptr) {
                        logger::fatal << "Wayland seat failed to create XKB state" << std::endl;
                        return;
                    }
                }

                static void __handleKeyboardKey(void *data, wl_keyboard *keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state) {
                    __Impl *seat = static_cast<__Impl *>(data);
                    if (seat->__xkbState == nullptr) {
                        logger::error << "Keyboard event detected, but XKB state not initialized" << std::endl;
                        return;
                    }
                    uint32_t xkbKeyCode = key + 8;
                    xkb_keysym_t xkbKeySym = xkb_state_key_get_one_sym(seat->__xkbState, xkbKeyCode);
                    KeyboardEvent event;
                    event.key = __xkbKeySymToKey(xkbKeySym);
                    event.status = state == WL_KEYBOARD_KEY_STATE_PRESSED ? KeyStatus::PRESSED : KeyStatus::RELEASED;
                    event.mod.shift = xkb_state_mod_name_is_active(seat->__xkbState, XKB_MOD_NAME_SHIFT, XKB_STATE_MODS_EFFECTIVE);
                    event.mod.ctrl = xkb_state_mod_name_is_active(seat->__xkbState, XKB_MOD_NAME_CTRL, XKB_STATE_MODS_EFFECTIVE);
                    event.mod.alt = xkb_state_mod_name_is_active(seat->__xkbState, XKB_MOD_NAME_ALT, XKB_STATE_MODS_EFFECTIVE);
                    event.mod.caps = xkb_state_mod_name_is_active(seat->__xkbState, XKB_MOD_NAME_CAPS, XKB_STATE_MODS_EFFECTIVE);
                    event.mod.logo = xkb_state_mod_name_is_active(seat->__xkbState, XKB_MOD_NAME_LOGO, XKB_STATE_MODS_EFFECTIVE);
                    event.mod.num = xkb_state_mod_name_is_active(seat->__xkbState, XKB_MOD_NAME_NUM, XKB_STATE_MODS_EFFECTIVE);
                    seat->__dispatch(event);
                }

                static void __handleKeyboardEnter(void *data, wl_keyboard *kb, uint32_t serial, wl_surface *surf, wl_array *keys) {}
                static void __handleKeyboardLeave(void *data, wl_keyboard *kb, uint32_t serial, wl_surface *surf) {}

                static void __handleKeyboardModifiers(void *data, wl_keyboard *kb, uint32_t serial, uint32_t dep, uint32_t lat, uint32_t lock, uint32_t group) {
                    __Impl *seat = static_cast<__Impl *>(data);
                    if (seat->__xkbContext == nullptr) {
                        logger::error << "Keyboard state modification detected but XKB is not initialized" << std::endl;
                        return;
                    }
                    xkb_state_update_mask(seat->__xkbState, dep, lat, lock, 0, 0, group);
                }

                static void __handleKeyboardRepeat(void *data, wl_keyboard *kb, int32_t rate, int32_t delay) {}

                inline static const wl_keyboard_listener __keyboardListener = {
                    .keymap = __handleKeyboardKeymap,
                    .enter = __handleKeyboardEnter,
                    .leave = __handleKeyboardLeave,
                    .key = __handleKeyboardKey,
                    .modifiers = __handleKeyboardModifiers,
                    .repeat_info = __handleKeyboardRepeat
                };

                inline void __dispatch(const Event &event) { this->__eventQueueRef.push_back(event); }
                
                wl_seat             *__seat;
                wl_keyboard         *__keyboard;
                xkb_context         *__xkbContext;
                xkb_keymap          *__xkbMap;
                xkb_state           *__xkbState;
                std::vector<Event>  &__eventQueueRef;
                
            public:
                __Impl(wl_seat *seat, std::vector<Event> &eventQueue) :
                __seat(seat), // takes ownership of seat
                __keyboard(nullptr),
                __xkbContext(nullptr),
                __xkbMap(nullptr),
                __xkbState(nullptr),
                __eventQueueRef(eventQueue)
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
                    // 3. Load XKB context
                    if ((this->__xkbContext = xkb_context_new(XKB_CONTEXT_NO_FLAGS)) == nullptr) {
                        logger::fatal << "Wayland seat failed to load XKB context" << std::endl;
                        return;
                    }
                    // 4. Add listener
                    if (wl_keyboard_add_listener(this->__keyboard, &__keyboardListener, this) != 0) {
                        logger::fatal << "Wayland seat failed to add keyboard listener" << std::endl;
                        return;
                    }
                }

                ~__Impl() {
                    if (this->__keyboard) wl_keyboard_release(this->__keyboard);
                    if (this->__seat) wl_seat_release(this->__seat);
                    if (this->__xkbState) xkb_state_unref(this->__xkbState);
                    if (this->__xkbMap) xkb_keymap_unref(this->__xkbMap);
                    if (this->__xkbContext) xkb_context_unref(this->__xkbContext);
                }
        };

        __WaylandSeat::__WaylandSeat(wl_seat *seat, std::vector<Event> &eventQueue) : __impl(std::make_unique<__Impl>(seat, eventQueue)) {}
        __WaylandSeat::~__WaylandSeat() = default;
    } // namespace __private
} // namespace wsi

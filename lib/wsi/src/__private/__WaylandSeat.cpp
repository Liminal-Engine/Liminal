#include "__private/__WaylandSeat.hpp"
#include "Event.hpp"

#include <xkbcommon/xkbcommon.h>
#include <sys/mman.h>

#include <logger/logger.hpp>
#include <unistd.h>

namespace wsi {
    namespace __private {
        class __WaylandSeat::__Impl {
            private:
            
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
                    logger::info << "wayland key: " << key << std::endl;
                    uint32_t xkbKeyCode = key + 8;
                    xkb_keysym_t xkbKeySym = xkb_state_key_get_one_sym(seat->__xkbState, xkbKeyCode);
                    char buffer[128];
                    xkb_state_key_get_utf8(seat->__xkbState, xkbKeyCode, buffer, sizeof(buffer));
                    logger::info << "XKB keycode=" << xkbKeyCode << ", XKB key sym=" << xkbKeySym << ", XKB text=" << buffer << std::endl;
                    KeyEvent event;
                    event.code = xkbKeyCode;
                    event.text = std::string(buffer);
                    event.status = WL_KEYBOARD_KEY_STATE_PRESSED ? KeyStatus::PRESSED : KeyStatus::RELEASED;
                    event.mod.shift = xkb_state_mod_name_is_active(seat->__xkbState, XKB_MOD_NAME_SHIFT, XKB_STATE_MODS_EFFECTIVE);
                    event.mod.ctrl = xkb_state_mod_name_is_active(seat->__xkbState, XKB_MOD_NAME_CTRL, XKB_STATE_MODS_EFFECTIVE);
                    event.mod.alt = xkb_state_mod_name_is_active(seat->__xkbState, XKB_MOD_NAME_ALT, XKB_STATE_MODS_EFFECTIVE);
                    event.mod.caps = xkb_state_mod_name_is_active(seat->__xkbState, XKB_MOD_NAME_CAPS, XKB_STATE_MODS_EFFECTIVE);
                    event.mod.logo = xkb_state_mod_name_is_active(seat->__xkbState, XKB_MOD_NAME_LOGO, XKB_STATE_MODS_EFFECTIVE);
                    event.mod.num = xkb_state_mod_name_is_active(seat->__xkbState, XKB_MOD_NAME_NUM, XKB_STATE_MODS_EFFECTIVE);
                    seat->__eventQueueRef.push_back(event);
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

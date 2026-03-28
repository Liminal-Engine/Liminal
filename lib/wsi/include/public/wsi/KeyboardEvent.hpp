#ifndef __LIMINAL__LIB__WSI__KEYBOARD_EVENT_HPP__
#define __LIMINAL__LIB__WSI__KEYBOARD_EVENT_HPP__

#include <string>

namespace wsi {
    enum class Key {
        UNKNOWN = 0,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        NUM_0, NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9,
        ENTER, ESCAPE, BACKSPACE, TAB, SPACE,
        SHIFT_LEFT, SHIFT_RIGHT, CTRL_LEFT, CTRL_RIGHT, ALT_LEFT, ALT_RIGHT,
        CAPS_LOCK, NUM_LOCK, LOGO_LEFT, LOGO_RIGHT,
        ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    };

    enum class KeyStatus { PRESSED, RELEASED };

    struct KeyMod {
        bool    shift;
        bool    ctrl;
        bool    alt;
        bool    caps;
        bool    logo;
        bool    num;
        KeyMod(void);
        bool operator==(const KeyMod &other) const;
    };

     struct KeyboardEvent {
        Key             key;
        KeyStatus       status;
        KeyMod          mod;
        KeyboardEvent(void);
        bool operator==(const KeyboardEvent &other) const;
    };

    std::string toStr(Key key);
    std::string toStr(KeyStatus keyStatus);
} // namespace wsi

#endif // __LIMINAL__LIB__WSI__KEYBOARD_EVENT_HPP__
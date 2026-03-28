#include "KeyboardEvent.hpp"

namespace wsi {
    KeyMod::KeyMod(void) :
    shift(false), ctrl(false), alt(false), caps(false), logo(false), num(false)
    {}

    KeyboardEvent::KeyboardEvent(void) :
    key(Key::UNKNOWN), status(KeyStatus::RELEASED), mod()
    {}

    bool KeyMod::operator==(const KeyMod &other) const {
        return (
            this->shift ==  other.shift     &&
            this->ctrl  ==  other.ctrl      &&
            this->alt   ==  other.alt       &&
            this->caps  ==  other.caps      &&
            this->logo  ==  other.logo      &&
            this->num   ==  other.num
        );
    }

    bool KeyboardEvent::operator==(const KeyboardEvent &other) const {
        return (
            this->key       ==  other.key       &&
            this->status    ==  other.status    &&
            this->mod       ==  other.mod // FIXME: remove mod comparison, maybe move mods somewhere else
        );
    }

    std::string toStr(Key key) {
        switch (key) {
            case Key::A: return "A";
            case Key::B: return "B";
            case Key::C: return "C";
            case Key::D: return "D";
            case Key::E: return "E";
            case Key::F: return "F";
            case Key::G: return "G";
            case Key::H: return "H";
            case Key::I: return "I";
            case Key::J: return "J";
            case Key::K: return "K";
            case Key::L: return "L";
            case Key::M: return "M";
            case Key::N: return "N";
            case Key::O: return "O";
            case Key::P: return "P";
            case Key::Q: return "Q";
            case Key::R: return "R";
            case Key::S: return "S";
            case Key::T: return "T";
            case Key::U: return "U";
            case Key::V: return "V";
            case Key::W: return "W";
            case Key::X: return "X";
            case Key::Y: return "Y";
            case Key::Z: return "Z";
            case Key::NUM_0: return "0";
            case Key::NUM_1: return "1";
            case Key::NUM_2: return "2";
            case Key::NUM_3: return "3";
            case Key::NUM_4: return "4";
            case Key::NUM_5: return "5";
            case Key::NUM_6: return "6";
            case Key::NUM_7: return "7";
            case Key::NUM_8: return "8";
            case Key::NUM_9: return "9";
            case Key::ENTER: return "ENTER";
            case Key::ESCAPE: return "ESCAPE";
            case Key::BACKSPACE: return "BACKSPACE";
            case Key::TAB: return "TAB";
            case Key::SPACE: return "SPACE";
            case Key::SHIFT_LEFT: return "SHIFT_LEFT";
            case Key::SHIFT_RIGHT: return "SHIFT_RIGHT";
            case Key::CTRL_LEFT: return "CTRL_LEFT";
            case Key::CTRL_RIGHT: return "CTRL_RIGHT";
            case Key::ALT_LEFT: return "ALT_LEFT";
            case Key::ALT_RIGHT: return "ALT_RIGHT";
            case Key::CAPS_LOCK: return "CAPS_LOCK";
            case Key::NUM_LOCK: return "NUM_LOCK";
            case Key::LOGO_LEFT: return "LOGO_LEFT";
            case Key::LOGO_RIGHT: return "LOGO_RIGHT";
            case Key::ARROW_UP: return "ARROW_UP";
            case Key::ARROW_DOWN: return "ARROW_DOWN";
            case Key::ARROW_LEFT: return "ARROW_LEFT";
            case Key::ARROW_RIGHT: return "ARROW_RIGHT";
            case Key::F1: return "F1";
            case Key::F2: return "F2";
            case Key::F3: return "F3";
            case Key::F4: return "F4";
            case Key::F5: return "F5";
            case Key::F6: return "F6";
            case Key::F7: return "F7";
            case Key::F8: return "F8";
            case Key::F9: return "F9";
            case Key::F10: return "F10";
            case Key::F11: return "F11";
            case Key::F12: return "F12";
            case Key::UNKNOWN: default: return "UNKNOWN";
        }
    }

    std::string toStr(KeyStatus keyStatus) {
        switch (keyStatus) {
            case KeyStatus::PRESSED: return "PRESSED";
            case KeyStatus::RELEASED: return "RELEASED";
            default: return "UNKNOWN";
        }
    }
} // namespace wsi

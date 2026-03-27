#include "Event.hpp"

namespace wsi {
    KeyMod::KeyMod(void) :
    shift(false), ctrl(false), alt(false), caps(false), logo(false), num(false)
    {}

    KeyEvent::KeyEvent(void) :
    code(0), text(""), status(KeyStatus::RELEASED), mod()
    {}
} // namespace wsi

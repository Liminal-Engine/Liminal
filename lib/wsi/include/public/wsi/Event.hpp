#ifndef __LIMINAL__LIB__WSI__EVENT_HPP__
#define __LIMINAL__LIB__WSI__EVENT_HPP__

#include <cstdint>
#include <string>
#include <variant>

namespace wsi {

    enum class KeyStatus { PRESSED, RELEASED };

    struct KeyMod {
        bool    shift;
        bool    ctrl;
        bool    alt;
        bool    caps;
        bool    logo;
        bool    num;
        KeyMod(void);
    };

    struct KeyEvent {
        uint32_t        code;
        std::string     text;
        KeyStatus       status;
        KeyMod          mod;
        KeyEvent(void);
    };

    using Event = std::variant<KeyEvent>;

} // namespace wsi


#endif // __LIMINAL__LIB__WSI__EVENT_HPP__
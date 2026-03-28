#ifndef __LIMINAL__LIB__WSI__EVENT_HPP__
#define __LIMINAL__LIB__WSI__EVENT_HPP__

#include "KeyboardEvent.hpp"

#include <variant>

namespace wsi {

    using Event = std::variant<KeyboardEvent>;

    bool operator==(const Event &lsh, const Event &rhs);

} // namespace wsi


#endif // __LIMINAL__LIB__WSI__EVENT_HPP__
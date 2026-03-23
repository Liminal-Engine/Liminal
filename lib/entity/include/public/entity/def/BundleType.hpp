#ifndef __LIMINAL__LIB__ENTITY__BUNDLE__BUNDLE_TYPE_HPP__
#define __LIMINAL__LIB__ENTITY__BUNDLE__BUNDLE_TYPE_HPP__

#include "entity/def/BundleType.hpp"
#include "entity/bundle/Object.hpp"
#include "entity/bundle/Camera.hpp"

#include <concepts>

namespace entity {
    namespace def {
        template<typename T>
        concept BundleType = 
            std::is_same_v<T, bundle::Object>||
            std::is_same_v<T, bundle::Camera>;
    } // namespace def
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__BUNDLE__BUNDLE_TYPE_HPP__
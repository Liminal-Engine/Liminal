#ifndef LIMINAL_LIB_VULKAN_WRAPPER__LAYER__VULKAN_LAYER_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__LAYER__VULKAN_LAYER_WRAPPERS_HPP_

#include <vector>

namespace vulkan_wrapper {
    namespace _layer {

        using _Layers_t = std::vector<const char *>;

        /**
         * @brief Loads additional layers
         * 
         * @return The The loaded layers (_Layers_t)
         */
        _Layers_t _load(void);        

    } // namespace _layer 
} // namespace vulkan_wrapper


#endif // LIMINAL_LIB_VULKAN_WRAPPER__LAYER__VULKAN_LAYER_WRAPPERS_HPP_
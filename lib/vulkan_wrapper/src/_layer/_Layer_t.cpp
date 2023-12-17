#include "_layer/_Layer_t.hpp"

#include <vulkan/vulkan.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdexcept>

namespace vulkan_wrapper {
    namespace _layer {

        _Layers_t _load(void) {
            _Layers_t wanted_layers = { "VK_LAYER_KHRONOS_validation" }; // hard coded for now
            bool all_found = true;
            bool found = false;
            uint32_t n_available_layers = 0;

            vkEnumerateInstanceLayerProperties(&n_available_layers, nullptr);
            std::vector<VkLayerProperties> available_layers(n_available_layers);
            vkEnumerateInstanceLayerProperties(&n_available_layers, available_layers.data());
            for (const char *wanted_layer : wanted_layers) {
                found = false;
                for (const VkLayerProperties &available_layer : available_layers) {
                    if (strcmp(available_layer.layerName, wanted_layer) == 0) {
                        found = true;
                        break;                        
                    }
                }
                if (found == false) {
                    std::cerr << "Error : " << wanted_layer << " layer is not available" << '\n';
                    all_found = false;
                }
            }
            if (all_found == false) {
                std::cerr << std::endl; //flush buffer
                throw std::runtime_error("Failed to find all wanted layers");
            }
            return wanted_layers;
        }

    } // namespace _layer 
} // namespace vulkan_wrapper


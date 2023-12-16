#include "VulkanHdl.hpp"

int main() {
    vulkan_wrapper::VulkanHdl hanlder;

    while (glfwWindowShouldClose(hanlder._window) == false) {
        glfwPollEvents();
        hanlder.drawFrame();
    }
}
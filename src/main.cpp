#include "VulkanHdl.hpp"

int main() {
    vulkan_wrapper::VulkanHdl handler;

    while (handler.window.shouldClose() == false) {
        handler.window.pollEvents();
        handler.drawFrame();
    }
    handler.waitIdle();
}

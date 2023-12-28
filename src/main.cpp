#include "VulkanHdl.hpp"
#include "InFile.hpp"
#include "InJson.hpp"

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

int main() {
    vulkan_wrapper::VulkanHdl handler;
    liminal_fs::InFile file("./README.md");
    file.open();
    file.read();
    file.close();
    std::cout << file.get_content() << std::endl;
    std::cout << "extension  = " << file.get_extension() << " has extension = " << file.has_extension() << std::endl;
    liminal_json_io::InJson json;

    std::cout << "before parsing" << std::endl;
    json.parse("./tests/assets/mediumSized.json");
    std::cout << "after parsing" << std::endl;

    while (handler.window.shouldClose() == false) {
        handler.window.pollEvents();
        handler.drawFrame();
    }
    handler.waitIdle();
}

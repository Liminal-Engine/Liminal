#include "VulkanHdl.hpp"
#include "InFile.hpp"
#include "InJson.hpp"

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <string>

int main() {
    vulkan_wrapper::VulkanHdl handler;
    liminal_fs::InFile file("./README.md");
    file.open();
    file.read();
    file.close();
    std::cout << file.get_content() << std::endl;
    std::cout << "extension  = " << file.get_extension() << " has extension = " << file.has_extension() << std::endl;
    liminal_json_io::InJson json;

    json.parse("./tests/assets/bitNestedNoErrors.json");

    std::cout << json.get<liminal_json_io::types::FloatNum_t>("address.story.right").value() << std::endl;

    while (handler.window.shouldClose() == false) {
        handler.window.pollEvents();
        handler.drawFrame();
    }
    handler.waitIdle();
}

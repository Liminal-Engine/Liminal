#include "VulkanHdl.hpp"
#include "InFile.hpp"
#include "InJson.hpp"
#include "types/types.hpp"

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

    liminal_json_io::types::Object_t object = json.get<liminal_json_io::types::Object_t>("address").value();
    std::cout << json.get<liminal_json_io::types::Object_t>("address").value().get<liminal_json_io::types::FloatNum_t>("anotherData").value() << std::endl;
    std::cout << json.get<liminal_json_io::types::FloatNum_t>("address.anotherData").value() << std::endl;
    std::cout << json.get<liminal_json_io::types::IntNum_t>("address.story.left").value() << std::endl;
    std::cout << json.get<liminal_json_io::types::String_t>("hobbies[4].secondNestedHobbies[1]").value() << std::endl;
    liminal_json_io::types::Object_t mainObject = json.get<liminal_json_io::types::Object_t>().value();

    while (handler.window.shouldClose() == false) {
        handler.window.pollEvents();
        handler.drawFrame();
    }
    handler.waitIdle();
}

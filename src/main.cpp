/**
 * @file main.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "liminal_json_io/InJson.hpp"
#include "liminal_json_io/Json.hpp"
#include "liminal_json_io/OutJson.hpp"
#include "liminal_json_io/types.hpp"
#include "liminal_json_io/Status.hpp"

#include "liminal_windowing/WindowWrapper.hpp"

#include "vulkan_wrapper/VulkanHdl.hpp"

#include "liminal_fs/FileType.hpp"
#include "liminal_fs/InFile.hpp"
#include "liminal_fs/OutFile.hpp"
#include "liminal_fs/Status.hpp"
#include "liminal_fs/path/path.hpp"

#include "liminal_string_extras/string.hpp"

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

    liminal_json_io::types::Object_t object{json.get<liminal_json_io::types::Object_t>("address").value()};
    
    
    std::cout << json.get<liminal_json_io::types::Object_t>("address").value().get<liminal_json_io::types::FloatNum_t>("anotherData").value() << std::endl;
    std::cout << json.get<liminal_json_io::types::Array_t>("hobbies").value().get<liminal_json_io::types::String_t>(1).value() << std::endl;
    std::cout << json.get<liminal_json_io::types::FloatNum_t>("address.anotherData").value() << std::endl;
    std::cout << json.get<liminal_json_io::types::IntNum_t>("address.story.left").value() << std::endl;
    std::cout << json.get<liminal_json_io::types::String_t>("hobbies[4].secondNestedHobbies[1]").value() << std::endl;
    liminal_json_io::types::Object_t mainObject = json.get<liminal_json_io::types::Object_t>().value();

    // std::cout << json.getType() << std::endl;
    // std::cout << json.getType("address") << std::endl;
    // std::cout << json.getType("address.anotherData") << std::endl;
    // std::cout << json.getType("address.story.left") << std::endl;
    // std::cout << json.getType("hobbies[4].secondNestedHobbies[1]") << std::endl;
    
    while (handler.window.shouldClose() == false) {
        handler.window.pollEvents();
        handler.drawFrame();
    }
    handler.waitIdle();
    return  EXIT_SUCCESS;
}

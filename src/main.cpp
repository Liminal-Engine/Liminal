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

// #include "json_io/InJson.hpp"
// #include "json_io/Json.hpp"
// #include "json_io/OutJson.hpp"
// #include "json_io/types.hpp"
// #include "json_io/Status.hpp"

// #include "windowing/WindowWrapper.hpp"

// #include "vulkan_wrapper/VulkanHdl.hpp"

// #include "fs/FileType.hpp"
// #include "fs/InFile.hpp"
// #include "fs/OutFile.hpp"
// #include "fs/Status.hpp"
// #include "fs/path/path.hpp"

// #include "parser/string.hpp"

#include "logger/logger.hpp"
#include "json_io/InJson.hpp"
#include "fs/Path.hpp"
#include <parser/string.hpp>

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <string>

int main() {
    // logger::debug << "je debug" << "" << '7' << 45*89 << std::endl;
    // logger::trace << "je trace" << std::endl;

    // fs::Path path{"../tests/assets/json/valid/basic.json"};

    // path.insert("ccc");
    // path.insert("..");
    // path.insert("aaa", 2);
    // path.insert("bbb", 2);
    // path.insert("index.ftp--zeraaa");
    // logger::debug << path.toStr() << std::endl;
    // path.clean();
    // logger::debug << path.toStr() << std::endl;
    // logger::fatal << "3=" + path.getEntry().has_value() << std::endl; //<< " 4=" + path.getEntry(4).has_value() << " 5=" + path.getEntry(5).has_value() << std::endl;
    // logger::info << path.getExtension().value() << std::endl; //<< " 4=" + path.getEntry(4).has_value() << " 5=" + path.getEntry(5).has_value() << std::endl;
    // fs::Path path2{"ggg/hhh/jjj/lll.old.d"};
    // logger::info << path2.getExtension().value() << std::endl; //<< " 4=" + path.getEntry(4).has_value() << " 5=" + path.getEntry(5).has_value() << std::endl;
    // logger::info << fs::Path{"./"}.getAbsolute().toStr() << std::endl;

    // std::cout << parser::string::toBool("1", true) << std::endl;

    logger::info << parser::string::trimBegin("abcabcabc", std::vector<std::string>{"ab", "bc"}) << std::endl;


    // json_io::InJson inJson;
    // inJson.parse(fs::Path{"/home/matteo/Projects/Liminal/tests/assets/json/valid/basic.json"});




    // vulkan_wrapper::VulkanHdl handler;
    // fs::InFile file("./README.md");
    // file.open();
    // file.read();
    // file.close();
    // std::cout << file.get_content() << std::endl;
    
    json_io::InJson json;

    json.parse(fs::Path("./tests/assets/bitNestedNoErrors.json"));
    json.parse(fs::Path("/home/matteo/Projects/Liminal/tests/assets/json/invalid/bool/incomplete.json"));
    json.parse(fs::Path("keirhjioehjiot.json"));

    // json_io::types::Object_t object{json.get<json_io::types::Object_t>("address").value()};
    
    
    // std::cout << json.get<json_io::types::Object_t>("address").value().get<json_io::types::FloatNum_t>("anotherData").value() << std::endl;
    // std::cout << json.get<json_io::types::Array_t>("hobbies").value().get<json_io::types::String_t>(1).value() << std::endl;
    // std::cout << json.get<json_io::types::FloatNum_t>("address.anotherData").value() << std::endl;
    // std::cout << json.get<json_io::types::IntNum_t>("address.story.left").value() << std::endl;
    // std::cout << json.get<json_io::types::String_t>("hobbies[4].secondNestedHobbies[1]").value() << std::endl;
    // json_io::types::Object_t mainObject = json.get<json_io::types::Object_t>().value();

    // // std::cout << json.getType() << std::endl;
    // // std::cout << json.getType("address") << std::endl;
    // // std::cout << json.getType("address.anotherData") << std::endl;
    // // std::cout << json.getType("address.story.left") << std::endl;
    // // std::cout << json.getType("hobbies[4].secondNestedHobbies[1]") << std::endl;
    
    // while (handler.window.shouldClose() == false) {
    //     handler.window.pollEvents();
    //     handler.drawFrame();
    // }
    // handler.waitIdle();
    return  EXIT_SUCCESS;
}

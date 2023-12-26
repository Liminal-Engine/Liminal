#include "VulkanHdl.hpp"
#include "InFile.hpp"
#include "InJSON.hpp"

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

    int status;
    std::cout << "name = " << std::string(abi::__cxa_demangle(typeid(handler).name(), 0, 0, &status)) << std::endl;
    
    liminal_json_io::INJSON jsonparser(std::string("./tests/assets/basicNoErrors.json"));
    jsonparser.parse();


    while (handler.window.shouldClose() == false) {
        handler.window.pollEvents();
        handler.drawFrame();
    }
    handler.waitIdle();
}

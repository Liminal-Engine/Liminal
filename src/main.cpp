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

// #include "jsonio/InJson.hpp"
// #include "jsonio/Json.hpp"
// #include "jsonio/OutJson.hpp"
// #include "jsonio/types.hpp"
// #include "jsonio/Status.hpp"

#include "windowing/WindowWrapper.hpp"

#include "vulkan_wrapper/VulkanHdl.hpp"

// #include "fs/FileType.hpp"
// #include "fs/InFile.hpp"
// #include "fs/OutFile.hpp"
// #include "fs/Status.hpp"
// #include "fs/path/path.hpp"

// #include <parseop/parseop.hpp>

#include "logger/logger.hpp"
#include "jsonio/InJson.hpp"
#include "jsonio/OutJson.hpp"
#include "jsonio/Json.hpp"
#include "fs/Path.hpp"
#include <fs/Permission.hpp>
#include <time/Date.hpp>
#include <fs/OutFile.hpp>

#include <parseop/parseop.hpp>
#include <error/error.hpp>
#include <filesystem>
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <string>
#include <regex>
#include <any>
#include <vector>
#include <climits>
#include <limits>
#include <csignal>

#include <host/Engine.hpp>
#include <host/Application.hpp>

void setupLoggerSignalHandlers() {
    std::signal(SIGSEGV, logger::Logger::flushOnCrash);
    std::signal(SIGABRT, logger::Logger::flushOnCrash);
    std::signal(SIGINT,  logger::Logger::flushOnCrash);
    std::signal(SIGTERM, logger::Logger::flushOnCrash);
}

// Forget this for now, driver triggers itself surface change
// static void surfaceChangedCallback(GLFWwindow *window, int width, int height) {
//     (void)(window);
//     (void)(width);
//     (void(height));
// }

int main() {
    setupLoggerSignalHandlers();
    logger::Logger::startWorker();
    int res = host::Engine(host::Application()).run();
    // ::jsonio::OutJson outJson;
    // // outJson.parse(fs::Path("/home/matteo/Projects/Liminal/basic.json"));
    // // outJson.insert();
    // glfwInit();
    // glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    // GLFWwindow* window = glfwCreateWindow(800, 800, "Liminal Engine", nullptr, nullptr);
    // // glfwSetFramebufferSizeCallback(window, surfaceChangedCallback);
    // // renderer::Context context(window);
    // // renderer::SwapChain swapChain(window, context.getGPU(), context.getVKSurface());
    // // renderer::PipelineHandler pipelineHandler(context.getGPU(), swapChain);
    // // renderer::Presenter presenter(context.getGPU(), swapChain, pipelineHandler);
    // // renderer::Renderer renderer();
    // renderer::Renderer renderer(window);

    // while (!glfwWindowShouldClose(window)) {
    //     glfwPollEvents();
    //     renderer.draw();
    // }
    // renderer.waitForGPUToFinishJobs();
    // glfwDestroyWindow(window);
    logger::Logger::stopWorker();
    return res;
    // std::vector<std::string> tokPath = parseop::tokenize("", '.');

    // logger::error << true << ' ' << false << std::endl;

    // fs::OutFile instance(fs::Path("/home/matteo/Projects/Liminal/test/assets/fs/OutFile/a.txt"));
    // instance.open(true);
    // if (!instance.isOpen()) std::cerr << "instance NOT OPEN" << std::endl;
    // instance.write(std::string(10 * 1024 * 1024, 'A'));
    // instance.close();
    // std::ifstream file("/home/matteo/Projects/Liminal/test/assets/fs/OutFile/a.txt"); // Open the file
    // if (!file.is_open()) std::cerr << "file not opened" <<std::endl;
    // std::ostringstream buffer;
    // buffer << file.rdbuf();
    // std::cout << std::boolalpha << (buffer.str() == std::string(10 * 1024 * 1024, 'A')) << std::endl;


    // ::jsonio::OutJson json;
    // json.parse(fs::Path("/home/matteo/Projects/Liminal/basic.json"));
    // json.insert<jsonio::types::FloatNum_t>("NEWKEY", 42.23);
    // // outJson.write(::fs::Path("ioajze"));
    // // json.parse(fs::Path("/home/matteo/Projects/Liminal/basic.json"));
    // // ::jsonio::Status status  = json.insert<::jsonio::types::Object_t>("", ::jsonio::types::Object_t(), true);
    // // status = json.insert<std::string>("toto", "tata");
    // // status = json.insert("titi", jsonio::types::Object_t());
    // // status = json.insert("titi.tutu.toto", jsonio::types::Object_t());
    // ::jsonio::Status status = json.write(fs::Path("/home/matteo/Projects/Liminal/basic.json"), true);
    // status = json.insert("titi.tutu.tiktok", std::string("tana"));
    // status = json.write(::fs::Path("/home/matteo/Projects/Liminal/basic.json"));
    // json.insert("", ::jsonio::types::Object_t(), true);
    
    // json.get<::jsonio::types::Array_t>("toto.tata", std::vector<std::string>{"7"});
    
    // outJson.insert<jsonio::types::String_t>("address.story.left", "boubou", true);
    // outJson.insert<jsonio::types::IntNum_t>("address.story.street", 43, true);
    // outJson.insert<jsonio::types::FloatNum_t>("address.story", 47.42, true);
    // outJson.insert<jsonio::types::Object_t>("hobbies[1]", jsonio::types::Object_t(), true);
    // outJson.insert<jsonio::types::String_t>("hobbies[1].bonjour", "au revoir", true);
    
    
    // outJson.insert<jsonio::types::IntNum_t>("hobbies[4].secondNestedHobbies[4]", 42);
    // json.write(::fs::Path("/home/matteo/Projects/Liminal/basic2.json"));

    // outJson.insert<jsonio::types::String_t>("address.story.center.yes", "no", true);
    // outJson.insertValue<jsonio::types::String_t>("hobbies[2]", "boubou", true, JSON_DEFAULT_SEPARATORS);
    // outJson.insertKey("address.story.center", jsonio::types::ValueTypes::STRING, true);
    // outJson.get<jsonio::types::FloatNum_t>("bonjour.aurevoir");
    // ::fs::Status tmpFSStatus = ::fs::Path("../../test/assets/tmp/../../assets/tmp../tmp/create/character_device_attempt").create(
    //     ::fs::Entry::Type::CHARACTER_DEVICE, false, ::fs::Permission(0666)
    // );

    // std::cout << ::time_::convert(4, time_::Unit::YEAR, time_::Unit::NANO_SECOND) << std::endl;
    // fs::Path p("/");
    // std::cout << p.getEntry().getName() << std::endl;

    // time_::Date d((int)1974, 1);
    // std::cout << "d:\n--------------\nstamp = " << d.getStamp() << std::endl;
    // std::cout << d.asStr() << std::endl;
    // std::cout << d.extract(time_::Unit::YEAR) << std::endl;
    // std::cout << d.extract(time_::Unit::MONTH) << std::endl;
    // std::cout << d.extract(time_::Unit::MONTH_DAY) << std::endl;
    // std::cout << d.extract(time_::Unit::HOUR) << std::endl;
    // std::cout << d.extract(time_::Unit::MINUTE) << std::endl;
    // std::cout << d.extract(time_::Unit::SECOND) << std::endl;
    // std::cout << d.extract(time_::Unit::MILLI_SECOND) << std::endl;
    // std::cout << d.extract(time_::Unit::MICRO_SECOND) << std::endl;
    // std::cout << d.extract(time_::Unit::NANO_SECOND) << std::endl;

    // time_::Date d2(static_cast<time_::Stamp_t>(2145913200 + (3600 * 400)), ::time_::Unit::SECOND);
    // std::cout << "d2:\n--------------\nstamp = " << d2.getStamp() << std::endl;
    // std::cout << d2.asStr() << std::endl;
    // std::cout << d2.extract(time_::Unit::YEAR) << std::endl;
    // std::cout << d2.extract(time_::Unit::MONTH) << std::endl;
    // std::cout << d2.extract(time_::Unit::MONTH_DAY) << std::endl;
    // std::cout << d2.extract(time_::Unit::HOUR) << std::endl;
    // std::cout << d2.extract(time_::Unit::MINUTE) << std::endl;
    // std::cout << d2.extract(time_::Unit::SECOND) << std::endl;
    // std::cout << d2.extract(time_::Unit::MILLI_SECOND) << std::endl;
    // std::cout << d2.extract(time_::Unit::MICRO_SECOND) << std::endl;
    // std::cout << d2.extract(time_::Unit::NANO_SECOND) << std::endl;

    // std::cout << p2.asStr() << std::endl;
    // fs::Path p{"/path/to/non_empty_file.txt"};
    // p.insert("/", 0);
    // p.toRelative();
    // fs::Permission(fs::Permission::Type::EXEC | fs::Permission::Type::READ, fs::Permission::Type::NONE, fs::Permission::Type::NONE);
    // logger::info << "hello Maximum value of long long int:" << std::numeric_limits<long long int>::max() << std::endl;
    // // std::cout << time_::Date{1713557763499153664, time_::Unit::NANO_SECOND}.asStr("%2Y-%m-%dT%H:%M:%S.%E.%f.%i") << std::endl; 
    // std::cout << time_::convert(8, time_::Unit::MICRO_SECOND, time_::Unit::MICRO_SECOND);
    // std::cout << time_::convert(1414922587498, time_::Unit::MILLI_SECOND, time_::Unit::NANO_SECOND);
    // std::cout << date.toFormat("%Y-%m-%dT%H:%M:%SZ") << std::endl;
    // std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(
    //                 std::chrono::high_resolution_clock::now().time_since_epoch()
    //             ).count()
    // << std::endl;
    // std::cout << static_cast<time_::Stamp_t>(
    //             std::chrono::duration_cast<std::chrono::nanoseconds>(
    //                 std::chrono::high_resolution_clock::now().time_since_epoch()
    //             ).count())
    // << std::endl;
    // logger::info << date.toFormat("%Y-%m-%dT%H:%M:%SZ");
    // logger::info << "hello Maximum value of unsigned long long int:" << std::numeric_limits<unsigned long long int>::max() << std::endl;

    // std::string tmp = std::filesystem::relative("/home/matteo/Projects/Liminal/lib/error").string();
    // std::cout << std::endl;
    // fs::Path p{"/home/matteo/Projects/Liminal/lib/error"};
    // p.toRelative();
    // logger::info << p.asStr() << std::endl;
    // p2.toRelative();
    // logger::info << p2.asStr() << std::endl;
    // std::cout << p.getType() << std::endl;
    // std::regex pattern(R"(\d{4}-\d{2}-\d{2}T.*)");
    // std::stringstream buffer;
    // std::streambuf *sbuf = std::cout.rdbuf();
    // std::cout.rdbuf(buffer.rdbuf());
    // logger::info << "AAA" << std::endl;
    // std::cout.rdbuf(sbuf);
    // std::cout << buffer.str() << std::endl;
    // std::cout << "RESULT OF REGEX MATCH=" << std::string{std::regex_search(buffer.str(), pattern) ? "true" : "false"} << std::endl;
    // logger::debug << "je debug" << "" << '7' << 45*89 << std::endl;
    // logger::trace << "je trace" << std::endl;

    // fs::Path path{"../tests/assets/json/valid/basic.json"};

    // path.insert("ccc");
    // path.insert("..");
    // path.insert("aaa", 2);
    // path.insert("bbb", 2);
    // path.insert("index.ftp--zeraaa");
    // logger::debug << path.asStr() << std::endl;
    // path.clean();
    // logger::debug << path.asStr() << std::endl;
    // logger::fatal << "3=" + path.getEntry().has_value() << std::endl; //<< " 4=" + path.getEntry(4).has_value() << " 5=" + path.getEntry(5).has_value() << std::endl;
    // logger::info << path.getExtension().value() << std::endl; //<< " 4=" + path.getEntry(4).has_value() << " 5=" + path.getEntry(5).has_value() << std::endl;
    // fs::Path path2{"ggg/hhh/jjj/lll.old.d"};
    // logger::info << path2.getExtension().value() << std::endl; //<< " 4=" + path.getEntry(4).has_value() << " 5=" + path.getEntry(5).has_value() << std::endl;
    // logger::info << fs::Path{"./"}.getAbsolute().asStr() << std::endl;

    // std::cout << parseop::toBool("1", true) << std::endl;

    // logger::info << parseop::trimBegin("abcabcabc", std::vector<std::string>{"ab", "bc"}) << std::endl;

    // jsonio::InJson inJson;
    // inJson.parse(fs::Path{"/home/matteo/Projects/Liminal/tests/assets/json/valid/basic.json"});

    // vulkan_wrapper::VulkanHdl handler;
    // fs::InFile file("./README.md");
    // file.open();
    // file.read();
    // file.close();
    // std::cout << file.getContent() << std::endl;
    
    // jsonio::InJson json;

    // json.parse(fs::Path("./tests/assets/bitNestedNoErrors.json"));
    // json.parse(fs::Path("/home/matteo/Projects/Liminal/tests/assets/json/invalid/bool/incomplete.json"));
    // json.parse(fs::Path("keirhjioehjiot.json"));

    // jsonio::types::Object_t object{json.get<jsonio::types::Object_t>("address").value()};
    
    
    // std::cout << json.get<jsonio::types::Object_t>("address").value().get<jsonio::types::FloatNum_t>("anotherData").value() << std::endl;
    // std::cout << json.get<jsonio::types::Array_t>("hobbies").value().get<jsonio::types::String_t>(1).value() << std::endl;
    // std::cout << json.get<jsonio::types::FloatNum_t>("address.anotherData").value() << std::endl;
    // std::cout << json.get<jsonio::types::IntNum_t>("address.story.left").value() << std::endl;
    // std::cout << json.get<jsonio::types::String_t>("hobbies[4].secondNestedHobbies[1]").value() << std::endl;
    // jsonio::types::Object_t mainObject = json.get<jsonio::types::Object_t>().value();

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

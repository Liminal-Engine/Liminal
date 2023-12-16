file(GLOB_RECURSE SOURCES "src/*.cpp")

project(vulkan_wrapper)

add_library(vulkan_wrapper STATIC ${SOURCES})
target_include_directories(vulkan_wrapper PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(vulkan_wrapper PUBLIC glfw vulkan dl pthread X11 Xxf86vm Xrandr Xi)
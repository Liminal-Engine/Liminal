cmake_minimum_required(VERSION 3.10)

file(READ VERSION PROJECT_VERSION)

project(Liminal VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -g3")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -flto -DNDEBUG") #-march=native
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib/vulkan_wrapper)

add_executable(Liminal src/main.cpp)
target_include_directories(Liminal PUBLIC include)
target_link_libraries(Liminal PUBLIC vulkan_wrapper)

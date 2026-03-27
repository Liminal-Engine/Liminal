cmake_minimum_required(VERSION 3.14)

file(READ VERSION PROJECT_VERSION)
string(STRIP "${PROJECT_VERSION}" PROJECT_VERSION)

project(Liminal VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -g3 -Wall -Wextra -Wpedantic")

# Get the number of cores
execute_process(COMMAND nproc OUTPUT_VARIABLE NUM_CORES OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -flto=${NUM_CORES} -DNDEBUG -funroll-loops -fvisibility=hidden -Werror") #-march=native -Wall -Wextra -Wpedantic -Werror

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Liminal src/main.cpp)

target_include_directories(Liminal PUBLIC include)

include(${CMAKE_CURRENT_SOURCE_DIR}/tools/macros.cmake)

# Build each libs and link them to the final binary
file(GLOB FULL_LIB_DIRS LIST_DIRECTORIES true "lib/*")
foreach(FULL_DIR ${FULL_LIB_DIRS})
    file(RELATIVE_PATH DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib ${FULL_DIR})
    add_subdirectory(lib/${DIR})
    target_include_directories(Liminal PUBLIC lib/${DIR}/include/public)
    target_link_libraries(Liminal PUBLIC ${DIR})
endforeach()

# add vendors
# 1. shaderc_combined
# target_include_directories(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/shaderc/libshaderc/include)
# target_include_directories(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/shaderc/libshaderc_util/include)
# target_include_directories(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/shaderc/spirv-tools/include)
# target_link_libraries(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/build/shaderc/libshaderc/libshaderc_combined.a)
# 2. glm
target_include_directories(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/glm)
target_link_libraries(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/build/glm/glm/libglm.a)
# 3. glad
target_include_directories(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/glad/include)
target_link_libraries(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/build/glad/libglad.a)
# 4. glfw
# target_include_directories(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/glfw/include)
# target_link_libraries(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/build/glfw/src/libglfw3.a)
# 5. stb_image
target_include_directories(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/stb_image/include)
# no lib or compilation process required for stb_image since it is a header only library
#6. entt
target_include_directories(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/entt/src)
# no lib or compilation process required for entt since it is a header onyl library

# add tests
enable_testing()
add_subdirectory(test)



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
target_include_directories(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/shaderc/libshaderc/include)
target_include_directories(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/shaderc/libshaderc_util/include)
target_include_directories(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/shaderc/spirv-tools/include)
target_link_libraries(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/build/shaderc/libshaderc/libshaderc_combined.a)
# 2. glm
target_include_directories(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/gml)
target_link_libraries(Liminal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendors/build/glm/glm/libglm.a)
# add tests
enable_testing()
add_subdirectory(test)



cmake_minimum_required(VERSION 3.14)

file(READ VERSION PROJECT_VERSION)

project(Liminal VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -g3 -Wall -Wextra -Wpedantic")

# Get the number of cores
execute_process(COMMAND nproc OUTPUT_VARIABLE NUM_CORES OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -flto=${NUM_CORES} -DNDEBUG -funroll-loops -fvisibility=hidden -Wall -Wextra -Wpedantic -Werror") #-march=native
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Liminal src/main.cpp)

target_include_directories(Liminal PUBLIC include)

# Build each libs and link them to the final binary
file(GLOB FULL_LIB_DIRS LIST_DIRECTORIES true "lib/*")
foreach(FULL_DIR ${FULL_LIB_DIRS})
    file(RELATIVE_PATH DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib ${FULL_DIR})
    add_subdirectory(lib/${DIR})
    target_include_directories(Liminal PUBLIC lib/${DIR}/include/public)
    target_link_libraries(Liminal PUBLIC ${DIR})
endforeach()

enable_testing()
add_subdirectory(tests)
# add_test(Liminal_tests, ${CMAKE_CURRENT_SOURCE_DIR}/build/tests/LiminalUnitTests)

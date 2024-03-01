cmake_minimum_required(VERSION 3.14)
set(PROJECT_NAME LiminalUnitTests)
project(${PROJECT_NAME})

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Actually build the tests:

# 1. Add executable
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# 2. Link the google test lib
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest_main GTest::gmock_main)
include(GoogleTest)

# 3. Discover tests to make them runnable by cmake system
# gtest_discover_tests(${PROJECT_NAME} DISCOVERY_MODE POST_BUILD)
gtest_discover_tests(${PROJECT_NAME})
# gtest_add_tests(TARGET ${PROJECT_NAME})
# add_test(Liminal_tests, ${CMAKE_CURRENT_SOURCE_DIR}/build/tests/LiminalUnitTests)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/liminal_json_io)

# 4. Add project include dirs and libs
file(GLOB FULL_LIB_DIRS LIST_DIRECTORIES true "../lib/*")

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

foreach(FULL_DIR ${FULL_LIB_DIRS})

  file(RELATIVE_PATH DIR ${CMAKE_CURRENT_SOURCE_DIR}/../lib ${FULL_DIR})

  target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/${DIR}/include/public)
  target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/${DIR}/include/public/${DIR})

  # Allow _private dirs to be included : ONLY for test purposing
  target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
  target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../lib/${DIR}/include)
  
  target_link_libraries(${PROJECT_NAME} PRIVATE ${DIR})
endforeach()
# enable_testing()

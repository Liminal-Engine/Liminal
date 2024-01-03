cmake_minimum_required(VERSION 3.10)

file(READ VERSION PROJECT_VERSION)

project(Liminal VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -g3 -Wall -Wextra -Wpedantic")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -flto -DNDEBUG -funroll-loops -fvisibility=hidden -Wall -Wextra -Wpedantic -Werror") #-march=native
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(Liminal src/main.cpp)

target_include_directories(Liminal PUBLIC include)

add_subdirectory(lib/liminal_windowing)
target_include_directories(Liminal PRIVATE lib/liminal_windowing/include/public)
target_link_libraries(Liminal PUBLIC liminal_windowing)


add_subdirectory(lib/liminal_string_extras)
target_include_directories(Liminal PUBLIC lib/liminal_string_extras/include/public)
target_link_libraries(Liminal PUBLIC liminal_string_extras)

add_subdirectory(lib/vulkan_wrapper)
target_include_directories(Liminal PUBLIC lib/vulkan_wrapper/include/public)
target_link_libraries(Liminal PUBLIC vulkan_wrapper)

add_subdirectory(lib/liminal_fs)
target_include_directories(Liminal PUBLIC lib/liminal_fs/include/public)
target_link_libraries(Liminal PUBLIC liminal_fs)

add_subdirectory(lib/liminal_json_io)
target_include_directories(Liminal PUBLIC lib/liminal_json_io/include/public)
target_link_libraries(Liminal PUBLIC liminal_json_io)

# add_subdirectory(lib/liminal_fs)
# target_link_libraries(Liminal PUBLIC liminal_fs)
# target_include_directories(Liminal PUBLIC lib/liminal_fs/include/public)

# add_subdirectory(lib/liminal_windowing)
# add_subdirectory(lib/vulkan_wrapper)
# add_subdirectory(lib/liminal_json_io)
# add_subdirectory(lib/liminal_fs)
# add_subdirectory(lib/liminal_parser)


# target_include_directories(liminal_fs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/_private)
# target_link_libraries(Liminal PUBLIC liminal_windowing)
# target_link_libraries(Liminal PUBLIC vulkan_wrapper)
# target_link_libraries(Liminal PUBLIC liminal_json_io)
# target_link_libraries(Liminal PUBLIC liminal_fs)
# target_link_libraries(Liminal PUBLIC liminal_parser)











# cmake_minimum_required(VERSION 3.10)

# file(READ VERSION PROJECT_VERSION)

# project(Liminal VERSION ${PROJECT_VERSION})

# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -g3 -Wall -Wextra -Wpedantic")

# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -flto -DNDEBUG -funroll-loops -fvisibility=hidden -Wall -Wextra -Wpedantic -Werror") #-march=native
# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED True)


# add_executable(Liminal src/main.cpp)

# add_subdirectory(lib/liminal_windowing)
# add_subdirectory(lib/vulkan_wrapper)
# add_subdirectory(lib/liminal_json_io)
# add_subdirectory(lib/liminal_fs)
# add_subdirectory(lib/liminal_parser)

# target_include_directories(Liminal PUBLIC include)

# target_include_directories(liminal_fs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/_private)
# target_link_libraries(Liminal PUBLIC liminal_windowing)
# target_link_libraries(Liminal PUBLIC vulkan_wrapper)
# target_link_libraries(Liminal PUBLIC liminal_json_io)
# target_link_libraries(Liminal PUBLIC liminal_fs)
# target_link_libraries(Liminal PUBLIC liminal_parser)

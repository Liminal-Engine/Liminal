cmake_minimum_required(VERSION 3.14)

project(VendorDependencies NONE)


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 1. shaderc
# set(SHADERC_ENABLE_SHARED_CRT OFF CACHE BOOL "" FORCE)
# set(SHADERC_SKIP_TESTS ON CACHE BOOL "" FORCE)
# set(SHADERC_SKIP_EXAMPLES ON CACHE BOOL "" FORCE)
# set(SHADERC_ENABLE_GLSLANG_BINARIES OFF CACHE BOOL "" FORCE)
# set(SHADERC_ENABLE_WERROR OFF CACHE BOOL "" FORCE)
# set(SHADERC_ENABLE_JUMBO_BUILD ON CACHE BOOL "" FORCE)

# add_subdirectory(shaderc)

# 2. glm
set(GLM_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLM_BUILD_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(glm)

# 3. glad
add_subdirectory(glad)

# 4. glfw
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_INSTALL OFF CACHE BOOL "" FORCE)
# add_subdirectory(glfw)

# 5. stb image
# nothing to do here since stb_image is a header only library
#6. entt
add_subdirectory(entt)

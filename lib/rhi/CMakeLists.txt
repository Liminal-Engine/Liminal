discover_lib()

# Local lib deps
link_internal_libs(PUBLIC logger fs entity)

find_package(PkgConfig REQUIRED)
pkg_check_modules(EGL REQUIRED egl)
link_external_libs(PRIVATE ${EGL_LIBRARIES})
# link_external_libs(PUBLIC glad)

# FIXME : create macro for vendors
target_include_directories(rhi PUBLIC ${CMAKE_SOURCE_DIR}/vendors/glad/include)
target_link_libraries(rhi PRIVATE ${CMAKE_SOURCE_DIR}/vendors/build/glad/libglad.a)

target_include_directories(rhi PRIVATE ${CMAKE_SOURCE_DIR}/vendors/stb_image/include)

target_include_directories(rhi PUBLIC ${CMAKE_SOURCE_DIR}/vendors/glm)
target_link_libraries(rhi PRIVATE ${CMAKE_SOURCE_DIR}/vendors/build/glm/glm/libglm.a)
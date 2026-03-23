discover_lib()

# Local lib deps
link_internal_libs(PUBLIC rhi fs logger parseop jsonio entity)

target_include_directories(gfx PRIVATE ${CMAKE_SOURCE_DIR}/vendors/stb_image/include)

target_include_directories(gfx PUBLIC ${CMAKE_SOURCE_DIR}/vendors/glad/include)
target_link_libraries(gfx PRIVATE ${CMAKE_SOURCE_DIR}/vendors/build/glad/libglad.a)

target_include_directories(gfx PRIVATE ${CMAKE_SOURCE_DIR}/vendors/entt/src)
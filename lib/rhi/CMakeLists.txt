discover_lib()

# Local lib deps
link_internal_libs(PUBLIC logger)
# link_external_libs(PUBLIC glad)

# FIXME : create macro for vendors
target_include_directories(rhi PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glad/include)
target_link_libraries(rhi PUBLIC ${CMAKE_SOURCE_DIR}/vendors/build/glad/libglad.a)
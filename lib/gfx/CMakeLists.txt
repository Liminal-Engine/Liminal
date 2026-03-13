discover_lib()

# Local lib deps
link_internal_libs(PUBLIC rhi fs logger parseop)

target_include_directories(gfx PRIVATE ${CMAKE_SOURCE_DIR}/vendors/stb_image/include)

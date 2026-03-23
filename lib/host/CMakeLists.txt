discover_lib()

# Local lib deps
link_internal_libs(PUBLIC logger gfx entity wsi)

target_include_directories(host PRIVATE ${CMAKE_SOURCE_DIR}/vendors/entt/src)
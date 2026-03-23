discover_lib()

# Local lib deps
link_internal_libs(PUBLIC logger gfx math)
# link_external_libs(PUBLIC glad)

# FIXME : create macro for vendors
target_include_directories(entity PRIVATE ${CMAKE_SOURCE_DIR}/vendors/glm)
target_link_libraries(entity PRIVATE ${CMAKE_SOURCE_DIR}/vendors/build/glm/glm/libglm.a)

target_include_directories(entity PRIVATE ${CMAKE_SOURCE_DIR}/vendors/entt/src)
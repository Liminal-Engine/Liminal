macro(_set_project_name)
    get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    set(PROJECT_NAME ${PROJECT_NAME} PARENT_SCOPE)
endmacro(_set_project_name)

macro(discover_lib)
    _set_project_name()

    file(GLOB_RECURSE SOURCES "src/*.cpp")
    add_library(${PROJECT_NAME} STATIC ${SOURCES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/public/${PROJECT_NAME})
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/)
endmacro()

macro(link_external_libs mode libs)
    _set_project_name()

    target_link_libraries(${PROJECT_NAME} ${mode} ${libs})
endmacro(link_external_libs)

macro(link_internal_libs mode)
    set(libs ${ARGN})
    foreach(lib ${libs})
        target_include_directories(${PROJECT_NAME} ${mode} ${CMAKE_CURRENT_SOURCE_DIR}/../${lib}/include/public)
        target_link_libraries(${PROJECT_NAME} ${mode} ${lib})
    endforeach()
endmacro(link_internal_libs)

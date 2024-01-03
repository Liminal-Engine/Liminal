file(GLOB_RECURSE SOURCES "src/*.cpp")

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/include/public/${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/include/)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw dl pthread X11 Xxf86vm Xrandr Xi)

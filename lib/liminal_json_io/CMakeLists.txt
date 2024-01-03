file(GLOB_RECURSE SOURCES "src/*.cpp")

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${PROJECT_NAME})

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/public/${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Local lib deps
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../liminal_fs/include/public)
target_link_libraries(${PROJECT_NAME} PUBLIC liminal_fs)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../liminal_string_extras/include/public)
target_link_libraries(${PROJECT_NAME} PUBLIC liminal_string_extras)
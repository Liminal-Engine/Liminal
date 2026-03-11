cmake_minimum_required(VERSION 3.14)

project(glad)

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC include)
target_compile_options(glad PRIVATE -w)

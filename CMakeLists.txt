cmake_minimum_required(VERSION 3.14)

project(glad LANGUAGES C)

set(BUILD_GL_FILES "src/gl.c")

add_library(glad ${BUILD_GL_FILES})

target_include_directories(glad PUBLIC ./include)
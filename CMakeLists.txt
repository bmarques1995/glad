cmake_minimum_required(VERSION 3.14)

project(glad LANGUAGES C)

set(BUILD_GL_FILES "src/gl.c")

add_library(glad ${BUILD_GL_FILES})

target_include_directories(glad PUBLIC ./include)

install(DIRECTORY include/glad DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN gl.h PATTERN gl_safe_include.h)
install(TARGETS glad RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

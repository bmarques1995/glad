cmake_minimum_required(VERSION 3.14)

project(glad LANGUAGES C)

option(BUILD_VULKAN "Select if vulkan will be built" OFF)

set(BUILD_GL_FILES "src/gl.c")
set(BUILD_VK_FILES "src/vulkan.c")

add_library(glad ${BUILD_GL_FILES})

if(BUILD_VULKAN)
    target_sources(glad PUBLIC ${BUILD_VK_FILES})
    message("VULKAN WILL BE BUILT")
endif()

target_include_directories(glad PUBLIC ./include)
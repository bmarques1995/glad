cmake_minimum_required(VERSION 3.14)

project(glad LANGUAGES C)

set(GL_SOURCES)

if(WIN32)
    set(GL_SOURCES ${GL_SOURCES} "src/gl.c" "src/wgl.c")
    install(DIRECTORY include/glad DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN gl.h PATTERN gl_safe_include.h PATTERN wgl.h PATTERN wglext.h)
endif(WIN32)

#Needs test
if(UNIX AND NOT APPLE)
    if(NOT DEFINED ENV{XDG_SESSION_TYPE})
        message(ERROR "XDG_SESSION_TYPE not set")
    elseif("$ENV{XDG_SESSION_TYPE}" STREQUAL "x11")
        set(USING_X11 TRUE)
    elseif("$ENV{XDG_SESSION_TYPE}" STREQUAL "wayland")
        set(USING_X11 FALSE)
    else()
        message(FATAL_ERROR "Unknown XDG_SESSION_TYPE value: $ENV{XDG_SESSION_TYPE}")
    endif()
    if(USING_X11)
        set(GL_SOURCES ${GL_SOURCES} "src/gl.c" "src/glx.c")
        install(DIRECTORY include/glad DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN gl.h PATTERN gl_safe_include.h PATTERN glx.h)
    else()
        set(GL_SOURCES ${GL_SOURCES}  "src/gl.c" "src/egl.c")
        install(DIRECTORY include/glad DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN gl.h PATTERN gl_safe_include.h PATTERN egl.h)
        install(DIRECTORY include/EGL DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN eglplatform.h)
    endif()
endif()

message(${GL_SOURCES})
add_library(glad STATIC ${GL_SOURCES})
target_include_directories(glad PUBLIC ./include)

install(DIRECTORY include/KHR DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN khrplatform.h)
install(TARGETS glad RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

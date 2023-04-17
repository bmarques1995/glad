cmake_minimum_required(VERSION 3.14)

project(glad LANGUAGES C)

set(GL_SOURCES)
set(GL_HEADERS)

if(WIN32)
    set(GL_SOURCES ${GL_SOURCES} "src/gl.c" "src/wgl.c")
    set(GL_HEADERS ${GL_HEADERs} "include/glad/gl.h" "include/glad/wgl.h" "include/glad/wglext.h")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    install(DIRECTORY include/glad DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN gl.h PATTERN wgl.h PATTERN wglext.h)
endif(WIN32)

#Needs test
if(UNIX AND NOT APPLE)
    set(GL_SOURCES ${GL_SOURCES}  "src/gl.c" "src/egl.c")
    set(GL_HEADERS ${GL_HEADERs} "include/glad/gl.h" "include/glad/egl.h" "include/EGL/eglplatform.h")
    install(DIRECTORY include/glad DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN gl.h PATTERN egl.h)
    install(DIRECTORY include/EGL DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN eglplatform.h)
endif()

add_library(gladstatic STATIC ${GL_SOURCES} ${GL_HEADERS})
add_library(glad SHARED ${GL_SOURCES} ${GL_HEADERS})
if(WIN32)
target_compile_definitions(glad PUBLIC GLAD_PLATFORM_WIN32 GLAD_API_CALL_EXPORT_BUILD GLAD_API_CALL_EXPORT)
target_compile_definitions(gladstatic PUBLIC GLAD_PLATFORM_WIN32)
target_link_libraries(glad PRIVATE opengl32)
endif()
target_include_directories(glad PUBLIC ./include)
target_include_directories(gladstatic PUBLIC ./include)


install(DIRECTORY include/KHR DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN khrplatform.h)
install(TARGETS glad gladstatic
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
        ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}" )

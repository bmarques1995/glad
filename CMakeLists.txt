cmake_minimum_required(VERSION 3.14)

set(PROJECT_NAME glad)

project(${PROJECT_NAME} VERSION 2.0.0 LANGUAGES C)

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



set(GLAD_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(GLAD_VERSION_CONFIG "${GLAD_GENERATED_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(GLAD_PROJECT_CONFIG "${GLAD_GENERATED_DIR}/${PROJECT_NAME}Config.cmake")
set(GLAD_TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(GLAD_CONFIG_INSTALL_DIR "lib/cmake/${PROJECT_NAME}")
set(GLAD_NAMESPACE "${PROJECT_NAME}::")
set(GLAD_VERSION 2.0.0)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${GLAD_VERSION_CONFIG}" VERSION ${GLAD_VERSION} COMPATIBILITY SameMajorVersion
)
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/config.cmake.in" "${GLAD_PROJECT_CONFIG}" @ONLY)

# Install cmake config files
install(
    FILES "${GLAD_PROJECT_CONFIG}" "${GLAD_VERSION_CONFIG}"
    DESTINATION "${GLAD_CONFIG_INSTALL_DIR}")
# Install cmake targets files
install(
    EXPORT "${GLAD_TARGETS_EXPORT_NAME}"
    NAMESPACE "${GLAD_NAMESPACE}"
    DESTINATION "${GLAD_CONFIG_INSTALL_DIR}")

add_library(${PROJECT_NAME}static STATIC ${GL_SOURCES} ${GL_HEADERS})
add_library(${PROJECT_NAME} SHARED ${GL_SOURCES} ${GL_HEADERS})
if(WIN32)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLAD_PLATFORM_WIN32 GLAD_API_CALL_EXPORT_BUILD GLAD_API_CALL_EXPORT)
target_compile_definitions(${PROJECT_NAME}static PUBLIC GLAD_PLATFORM_WIN32)
target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
endif()
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)
target_include_directories(${PROJECT_NAME}static PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include>)

install(DIRECTORY include/KHR DESTINATION ${CMAKE_INSTALL_PREFIX}/include FILES_MATCHING PATTERN khrplatform.h)

install(TARGETS glad gladstatic
        EXPORT gladTargets
        RUNTIME DESTINATION "${INSTALL_BIN_DIR}"
        ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
        LIBRARY DESTINATION "${INSTALL_LIB_DIR}")

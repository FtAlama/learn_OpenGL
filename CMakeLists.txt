cmake_minimum_required(VERSION 3.10)
project(MonProjetOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

set(APP_NAME learn_opengl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/glfw-3.4)

add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

add_executable(${APP_NAME} src/Application.cpp
														src/glad.c)

target_include_directories(${APP_NAME} PRIVATE 
								${CMAKE_SOURCE_DIR}/include
								external/glad/include)

target_compile_options(${APP_NAME} PRIVATE
    -Wall
    -Wextra
    -Werror
		-Wno-deprecated-declarations
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${APP_NAME} PRIVATE -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${APP_NAME} PRIVATE -O3)
endif()

target_link_libraries(${APP_NAME} PRIVATE glad glfw)


if(APPLE)
    message(STATUS "macOS detected")

    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
        set(GLFW_ARCH "lib-arm64")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
        set(GLFW_ARCH "lib-x86_64")
    else()
        message(FATAL_ERROR "Unknown macOS architecture: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()

    # Ajoute les include et lib paths de GLFW
    set(GLFW_ROOT "${CMAKE_SOURCE_DIR}/external/glfw-3.4.bin.MACOS")
    include_directories("${GLFW_ROOT}/include")
    link_directories("${GLFW_ROOT}/${GLFW_ARCH}")

    # Link GLFW et OpenGL
    target_link_libraries(${APP_NAME} PRIVATE glfw "-framework OpenGL" "-framework Cocoa" "-framework IOKit" "-framework CoreVideo")
elseif(UNIX)
    target_link_libraries(${APP_NAME} PRIVATE GL dl pthread)
endif()

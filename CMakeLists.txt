cmake_minimum_required(VERSION 3.10)
project(MonProjetOpenGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(APP_NAME learn_opengl)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external/glfw-3.4)

add_executable(${APP_NAME} src/Application.cpp)

target_include_directories(${APP_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_compile_options(${APP_NAME} PRIVATE
    -Wall
    -Wextra
    -Werror
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${APP_NAME} PRIVATE -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${APP_NAME} PRIVATE -O3)
endif()

target_link_libraries(${APP_NAME} PRIVATE glfw)

if(APPLE)
    target_link_libraries(${APP_NAME} PRIVATE "-framework OpenGL")
elseif(UNIX)
    target_link_libraries(${APP_NAME} PRIVATE GL dl pthread)
endif()


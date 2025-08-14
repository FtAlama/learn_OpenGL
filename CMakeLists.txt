cmake_minimum_required(VERSION 3.10)
project(MonProjetOpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(APP_NAME learn_opengl)

# LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GLAD
add_library(glad STATIC src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# GLFW 
add_subdirectory(external/glfw-3.4)

# Application
add_executable(${APP_NAME}
  src/Application.cpp
	src/VertexBuffer/GLError.cpp
	src/VertexBuffer/GLCreateVertex.cpp
	src/shaders/Shader.cpp
	src/shaders/ShadersProcess.cpp
	src/shaders/textures/Texture.cpp
	src/Scene/Camera.cpp
)

target_include_directories(${APP_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  external/glad/include
	external/image_format
	external/glm
)

target_link_libraries(${APP_NAME} PRIVATE
  glad
  glfw
)

# Flags
target_compile_options(${APP_NAME} PRIVATE
  -Wall
  -Wextra
  -Werror
  -Wno-deprecated-declarations
	-ferror-limit=0
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(${APP_NAME} PRIVATE -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(${APP_NAME} PRIVATE -O3)
endif()

# macOS specific
if(APPLE)
  message(STATUS "macOS detected")
  target_link_libraries(${APP_NAME} PRIVATE
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
  )
elseif(UNIX)
  target_link_libraries(${APP_NAME} PRIVATE GL dl pthread)
endif()

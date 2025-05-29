cmake_minimum_required(VERSION 3.10)

project(ZeroEngine)

set(C_STANDARD_REQUIRED TRUE)
set(CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(C_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)

# find_package(GLEW REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(CLI11 CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(SOURCES
  src/main.cpp
  src/engine/app.cpp
  src/engine/window.cpp
  src/engine/renderer.cpp
  src/engine/fs.cpp
  src/engine/triangle.cpp
  src/engine/shader.cpp
  src/engine/gl.cpp
)

# Add sources to executable
if(WIN32_APP)
  # WIN32 GUI Application
  add_executable(ZeroEngine WIN32 ${SOURCES})
else()
  # Console Application
  add_executable(ZeroEngine ${SOURCES})
endif()


# Include directories
target_include_directories(ZeroEngine PRIVATE include)

# Link libraries
target_link_libraries(ZeroEngine PRIVATE 
  fmt::fmt-header-only
  spdlog::spdlog_header_only 
  CLI11::CLI11 
  SDL3::SDL3 
  OpenGL32
)

# Enable ALL compiler warnings
target_compile_options(ZeroEngine PRIVATE -Wall -Wextra -Wpedantic -Werror)

# Copy shaders into build dir
add_custom_target(Resources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders
  ${CMAKE_CURRENT_BINARY_DIR}/assets/shaders
  COMMENT "Copying shaders to build directory"
)
cmake_minimum_required(VERSION 3.10)

project(ZeroEngine)

set(C_STANDARD_REQUIRED TRUE)
set(CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(C_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)

find_package(CLI11 CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(SOURCES
  src/main.cpp
  src/App/App.cpp
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
target_link_libraries(ZeroEngine PRIVATE spdlog::spdlog_header_only CLI11::CLI11 SDL3::SDL3)

# Enable ALL compiler warnings
target_compile_options(ZeroEngine PRIVATE -Wall -Wextra -Wpedantic -Werror)
cmake_minimum_required(VERSION 3.22.1)

project(
  tootep
  VERSION "1.0.0"
  LANGUAGES "CXX")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} src/core.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Wshadow)
set_target_properties(
  ${PROJECT_NAME} PROPERTIES VERSION ${CMAKE_PROJECT_VERSION}
                             SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})

enable_testing()
add_subdirectory(tests)

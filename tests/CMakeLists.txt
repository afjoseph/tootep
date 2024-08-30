cmake_minimum_required(VERSION 3.22.1)
project(tootep-tests)

# Path to the libsodium source directory
set(LIBSODIUM_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ext/libsodium)

# Command to build libsodium as a static library using zig
add_custom_command(
  OUTPUT ${LIBSODIUM_DIR}/zig-out/lib/libsodium.a
  COMMAND zig clean && zig build -Dstatic=true
  WORKING_DIRECTORY ${LIBSODIUM_DIR}
  COMMENT "Building libsodium as a static library using zig"
  VERBATIM)

# Custom target to ensure libsodium is built before linking
add_custom_target(build_libsodium ALL
                  DEPENDS ${LIBSODIUM_DIR}/zig-out/lib/libsodium.a)

# Add the static libsodium library to the project
add_library(sodium STATIC IMPORTED)
set_target_properties(
  sodium PROPERTIES IMPORTED_LOCATION ${LIBSODIUM_DIR}/zig-out/lib/libsodium.a)

add_executable(${PROJECT_NAME} test_core.cpp)

# Add header files of libsodium
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${LIBSODIUM_DIR}/src/libsodium/include)

# Add googletest as a testing framework
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ext/googletest
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest)

# Ensure libsodium is built before linking
add_dependencies(${PROJECT_NAME} build_libsodium)

# Link libsodium and other dependencies to the executable
target_link_libraries(
  ${PROJECT_NAME} PRIVATE tootep sodium GTest::gtest GTest::gtest_main
                          GTest::gmock GTest::gmock_main)

target_include_directories(${PROJECT_NAME}
                           PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE ${GTEST_INCLUDE_DIRS})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

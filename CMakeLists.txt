cmake_minimum_required(VERSION 3.10)
project(test_json_checker VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)

# Add executable
add_executable(${PROJECT_NAME} main.c)

# Copy JsonChecker directory to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/JsonChecker DESTINATION ${CMAKE_BINARY_DIR})

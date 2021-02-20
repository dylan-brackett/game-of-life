cmake_minimum_required(VERSION 3.0.0)
project(life VERSION 0.1.0)
set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} include/)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra -Werror)

add_executable(life src/life.cpp src/main.cpp src/ltimer.cpp)
target_link_libraries(life PRIVATE SDL2)
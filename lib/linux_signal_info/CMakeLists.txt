cmake_minimum_required(VERSION 3.19)
project(info_linux_signal VERSION 0.0.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)
add_subdirectory(src)

message("lib: ${CMAKE_PROJECT_NAME} will be linked from:\n${my_libs_objects}")
add_library("${CMAKE_PROJECT_NAME}" STATIC ${my_libs_objects})
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "include")
target_compile_options("${CMAKE_PROJECT_NAME}" PUBLIC -g -Wall)


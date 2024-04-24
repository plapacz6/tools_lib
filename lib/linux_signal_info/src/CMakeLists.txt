cmake_minimum_required(VERSION 3.19)
project(info_linux_signal VERSION 0.0.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

list(APPEND my_libs
    signal_str2int
)
foreach(my_lib IN LISTS my_libs)    
    list(APPEND my_libs_target_objects $<TARGET_OBJECTS:${my_libs}>)
    add_library("${my_lib}" OBJECT "${my_lib}.c")
    target_include_directories("${my_lib}" PUBLIC "../include")
    target_compile_options("${my_lib}" PUBLIC -g -Wall)
endforeach()

add_subdirectory(tests)

# message("my_libs_target_objects: ${my_libs_target_objects}")
set(my_libs_objects ${my_libs_target_objects} PARENT_SCOPE)
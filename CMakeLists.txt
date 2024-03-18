cmake_minimum_required(VERSION 3.19)
project(struct_01 VERSION 0.0.1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


list(APPEND my_libs
    print_bits
)
foreach(my_lib IN LISTS my_libs)
    add_library("${my_lib}" SHARED "${my_lib}.c")
    target_include_directories("${my_lib}" PUBLIC ".")
    target_compile_options(${my_lib} PUBLIC -g -Wall)
    # target_link_libraries(${my_lib} PUBLIC
    #     m
    # )    
endforeach()

add_subdirectory(tests)
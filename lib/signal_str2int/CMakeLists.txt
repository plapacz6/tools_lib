#[[
Copyright 2024-2024 plapacz6@gmail.com

This file is part of signal_str2int.

signal_str2int is free software: you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free
Software Foundation, either version 3 of the License, or (at your option) any
later version.

signal_str2int is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
details.

You should have received a copy of the GNU Lesser General Public License along
 with signal_str2int. If not, see <https://www.gnu.org/licenses/>.
#]]

cmake_minimum_required(VERSION 3.19)
project(struct_01 VERSION 0.0.1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


list(APPEND my_libs
    signal_str2int
)
foreach(my_lib IN LISTS my_libs)
    add_library("${my_lib}" STATIC "${my_lib}.c")
    target_include_directories("${my_lib}" PUBLIC ".")
    target_compile_options("${my_lib}" PUBLIC -g -Wall)
endforeach()

add_subdirectory(tests)
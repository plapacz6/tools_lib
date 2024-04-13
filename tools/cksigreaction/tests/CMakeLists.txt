# Copyright 2024-2024 plapacz6@gmail.com

# This file is part of cksigreaction.

# cksigreaction is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option) any
# later version.

# cksigreaction is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public License along
#  with cksigreaction. If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.19)
project(struct_01 VERSION 0.0.1)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

enable_testing()
foreach(my_lib IN LISTS my_libs)
    list(APPEND my_lib_tests "${my_lib}_test")        
endforeach()


foreach(my_lib_test my_lib 
        IN ZIP_LISTS 
        my_lib_tests my_libs)
    message("${my_lib_test} : ${my_lib}")        
    add_executable("${my_lib_test}" "${my_lib_test}.cpp")
    target_compile_options(${my_lib_test} PRIVATE -g -Wall -pthread)
    target_link_libraries(${my_lib_test} PRIVATE
        "${my_lib}"
        GTest::GTest
        GTest::gtest_main
        pthread
    )        
    add_test("${my_lib_test}_runner" "${my_lib_test}")
endforeach()


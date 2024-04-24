cmake_minimum_required(VERSION 3.19)

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


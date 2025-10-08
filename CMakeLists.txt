message(host system name == ${CMAKE_HOST_SYSTEM_NAME})
cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# force the MSVC to consider source files' encoding as utf-8
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

project("bj")

add_subdirectory("bj")


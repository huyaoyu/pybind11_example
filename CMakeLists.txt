cmake_minimum_required(VERSION 3.17)
project(01_CLionTest)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(DynamicLibrary)

set(EXE_NAME 01_CLionTest)
add_executable(${EXE_NAME} main.cpp)
target_link_libraries(${EXE_NAME} DynaLib)
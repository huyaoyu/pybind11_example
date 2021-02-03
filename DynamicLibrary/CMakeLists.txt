cmake_minimum_required(VERSION 3.17)
project(DynamicLibrary LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 17)

set(LIB_NAME DynaLib)
add_library( ${LIB_NAME} SHARED src/DynamicLibrary.cpp )
target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>)

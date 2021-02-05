cmake_minimum_required(VERSION 3.16)
project(01_CLionTest)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED NO_MODULE)

set(CGAL_DIR /home/yaoyu/Libraries/cgal)
find_package(CGAL REQUIRED COMPONENTS Qt5 OPTIONAL_COMPONENTS Core )
message(STATUS "CGAL_LIBRARIES=${CGAL_LIBRARIES}")

if(CGAL_Qt5_FOUND)
    add_definitions(-DCGAL_USE_BASIC_VIEWER -DQT_NO_KEYWORDS)
endif()

add_subdirectory(pybind11)

add_subdirectory(DynamicLibrary)

set(EXE_NAME 01_CLionTest)
add_executable(${EXE_NAME} main.cpp)
target_link_libraries(${EXE_NAME} Eigen3::Eigen ${CGAL_LIBRARIES} DynaLib)
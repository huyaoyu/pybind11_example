cmake_minimum_required(VERSION 3.16)
project(DynamicLibrary LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 17)

# Boost and its components
find_package( Boost REQUIRED )

find_package(Eigen3 REQUIRED NO_MODULE)

#if( EIGEN3_FOUND )
#    message(STATUS "Eigen3 found. ")
#    message(STATUS "EIGEN3_INCLUDE_DIR=${EIGEN3_INCLUDE_DIR}")
#endif()

set(CGAL_DIR /home/yaoyu/Libraries/cgal)
find_package(CGAL REQUIRED COMPONENTS Qt5 OPTIONAL_COMPONENTS Core )
message(STATUS "CGAL_LIBRARIES=${CGAL_LIBRARIES}")

if(CGAL_Qt5_FOUND)
    add_definitions(-DCGAL_USE_BASIC_VIEWER -DQT_NO_KEYWORDS)
endif()

set(LIB_NAME DynaLib)
add_library( ${LIB_NAME} SHARED src/DynamicLibrary.cpp )
target_include_directories(${LIB_NAME} PUBLIC $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>)
target_link_libraries(${LIB_NAME} PRIVATE Eigen3::Eigen ${CGAL_LIBRARIES} )

set(LIB_NAME_PY ${LIB_NAME}_py)
pybind11_add_module( ${LIB_NAME_PY} src/DynamicLibrary_pb11.cpp )
target_include_directories(${LIB_NAME_PY} PUBLIC
        $<BUILD_INTERFACE:${${PROJECT_NAME}_SOURCE_DIR}/include>)
if( DEFINED SPECIFIC_PYTHON_INCLUDE )
    message(STATUS "SPECIFIC_PYTHON_INCLUDE=${SPECIFIC_PYTHON_INCLUDE}")
    target_include_directories(${LIB_NAME_PY} PRIVATE
            ${SPECIFIC_PYTHON_INCLUDE})
endif()
target_link_libraries( ${LIB_NAME_PY} PRIVATE Eigen3::Eigen ${CGAL_LIBRARIES} ${LIB_NAME} )


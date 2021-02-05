//
// Created by yaoyu on 2/3/21.
//

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <string>

#include "DynamicLibrary/DynamicLibrary.hpp"

namespace py = pybind11;

// Function template for DL::DynaMesh class template.
template < typename F_T >
void declare_dynamesh( py::module &m, const std::string& typeStr ) {
    using Class = DL::DynaMesh<F_T>;
    const std::string PYClassName = std::string("DynaMesh") + typeStr;

    py::class_<Class>(m, PYClassName.c_str())
            .def( py::init<>() )
            .def( "convert_2_cgal_mesh", &Class::convert_2_cgal_mesh );
}

PYBIND11_MODULE( DynaLib_py, m ) {
    py::class_<DL::DynaLib_0>(m, "DynaLib_0")
            .def( py::init<>() )
            .def( "set_init", &DL::DynaLib_0::set_int )
            .def( "get_int", &DL::DynaLib_0::get_int )
            .def( "increase_int", &DL::DynaLib_0::increase_int );

    py::class_<DL::DynaEigen>(m, "DynaEigen")
            .def( py::init<>() )
            .def( "change_through_reference",
                  &DL::DynaEigen::change_through_reference<DL::MatrixXdR>,
                  "Change the input array by reference. float64 version." )
            .def( "change_through_reference",
                  &DL::DynaEigen::change_through_reference<DL::MatrixXfR>,
                  "Change the input array by reference. float32 version" )
            .def( "return_matrix_by_value", &DL::DynaEigen::return_matrix_by_value,
                  py::return_value_policy::take_ownership );

    declare_dynamesh<double>(m, "Double");
    declare_dynamesh<float>(m, "Float");
}
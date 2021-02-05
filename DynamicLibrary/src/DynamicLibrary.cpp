//
// Created by yaoyu on 2/3/21.
//

#include <iostream>

#include "DynamicLibrary/DynamicLibrary.hpp"

using namespace DL;

void DynaLib_0::increase_int() {
    mInt++;
}

//void DynaEigen::change_through_reference(Eigen::Ref<DL::MatrixXdR> matRef) {
//    std::cout << "float64: \n"
//              << "matRef.rows() = " << matRef.rows() << ", "
//              << "matRef.cols() = " << matRef.cols() << '\n';
//
//    matRef.array() += 1.0;
//}
//
//void DynaEigen::change_through_reference(Eigen::Ref<DL::MatrixXfR> matRef) {
//    std::cout << "float32: \n"
//              << "matRef.rows() = " << matRef.rows() << ", "
//              << "matRef.cols() = " << matRef.cols() << '\n';
//
//    matRef.array() += 1.0;
//}

template void DynaEigen::change_through_reference<>( Eigen::Ref<MatrixXdR>);
template void DynaEigen::change_through_reference<>( Eigen::Ref<MatrixXfR>);

MatrixXdR DynaEigen::return_matrix_by_value() {
    MatrixXdR mat = MatrixXdR::Ones( 3,4 );
    return mat;
}

// Initialization of DynaMesh class.

namespace DL
{
    template class DynaMesh<double>;
    template class DynaMesh<float>;
}

//
// Created by yaoyu on 2/3/21.
//

#ifndef INC_01_CLIONTEST_DYNAMICLIBRARY_HPP
#define INC_01_CLIONTEST_DYNAMICLIBRARY_HPP

#include <iostream>
#include <sstream>
#include <vector>

#include <Eigen/Dense>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>

#include "TypeName.hpp"

namespace DL
{
    class DynaLib_0 {
    public:
        DynaLib_0() = default;
        ~DynaLib_0() = default;

        void set_int( int v ) { mInt = v; }
        int get_int() const { return mInt; }

        void increase_int();

    private:
        int mInt = 0;
    };

    typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixXdR;
    typedef Eigen::Matrix<float,  Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixXfR;

    struct DynaEigen {
        DynaEigen() = default;
        ~DynaEigen() = default;

//        void change_through_reference( Eigen::Ref< MatrixXdR > matRef );
//        void change_through_reference( Eigen::Ref< MatrixXfR > matRef );
        template < typename T >
        void change_through_reference( Eigen::Ref<T> matRef );
        MatrixXdR return_matrix_by_value();
    };

    template < typename T >
    void DynaEigen::change_through_reference(Eigen::Ref<T> matRef) {
        std::cout << "Type of matRef is " << TYPE_NAME(matRef) << '\n'
                  << "matRef.rows() = " << matRef.rows() << ", "
                  << "matRef.cols() = " << matRef.cols() << '\n';
        matRef.array() += 1;
    }

    typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel_t;
    typedef Kernel_t::Point_3              Point_t;
    typedef Kernel_t::Vector_3             Vector_t;
    typedef CGAL::Surface_mesh<Point_t>    Mesh_t;
    typedef Mesh_t::Vertex_index           VertexIdx_t;
    typedef Mesh_t::Face_index             FaceIdx_t;

    typedef boost::graph_traits<Mesh_t>::face_descriptor     FaceDesc_t;
    typedef boost::graph_traits<Mesh_t>::edge_descriptor     EdgeDesc_t;
    typedef boost::graph_traits<Mesh_t>::halfedge_descriptor HalfedgeDesc_t;
    typedef boost::graph_traits<Mesh_t>::vertex_descriptor   VertexDesc_t;

    template < typename F_T >
    using MatrixXR = Eigen::Matrix< F_T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor >;

    template < typename F_T >
    struct DynaMesh {
        DynaMesh() = default;

        void convert_2_cgal_mesh(
                const Eigen::Ref<const MatrixXR<F_T>>& vertices,
                const Eigen::Ref<const MatrixXR<int>>& faces ) {
            // Check if mesh is already created.
            if ( mesh.number_of_vertices() != 0 ) {
                throw std::runtime_error("mesh is already created. ");
            }

            // Prepare space for the vertices ans faces.
            const int nVertices = vertices.cols();
            const int nFaces    = faces.rows();

            std::vector<VertexDesc_t> vertVec;
            vertVec.reserve( nVertices );

            // Build the mesh.
            for ( int i = 0; i < nVertices; i++ ) {
                auto dp = mesh.add_vertex( Point_t(
                        vertices(0, i), vertices(1, i), vertices(2, i) ) );
                vertVec.push_back(dp);
            }

            for ( int i = 0; i < nFaces; i++ ) {
                const int v0 = faces(i, 0);
                const int v1 = faces(i, 1);
                const int v2 = faces(i, 2);

                auto f = mesh.add_face( vertVec[v0], vertVec[v1], vertVec[v2] );

                if ( f == Mesh_t::null_face() ) {
                    // Try a new other.
                    f = mesh.add_face(vertVec[v0], vertVec[v2], vertVec[v1]);
                    if ( f == Mesh_t::null_face() ) {
                        std::stringstream ss;
                        ss << "Cannot add face with vertex indices "
                           << v0 << ", " << v1 << ", " << v2 << ". ";
                        throw std::runtime_error(ss.str());
                    }
                }
            }

            if ( CGAL::is_valid_polygon_mesh(mesh) ) {
                std::cout << "Converted to CGAL mesh. \n";
                std::cout << "mesh.number_of_vertices() = " << mesh.number_of_vertices() << '\n';
                std::cout << "mesh.number_of_faces()    = " << mesh.number_of_faces() << '\n';
            } else {
                throw std::runtime_error("The converted mesh is invalid. ");
            }
        }

        Mesh_t mesh;
    };
}

#endif //INC_01_CLIONTEST_DYNAMICLIBRARY_HPP

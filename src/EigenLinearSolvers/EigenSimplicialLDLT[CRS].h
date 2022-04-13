#pragma once
#include <EigenLinearSolvers/config.h>

#include <EigenLinearSolvers/EigenSimplicialLDLT.h>
#include <EigenLinearSolvers/EigenDirectSparseSolver[CRS].h>

#include <Eigen/SparseCore>
#include <Eigen/SparseCholesky>

namespace EigenLinearSolvers
{

/**
 * Partial template specialization of EigenSimplicialLDLT for a matrix of type CompressedRowSparseMatrix
 */
template<class TBlockType>
class EigenSimplicialLDLT<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
        sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real> >
    : public EigenDirectSparseSolver<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
        sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>,
        Eigen::SimplicialLDLT<Eigen::SparseMatrix<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real> >
    >
{
public:
    typedef sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType> Matrix;
    using Real = typename Matrix::Real;
    typedef sofa::linearalgebra::FullVector<Real> Vector;
    using EigenSolver = Eigen::SimplicialLDLT<Eigen::SparseMatrix<Real> >;

    SOFA_CLASS(SOFA_TEMPLATE2(EigenSimplicialLDLT, Matrix, Vector),SOFA_TEMPLATE3(EigenDirectSparseSolver, Matrix, Vector, EigenSolver));

};

#ifndef EIGENLINEARSOLVERS_EIGENEIGENSIMPLICIALLDLT_CRS_CPP
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> >;
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT<
        sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
        sofa::linearalgebra::FullVector<SReal> >;
#endif

}

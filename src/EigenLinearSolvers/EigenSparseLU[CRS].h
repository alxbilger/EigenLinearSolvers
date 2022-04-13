#pragma once
#include <EigenLinearSolvers/config.h>

#include <EigenLinearSolvers/EigenSparseLU.h>
#include <EigenLinearSolvers/EigenDirectSparseSolver[CRS].h>

#include <Eigen/SparseCore>
#include <Eigen/SparseLU>

namespace EigenLinearSolvers
{

/**
 * Partial template specialization of EigenSparseLU for a matrix of type CompressedRowSparseMatrix
 */
template<class TBlockType>
class EigenSparseLU<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
        sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real> >
    : public EigenDirectSparseSolver<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
        sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>,
        Eigen::SparseLU<Eigen::SparseMatrix<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>, Eigen::COLAMDOrdering<typename Eigen::SparseMatrix<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>::StorageIndex> >
    >
{
public:
    typedef sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType> Matrix;
    using Real = typename Matrix::Real;
    typedef sofa::linearalgebra::FullVector<Real> Vector;
    using EigenSolver = Eigen::SparseLU<Eigen::SparseMatrix<Real>, Eigen::COLAMDOrdering<typename Eigen::SparseMatrix<Real>::StorageIndex> >;

    SOFA_CLASS(SOFA_TEMPLATE2(EigenSparseLU, Matrix, Vector), SOFA_TEMPLATE3(EigenDirectSparseSolver, Matrix, Vector, EigenSolver));

};

#ifndef EIGENLINEARSOLVERS_EIGENSPARSELU_CRS_CPP
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSparseLU< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> >;
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSparseLU<
        sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
        sofa::linearalgebra::FullVector<SReal> >;
#endif

}

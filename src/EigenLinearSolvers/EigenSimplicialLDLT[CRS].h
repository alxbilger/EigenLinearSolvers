#pragma once
#include <EigenLinearSolvers/config.h>

#include <EigenLinearSolvers/EigenSimplicialLDLT.h>
#include <sofa/component/linearsolver/iterative/MatrixLinearSolver.h>
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
    : public sofa::component::linearsolver::MatrixLinearSolver<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real> >
{
public:
    typedef sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType> Matrix;
    using Real = typename Matrix::Real;
    typedef sofa::linearalgebra::FullVector<Real> Vector;

    SOFA_CLASS(SOFA_TEMPLATE2(EigenSimplicialLDLT, Matrix, Vector),SOFA_TEMPLATE2(sofa::component::linearsolver::MatrixLinearSolver, Matrix, Vector));

    using EigenSparseMatrix = Eigen::SparseMatrix<Real, Eigen::RowMajor>;
    using EigenSparseMatrixMap = Eigen::Map<EigenSparseMatrix>;
    using EigenVectorXdMap = Eigen::Map<Eigen::Matrix<Real, Eigen::Dynamic, 1> >;

    void solve (Matrix& A, Vector& x, Vector& b) override;
    void invert(Matrix& A) override;

protected:
    Eigen::SimplicialLDLT<EigenSparseMatrixMap, Eigen::Lower> m_solver;

    sofa::linearalgebra::CompressedRowSparseMatrix<Real> Mfiltered;
    std::unique_ptr<EigenSparseMatrixMap> m_map;

    typename sofa::linearalgebra::CompressedRowSparseMatrix<Real>::VecIndex MfilteredrowBegin;
    typename sofa::linearalgebra::CompressedRowSparseMatrix<Real>::VecIndex MfilteredcolsIndex;
};

#ifndef EIGENLINEARSOLVERS_EIGENEIGENSIMPLICIALLDLT_CRS_CPP
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> >;
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT<
        sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
        sofa::linearalgebra::FullVector<SReal> >;
#endif

}

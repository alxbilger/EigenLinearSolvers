#pragma once
#include <EigenLinearSolvers/config.h>

#include <EigenLinearSolvers/EigenSimplicialLDLT.h>
#include <sofa/component/linearsolver/iterative/MatrixLinearSolver.h>
#include <Eigen/SparseCore>

namespace EigenLinearSolvers
{

/**
 * Partial template specialization of EigenSimplicialLDLT for a matrix of type CompressedRowSparseMatrix
 */
template<class TBlockType, class TEigenVector>
class EigenSimplicialLDLT<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::eigen::EigenVector<TEigenVector> >
    : public sofa::component::linearsolver::MatrixLinearSolver<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::eigen::EigenVector<TEigenVector> >
{
public:
    typedef sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType> Matrix;
    typedef sofa::linearalgebra::eigen::EigenVector<TEigenVector> Vector;

    SOFA_CLASS(SOFA_TEMPLATE2(EigenSimplicialLDLT, Matrix, Vector),SOFA_TEMPLATE2(sofa::component::linearsolver::MatrixLinearSolver, Matrix, Vector));

    using Real = typename Matrix::Real;
    using EigenSparseMatrix = Eigen::SparseMatrix<Real, Eigen::RowMajor>;
    using Map = Eigen::Map<EigenSparseMatrix>;

    void solve (Matrix& A, Vector& x, Vector& b) override;
    void invert(Matrix& A) override;

protected:
    Eigen::SimplicialLDLT<Map, Eigen::Lower> m_solver;

    sofa::linearalgebra::CompressedRowSparseMatrix<Real> Mfiltered;
    std::unique_ptr<Map> m_map;

    typename sofa::linearalgebra::CompressedRowSparseMatrix<Real>::VecIndex MfilteredrowBegin;
    typename sofa::linearalgebra::CompressedRowSparseMatrix<Real>::VecIndex MfilteredcolsIndex;
};

#ifndef EIGENLINEARSOLVERS_EIGENEIGENSIMPLICIALLDLT_CRS_CPP
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::eigen::EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > >;
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT<
        sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
        sofa::linearalgebra::eigen::EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > >;
#endif

}

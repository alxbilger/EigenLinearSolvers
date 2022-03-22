#pragma once
#include <EigenLinearSolvers/config.h>

#include <EigenLinearSolvers/EigenConjugateGradient.h>
#include <sofa/component/linearsolver/iterative/MatrixLinearSolver.h>
#include <Eigen/SparseCore>

namespace EigenLinearSolvers
{

/**
 * Partial template specialization of EigenConjugateGradient for a matrix of type CompressedRowSparseMatrix
 */
template<class TBlockType, class TEigenVector>
class EigenConjugateGradient<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::eigen::EigenVector<TEigenVector> >
    : public sofa::component::linearsolver::MatrixLinearSolver<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::eigen::EigenVector<TEigenVector> >
    , EigenConjugateGradientImpl<Eigen::SparseMatrix<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real, Eigen::RowMajor> >
{
public:
    typedef sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType> Matrix;
    typedef sofa::linearalgebra::eigen::EigenVector<TEigenVector> Vector;

    using Real = typename Matrix::Real;
    using EigenSparseMatrix = Eigen::SparseMatrix<Real, Eigen::RowMajor>;
    using Map = Eigen::Map<EigenSparseMatrix>;

    SOFA_CLASS2(SOFA_TEMPLATE2(EigenConjugateGradient, Matrix, Vector),SOFA_TEMPLATE2(sofa::component::linearsolver::MatrixLinearSolver, Matrix, Vector),
        EigenConjugateGradientImpl<EigenSparseMatrix>);

    void solve (Matrix& A, Vector& x, Vector& b) override;
    void invert(Matrix& A) override;

protected:
    using Inherit2::m_usedPreconditioner;
    using Inherit2::m_identityCG;
    using Inherit2::m_incompleteLUTCG;
    using Inherit2::m_diagonalCG;

    sofa::linearalgebra::CompressedRowSparseMatrix<Real> Mfiltered;
    std::unique_ptr<Map> m_map;

    typename sofa::linearalgebra::CompressedRowSparseMatrix<Real>::VecIndex MfilteredrowBegin;
    typename sofa::linearalgebra::CompressedRowSparseMatrix<Real>::VecIndex MfilteredcolsIndex;
};

#ifndef EIGENLINEARSOLVERS_EIGENCONJUGATEGRADIENT_CRS_CPP
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenConjugateGradient< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::eigen::EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > >;
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenConjugateGradient<
        sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
        sofa::linearalgebra::eigen::EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > >;
#endif

}

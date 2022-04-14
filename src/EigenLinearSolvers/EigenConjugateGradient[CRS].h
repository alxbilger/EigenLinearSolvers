#pragma once
#include <EigenLinearSolvers/config.h>

#include <EigenLinearSolvers/EigenConjugateGradient.h>

#if __has_include(<sofa/component/linearsolver/iterative/MatrixLinearSolver.h>)
#include <sofa/component/linearsolver/iterative/MatrixLinearSolver.h>
#else
#include <SofaBaseLinearSolver/MatrixLinearSolver.h>
#endif

#include <variant>
#include <Eigen/Core>
#include <Eigen/SparseCore>
#include <Eigen/Sparse>

#include <sofa/helper/OptionsGroup.h>

namespace EigenLinearSolvers
{

/**
 * Partial template specialization of EigenConjugateGradient for a matrix of type CompressedRowSparseMatrix
 */
template<class TBlockType>
class EigenConjugateGradient<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
        sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real> >
    : public sofa::component::linearsolver::MatrixLinearSolver<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
        sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real> >
{
public:
    typedef sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType> Matrix;
    using Real = typename Matrix::Real;
    typedef sofa::linearalgebra::FullVector<Real> Vector;

    using EigenSparseMatrix = Eigen::SparseMatrix<Real, Eigen::RowMajor>;
    using EigenSparseMatrixMap = Eigen::Map<EigenSparseMatrix>;
    using EigenVectorXdMap = Eigen::Map<Eigen::Matrix<Real, Eigen::Dynamic, 1> >;

    SOFA_CLASS(SOFA_TEMPLATE2(EigenConjugateGradient, Matrix, Vector),SOFA_TEMPLATE2(sofa::component::linearsolver::MatrixLinearSolver, Matrix, Vector));

    void init() override;
    void reinit() override;

    void solve (Matrix& A, Vector& x, Vector& b) override;
    void invert(Matrix& A) override;

protected:

    sofa::Data<unsigned> d_maxIter; ///< maximum number of iterations of the Conjugate Gradient solution
    sofa::Data<SReal> d_tolerance; ///< desired precision of the Conjugate Gradient Solution (ratio of current residual norm over initial residual norm)
    sofa::Data<sofa::helper::OptionsGroup> d_preconditioner;

    void updatePreconditioner();

    unsigned int m_usedPreconditioner { std::numeric_limits<unsigned int>::max()};

    std::variant<
        Eigen::ConjugateGradient<EigenSparseMatrix, Eigen::Lower|Eigen::Upper, Eigen::IdentityPreconditioner>,
        Eigen::ConjugateGradient<EigenSparseMatrix, Eigen::Lower|Eigen::Upper, Eigen::IncompleteLUT<Real> >,
        Eigen::ConjugateGradient<EigenSparseMatrix, Eigen::Lower|Eigen::Upper, Eigen::DiagonalPreconditioner<Real> >
    > m_solver;

    sofa::linearalgebra::CompressedRowSparseMatrix<Real> Mfiltered;
    std::unique_ptr<EigenSparseMatrixMap> m_map;

    typename sofa::linearalgebra::CompressedRowSparseMatrix<Real>::VecIndex MfilteredrowBegin;
    typename sofa::linearalgebra::CompressedRowSparseMatrix<Real>::VecIndex MfilteredcolsIndex;

    EigenConjugateGradient();
};

#ifndef EIGENLINEARSOLVERS_EIGENCONJUGATEGRADIENT_CRS_CPP
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenConjugateGradient< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> >;
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenConjugateGradient<
        sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
        sofa::linearalgebra::FullVector<SReal> >;
#endif

}

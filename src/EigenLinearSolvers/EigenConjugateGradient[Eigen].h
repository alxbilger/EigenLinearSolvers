#pragma once

#include <EigenLinearSolvers/config.h>
#include <EigenLinearSolvers/EigenConjugateGradient.h>
#include <sofa/linearalgebra/eigen/EigenMatrix.h>
#include <sofa/component/linearsolver/iterative/MatrixLinearSolver.h>
#include <sofa/helper/OptionsGroup.h>

namespace EigenLinearSolvers
{

/**
 * Partial template specialization of EigenConjugateGradient for a matrix of type EigenMatrix
 */
template<class TEigenMatrix, class TEigenVector>
class EigenConjugateGradient<sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix>, sofa::linearalgebra::eigen::EigenVector<TEigenVector> >
    : public sofa::component::linearsolver::MatrixLinearSolver<
        sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix>, sofa::linearalgebra::eigen::EigenVector<TEigenVector> >
    , EigenConjugateGradientImpl<typename sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix>::EigenType>
{
public:
    typedef sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix> Matrix;
    typedef sofa::linearalgebra::eigen::EigenVector<TEigenVector> Vector;

    SOFA_CLASS2(SOFA_TEMPLATE2(EigenConjugateGradient, Matrix, Vector),
        SOFA_TEMPLATE2(sofa::component::linearsolver::MatrixLinearSolver, Matrix, Vector),
        EigenConjugateGradientImpl<typename sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix>::EigenType>);

    using EigenSparseMatrix = typename Matrix::EigenType;
    using Scalar = typename Matrix::Scalar;

    void init() override;

    /// Solve iteratively the linear system Ax=b following a conjugate gradient descent
    void solve (Matrix& A, Vector& x, Vector& b) override;
    void invert(Matrix& A) override;

protected:
    using Inherit2::m_usedPreconditioner;
    using Inherit2::m_identityCG;
    using Inherit2::m_incompleteLUTCG;
    using Inherit2::m_diagonalCG;

};

#ifndef EIGENLINEARSOLVERS_EIGENCONJUGATEGRADIENT_EIGEN_CPP
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenConjugateGradient<
        sofa::linearalgebra::eigen::EigenMatrix<Eigen::SparseMatrix<SReal, Eigen::RowMajor> >,
        sofa::linearalgebra::eigen::EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > >
    >;
#endif

}

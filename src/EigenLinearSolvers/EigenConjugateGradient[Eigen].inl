#pragma once
#include <EigenLinearSolvers/EigenConjugateGradient[Eigen].h>
#include <thread>

namespace EigenLinearSolvers
{

template <class TEigenMatrix, class TEigenVector>
void EigenConjugateGradient<sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix>, sofa::linearalgebra::eigen::EigenVector<TEigenVector> >::init()
{
    Eigen::setNbThreads(std::thread::hardware_concurrency() / 2);
}

template <class TEigenMatrix, class TEigenVector>
void EigenConjugateGradient<sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix>, sofa::linearalgebra::eigen::EigenVector<TEigenVector> >::solve(Matrix& A, Vector& x, Vector& b)
{
    if (m_usedPreconditioner == 0)
    {
        x.vector() = m_identityCG.solveWithGuess(b.vector(), x.vector());
    }
    else if (m_usedPreconditioner == 2)
    {
        x.vector() = m_incompleteLUTCG.solveWithGuess(b.vector(), x.vector());
    }
    else
    {
        x.vector() = m_diagonalCG.solveWithGuess(b.vector(), x.vector());
    }
}

template <class TEigenMatrix, class TEigenVector>
void EigenConjugateGradient<sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix>, sofa::linearalgebra::eigen::EigenVector<TEigenVector> >::invert(Matrix& A)
{
    m_usedPreconditioner = this->d_preconditioner.getValue().getSelectedId();

    if (m_usedPreconditioner == 0)
    {
        m_identityCG.setTolerance(this->d_tolerance.getValue());
        m_identityCG.setMaxIterations(this->d_maxIter.getValue());
        m_identityCG.compute(A.matrix());
    }
    else if (m_usedPreconditioner == 2)
    {
        m_incompleteLUTCG.setTolerance(this->d_tolerance.getValue());
        m_incompleteLUTCG.setMaxIterations(this->d_maxIter.getValue());
        m_incompleteLUTCG.compute(A.matrix());
    }
    else
    {
        m_diagonalCG.setTolerance(this->d_tolerance.getValue());
        m_diagonalCG.setMaxIterations(this->d_maxIter.getValue());
        m_diagonalCG.compute(A.matrix());
    }

}


}

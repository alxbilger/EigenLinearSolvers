#pragma once
#include <EigenLinearSolvers/EigenSimplicialLDLT[Eigen].h>


namespace EigenLinearSolvers
{

template <class TEigenMatrix, class TEigenVector>
void EigenSimplicialLDLT<sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix>, sofa::linearalgebra::eigen::EigenVector<TEigenVector
>>::solve(Matrix& A, Vector& x, Vector& b)
{
    x.vector() = m_solver.solve(b.vector());
}

template <class TEigenMatrix, class TEigenVector>
void EigenSimplicialLDLT<sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix>, sofa::linearalgebra::eigen::EigenVector<TEigenVector
>>::invert(Matrix& A)
{
    if (m_analyzePattern)
    {
        m_solver.analyzePattern(A.matrix());
        m_analyzePattern = false;
    }
    m_solver.factorize(A.matrix());
}

}

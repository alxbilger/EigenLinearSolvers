#pragma once
#include <EigenLinearSolvers/EigenConjugateGradient[CRS].h>

#include <sofa/helper/ScopedAdvancedTimer.h>

namespace EigenLinearSolvers
{

template <class TBlockType>
void EigenConjugateGradient<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real> >
    ::solve(Matrix& A, Vector& x, Vector& b)
{
    SOFA_UNUSED(A);
    sofa::helper::ScopedAdvancedTimer solveTimer("solve");

    EigenVectorXdMap xMap(x.ptr(), x.size());
    EigenVectorXdMap bMap(b.ptr(), b.size());

    if (m_usedPreconditioner == 0)
    {
        xMap = m_identityCG.solveWithGuess(bMap, xMap);
    }
    else if (m_usedPreconditioner == 2)
    {
        xMap = m_incompleteLUTCG.solveWithGuess(bMap, xMap);
    }
    else
    {
        xMap = m_diagonalCG.solveWithGuess(bMap, xMap);
    }
}

template <class TBlockType>
void EigenConjugateGradient<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real> >
    ::invert(Matrix& A)
{
    {
        sofa::helper::ScopedAdvancedTimer copyTimer("copyMatrixData");
        Mfiltered.copyNonZeros(A);
        Mfiltered.compress();
    }

    if (!m_map)
    {
        m_map = std::make_unique<EigenSparseMatrixMap>(Mfiltered.rows(), Mfiltered.cols(), Mfiltered.getColsValue().size(),
            (typename EigenSparseMatrixMap::StorageIndex*)Mfiltered.rowBegin.data(), (typename EigenSparseMatrixMap::StorageIndex*)Mfiltered.colsIndex.data(), Mfiltered.colsValue.data());
    }

    m_usedPreconditioner = this->d_preconditioner.getValue().getSelectedId();

    sofa::helper::ScopedAdvancedTimer factorizationTimer("factorization");
    if (m_usedPreconditioner == 0)
    {
        m_identityCG.setTolerance(this->d_tolerance.getValue());
        m_identityCG.setMaxIterations(this->d_maxIter.getValue());
        m_identityCG.compute(*m_map);
    }
    else if (m_usedPreconditioner == 2)
    {
        m_incompleteLUTCG.setTolerance(this->d_tolerance.getValue());
        m_incompleteLUTCG.setMaxIterations(this->d_maxIter.getValue());
        m_incompleteLUTCG.compute(*m_map);
    }
    else
    {
        m_diagonalCG.setTolerance(this->d_tolerance.getValue());
        m_diagonalCG.setMaxIterations(this->d_maxIter.getValue());
        m_diagonalCG.compute(*m_map);
    }
}

}

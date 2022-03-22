#pragma once
#include <EigenLinearSolvers/EigenConjugateGradient[CRS].h>

#include <sofa/helper/ScopedAdvancedTimer.h>

namespace EigenLinearSolvers
{

template <class TBlockType, class TEigenVector>
void EigenConjugateGradient<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::eigen::EigenVector<
TEigenVector>>::solve(Matrix& A, Vector& x, Vector& b)
{
    sofa::helper::ScopedAdvancedTimer solveTimer("solve");
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

template <class TBlockType, class TEigenVector>
void EigenConjugateGradient<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::eigen::EigenVector<
TEigenVector>>::invert(Matrix& A)
{
    {
        sofa::helper::ScopedAdvancedTimer copyTimer("copyMatrixData");
        Mfiltered.copyNonZeros(A);
        Mfiltered.compress();
    }

    if (!m_map)
    {
        m_map = std::make_unique<Map>(Mfiltered.rows(), Mfiltered.cols(), Mfiltered.getColsValue().size(),
            (typename Map::StorageIndex*)Mfiltered.rowBegin.data(), (typename Map::StorageIndex*)Mfiltered.colsIndex.data(), Mfiltered.colsValue.data());
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

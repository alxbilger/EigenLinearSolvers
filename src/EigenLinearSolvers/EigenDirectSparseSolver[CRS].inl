#pragma once
#include <EigenLinearSolvers/EigenDirectSparseSolver[CRS].h>

#include <sofa/helper/ScopedAdvancedTimer.h>

namespace EigenLinearSolvers
{

template <class TBlockType, class EigenSolver>
void EigenDirectSparseSolver<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>, EigenSolver >
    ::solve(Matrix& A, Vector& x, Vector& b)
{
    EigenVectorXdMap xMap(x.ptr(), x.size());
    EigenVectorXdMap bMap(b.ptr(), b.size());
    xMap = m_solver.solve(bMap);
}

template <class TBlockType, class EigenSolver>
void EigenDirectSparseSolver<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>, EigenSolver >
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

    const bool analyzePattern = (MfilteredrowBegin != Mfiltered.rowBegin) || (MfilteredcolsIndex != Mfiltered.colsIndex);

    if (analyzePattern)
    {
        sofa::helper::ScopedAdvancedTimer patternAnalysisTimer("patternAnalysis");
        m_solver.analyzePattern(*m_map);

        MfilteredrowBegin = Mfiltered.rowBegin;
        MfilteredcolsIndex = Mfiltered.colsIndex;
    }

    {
        sofa::helper::ScopedAdvancedTimer factorizeTimer("factorization");
        m_solver.factorize(*m_map);
    }

    msg_error_when(m_solver.info() == Eigen::ComputationInfo::InvalidInput) << "Solver cannot factorize: invalid input";
    msg_error_when(m_solver.info() == Eigen::ComputationInfo::NoConvergence) << "Solver cannot factorize: no convergence";
    msg_error_when(m_solver.info() == Eigen::ComputationInfo::NumericalIssue) << "Solver cannot factorize: numerical issue";
}

}

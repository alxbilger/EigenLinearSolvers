#pragma once
#include <EigenLinearSolvers/EigenSimplicialLDLT[CRS].h>

#include <sofa/helper/ScopedAdvancedTimer.h>

namespace EigenLinearSolvers
{

template <class TBlockType, class TEigenVector>
void EigenSimplicialLDLT<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::eigen::EigenVector<
TEigenVector>>::solve(Matrix& A, Vector& x, Vector& b)
{
    x.vector() = m_solver.solve(b.vector());
}

template <class TBlockType, class TEigenVector>
void EigenSimplicialLDLT<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::eigen::EigenVector<
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

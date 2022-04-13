#pragma once
#include <EigenLinearSolvers/EigenDirectSparseSolver[CRS].h>

#include <sofa/helper/ScopedAdvancedTimer.h>

namespace EigenLinearSolvers
{
template <class TBlockType, class EigenSolver>
void EigenDirectSparseSolver<
    sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
    sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>, EigenSolver>
    ::init()
{
    updateSolverOderingMethod();
}

template <class TBlockType, class EigenSolver>
void EigenDirectSparseSolver<
    sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
    sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>, EigenSolver>
    ::reinit()
{
    updateSolverOderingMethod();
}

template <class TBlockType, class EigenSolver>
void EigenDirectSparseSolver<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>, EigenSolver >
    ::solve(Matrix& A, Vector& x, Vector& b)
{
    SOFA_UNUSED(A);

    EigenVectorXdMap xMap(x.ptr(), x.size());
    EigenVectorXdMap bMap(b.ptr(), b.size());

    std::visit([&bMap, &xMap](auto&& solver)
    {
        xMap = solver.solve(bMap);
    }, m_solver);
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
        std::visit([this](auto&& solver)
        {
            solver.analyzePattern(*m_map);
        }, m_solver);

        MfilteredrowBegin = Mfiltered.rowBegin;
        MfilteredcolsIndex = Mfiltered.colsIndex;
    }

    {
        sofa::helper::ScopedAdvancedTimer factorizeTimer("factorization");
        std::visit([this](auto&& solver)
        {
            solver.factorize(*m_map);
        }, m_solver);
    }

    msg_error_when(getSolverInfo() == Eigen::ComputationInfo::InvalidInput) << "Solver cannot factorize: invalid input";
    msg_error_when(getSolverInfo() == Eigen::ComputationInfo::NoConvergence) << "Solver cannot factorize: no convergence";
    msg_error_when(getSolverInfo() == Eigen::ComputationInfo::NumericalIssue) << "Solver cannot factorize: numerical issue";
}

template <class TBlockType, class EigenSolver>
Eigen::ComputationInfo EigenDirectSparseSolver<
    sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
    sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>, EigenSolver>
::getSolverInfo() const
{
    Eigen::ComputationInfo info;
    std::visit([&info](auto&& solver)
    {
        info = solver.info();
    }, m_solver);
    return info;
}

template <class TBlockType, class EigenSolver>
void EigenDirectSparseSolver<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::FullVector
<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>, EigenSolver>::updateSolverOderingMethod()
{
    if (m_selectedOrderingMethod != d_orderingMethod.getValue().getSelectedId())
    {
        switch(d_orderingMethod.getValue().getSelectedId())
        {
        case 0:  m_solver.template emplace<NaturalOrderSolver>(); break;
        case 1:  m_solver.template emplace<AMDOrderSolver>(); break;
        case 2:  m_solver.template emplace<COLAMDOrderSolver>(); break;
        case 3:  m_solver.template emplace<MetisOrderSolver>(); break;
        default: m_solver.template emplace<AMDOrderSolver>(); break;
        }
        m_selectedOrderingMethod = d_orderingMethod.getValue().getSelectedId();
        if (m_selectedOrderingMethod > 2)
            m_selectedOrderingMethod = 1;

        MfilteredrowBegin.clear();
        MfilteredcolsIndex.clear();
        m_map.reset();
    }
}

template <class TBlockType, class EigenSolver>
EigenDirectSparseSolver<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::FullVector<
typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>, EigenSolver>::EigenDirectSparseSolver()
    : Inherit1()
    , d_orderingMethod(initData(&d_orderingMethod, "ordering", "Ordering method"))
{
    sofa::helper::OptionsGroup d_orderingMethodOptions(4,"Natural", "AMD", "COLAMD", "Metis");
    d_orderingMethodOptions.setSelectedItem(1); // default None
    d_orderingMethod.setValue(d_orderingMethodOptions);
}

}

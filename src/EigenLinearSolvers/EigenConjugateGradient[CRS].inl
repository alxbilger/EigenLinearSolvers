#pragma once
#include <EigenLinearSolvers/EigenConjugateGradient[CRS].h>

#include <sofa/helper/ScopedAdvancedTimer.h>

namespace EigenLinearSolvers
{

template <class TBlockType>
void EigenConjugateGradient<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::
FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>>::init()
{
    updatePreconditioner();
}

template <class TBlockType>
void EigenConjugateGradient<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::FullVector<
typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>>::reinit()
{
    updatePreconditioner();
}

template <class TBlockType>
void EigenConjugateGradient<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real> >
    ::solve(Matrix& A, Vector& x, Vector& b)
{
    SOFA_UNUSED(A);
    sofa::helper::ScopedAdvancedTimer solveTimer("solve");

    EigenVectorXdMap xMap(x.ptr(), x.size());
    EigenVectorXdMap bMap(b.ptr(), b.size());

    std::visit([&bMap, &xMap](auto&& solver)
    {
        xMap = solver.solveWithGuess(bMap, xMap);
    }, m_solver);
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

    sofa::helper::ScopedAdvancedTimer factorizationTimer("factorization");

    std::visit([this](auto&& solver)
    {
        solver.setTolerance(this->d_tolerance.getValue());
        solver.setMaxIterations(this->d_maxIter.getValue());
        solver.compute(*m_map);
    }, m_solver);
}

template <class TBlockType>
void EigenConjugateGradient<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::FullVector<
typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>>::updatePreconditioner()
{
    if (m_usedPreconditioner != d_preconditioner.getValue().getSelectedId())
    {
        switch(d_preconditioner.getValue().getSelectedId())
        {
        case 0:  m_solver.template emplace<std::variant_alternative_t<0, decltype(m_solver)> >(); break;
        case 1:  m_solver.template emplace<std::variant_alternative_t<1, decltype(m_solver)> >(); break;
        case 2:  m_solver.template emplace<std::variant_alternative_t<2, decltype(m_solver)> >(); break;
        default: m_solver.template emplace<std::variant_alternative_t<1, decltype(m_solver)> >(); break;
        }
        m_usedPreconditioner = d_preconditioner.getValue().getSelectedId();
        if (m_usedPreconditioner >= std::variant_size_v<decltype(m_solver)>)
            m_usedPreconditioner = 1;

        MfilteredrowBegin.clear();
        MfilteredcolsIndex.clear();
        m_map.reset();
    }
}

template <class TBlockType>
EigenConjugateGradient<sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>, sofa::linearalgebra::FullVector<
typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>>::EigenConjugateGradient(): Inherit1()
    , d_maxIter(initData(&d_maxIter, 25u, "iterations","Maximum number of iterations of the Conjugate Gradient solution"))
    , d_tolerance(initData(&d_tolerance, (Real)1e-5,"tolerance","Desired accuracy of the Conjugate Gradient solution evaluating: |r|²/|b|² (ratio of current residual norm over initial residual norm)"))
    , d_preconditioner(initData(&d_preconditioner, sofa::helper::OptionsGroup(3, "identity", "diagonal", "incompleteLUT"), "preconditioner", "The preconditioner used by this solver"))
{
    sofa::helper::getWriteOnlyAccessor(d_preconditioner)->setSelectedItem(1);
}
}

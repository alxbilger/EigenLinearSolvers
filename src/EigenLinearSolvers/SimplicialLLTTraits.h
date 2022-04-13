#pragma once
#include <EigenLinearSolvers/config.h>

#include <Eigen/SparseCholesky>
#include <Eigen/OrderingMethods>
#include <Eigen/MetisSupport>

namespace EigenLinearSolvers
{
    template<class Real>
    struct SimplicialLLTTraits
    {
        using EigenSolver = Eigen::SparseMatrix<Real>;
        using AMDOrderSolver = Eigen::SimplicialLLT<Eigen::SparseMatrix<Real>, Eigen::Lower, Eigen::AMDOrdering<typename EigenSolver::StorageIndex> >;
        using COLAMDOrderSolver = Eigen::SimplicialLLT<Eigen::SparseMatrix<Real>, Eigen::Lower, Eigen::COLAMDOrdering<typename EigenSolver::StorageIndex> >;
        using NaturalOrderSolver = Eigen::SimplicialLLT<Eigen::SparseMatrix<Real>, Eigen::Lower, Eigen::NaturalOrdering<typename EigenSolver::StorageIndex> >;
        using MetisOrderSolver = Eigen::SimplicialLLT<Eigen::SparseMatrix<Real>, Eigen::Lower, Eigen::MetisOrdering<typename EigenSolver::StorageIndex> >;
    };
}

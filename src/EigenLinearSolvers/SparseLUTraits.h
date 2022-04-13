#pragma once
#include <EigenLinearSolvers/config.h>

#include <Eigen/SparseLU>
#include <Eigen/OrderingMethods>
#include <Eigen/MetisSupport>

namespace EigenLinearSolvers
{
    template<class Real>
    struct SparseLUTraits
    {
        using EigenSolver = Eigen::SparseMatrix<Real>;
        using AMDOrderSolver = Eigen::SparseLU<Eigen::SparseMatrix<Real>, Eigen::AMDOrdering<typename EigenSolver::StorageIndex> >;
        using COLAMDOrderSolver = Eigen::SparseLU<Eigen::SparseMatrix<Real>, Eigen::COLAMDOrdering<typename EigenSolver::StorageIndex> >;
        using NaturalOrderSolver = Eigen::SparseLU<Eigen::SparseMatrix<Real>, Eigen::NaturalOrdering<typename EigenSolver::StorageIndex> >;
        using MetisOrderSolver = Eigen::SparseLU<Eigen::SparseMatrix<Real>, Eigen::MetisOrdering<typename EigenSolver::StorageIndex> >;
    };
}

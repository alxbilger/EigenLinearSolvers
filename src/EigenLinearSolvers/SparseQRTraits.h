#pragma once
#include <EigenLinearSolvers/config.h>

#include <Eigen/SparseQR>
#include <Eigen/OrderingMethods>

namespace EigenLinearSolvers
{
    template<class Real>
    struct SparseQRTraits
    {
        using EigenSolver = Eigen::SparseMatrix<Real>;
        using AMDOrderSolver = Eigen::SparseQR<Eigen::SparseMatrix<Real>, Eigen::AMDOrdering<typename EigenSolver::StorageIndex> >;
        using COLAMDOrderSolver = Eigen::SparseQR<Eigen::SparseMatrix<Real>, Eigen::COLAMDOrdering<typename EigenSolver::StorageIndex> >;
        using NaturalOrderSolver = Eigen::SparseQR<Eigen::SparseMatrix<Real>, Eigen::NaturalOrdering<typename EigenSolver::StorageIndex> >;
    };
}

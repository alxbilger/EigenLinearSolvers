#pragma once
#include <EigenLinearSolvers/config.h>

#include <Eigen/SparseLU>
#include <Eigen/OrderingMethods>
#include <EigenLinearSolvers/FindMetis.h>

namespace EigenLinearSolvers
{
    template<class Real>
    struct SparseLUTraits
    {
        using EigenSolver = Eigen::SparseMatrix<Real>;
        using AMDOrderSolver = Eigen::SparseLU<Eigen::SparseMatrix<Real>, Eigen::AMDOrdering<typename EigenSolver::StorageIndex> >;
        using COLAMDOrderSolver = Eigen::SparseLU<Eigen::SparseMatrix<Real>, Eigen::COLAMDOrdering<typename EigenSolver::StorageIndex> >;
        using NaturalOrderSolver = Eigen::SparseLU<Eigen::SparseMatrix<Real>, Eigen::NaturalOrdering<typename EigenSolver::StorageIndex> >;
#if EIGENLINEARSOLVERS_HAS_METIS_INCLUDE == 1
        using MetisOrderSolver = Eigen::SparseLU<Eigen::SparseMatrix<Real>, Eigen::MetisOrdering<typename EigenSolver::StorageIndex> >;
#endif
    };
}

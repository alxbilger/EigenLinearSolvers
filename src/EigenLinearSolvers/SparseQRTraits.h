#pragma once
#include <EigenLinearSolvers/config.h>

#include <Eigen/SparseQR>
#include <Eigen/OrderingMethods>
#include <EigenLinearSolvers/FindMetis.h>

namespace EigenLinearSolvers
{
    template<class Real>
    struct SparseQRTraits
    {
        using EigenSolver = Eigen::SparseMatrix<Real>;
        using AMDOrderSolver = Eigen::SparseQR<Eigen::SparseMatrix<Real>, Eigen::AMDOrdering<typename EigenSolver::StorageIndex> >;
        using COLAMDOrderSolver = Eigen::SparseQR<Eigen::SparseMatrix<Real>, Eigen::COLAMDOrdering<typename EigenSolver::StorageIndex> >;
        using NaturalOrderSolver = Eigen::SparseQR<Eigen::SparseMatrix<Real>, Eigen::NaturalOrdering<typename EigenSolver::StorageIndex> >;
#if EIGENLINEARSOLVERS_HAS_METIS_INCLUDE == 1
        using MetisOrderSolver = Eigen::SparseQR<Eigen::SparseMatrix<Real>, Eigen::MetisOrdering<typename EigenSolver::StorageIndex> >;
#endif
    };
}

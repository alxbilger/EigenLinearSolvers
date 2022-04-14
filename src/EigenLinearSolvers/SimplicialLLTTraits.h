#pragma once
#include <EigenLinearSolvers/config.h>

#include <Eigen/SparseCholesky>
#include <Eigen/OrderingMethods>
#include <EigenLinearSolvers/FindMetis.h>

namespace EigenLinearSolvers
{
    template<class Real>
    struct SimplicialLLTTraits
    {
        using EigenSolver = Eigen::SparseMatrix<Real>;
        using AMDOrderSolver = Eigen::SimplicialLLT<Eigen::SparseMatrix<Real>, Eigen::Lower, Eigen::AMDOrdering<typename EigenSolver::StorageIndex> >;
        using COLAMDOrderSolver = Eigen::SimplicialLLT<Eigen::SparseMatrix<Real>, Eigen::Lower, Eigen::COLAMDOrdering<typename EigenSolver::StorageIndex> >;
        using NaturalOrderSolver = Eigen::SimplicialLLT<Eigen::SparseMatrix<Real>, Eigen::Lower, Eigen::NaturalOrdering<typename EigenSolver::StorageIndex> >;
#if EIGENLINEARSOLVERS_HAS_METIS_INCLUDE == 1
        using MetisOrderSolver = Eigen::SimplicialLLT<Eigen::SparseMatrix<Real>, Eigen::Lower, Eigen::MetisOrdering<typename EigenSolver::StorageIndex> >;
#endif
    };
}

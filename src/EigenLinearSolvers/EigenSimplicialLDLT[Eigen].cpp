#define EIGENLINEARSOLVERS_EIGENEIGENSIMPLICIALLDLT_EIGEN_CPP
#include <EigenLinearSolvers/EigenSimplicialLDLT[Eigen].inl>
#include <sofa/component/linearsolver/iterative/MatrixLinearSolver.inl>
#include <sofa/core/ObjectFactory.h>

namespace EigenLinearSolvers
{
    using sofa::linearalgebra::eigen::EigenMatrix;
    using sofa::linearalgebra::eigen::EigenVector;

template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT< EigenMatrix<Eigen::SparseMatrix<SReal, Eigen::RowMajor> >, EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > >;

int EigenSimplicialLDLTEigenClass = sofa::core::RegisterObject("Direct Linear Solver using a Sparse LDL^T factorization.")
    .add< EigenSimplicialLDLT< EigenMatrix<Eigen::SparseMatrix<SReal, Eigen::RowMajor> >, EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > > >(true)
;

}

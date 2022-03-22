#define EIGENLINEARSOLVERS_EIGENEIGENSIMPLICIALLDLT_CRS_CPP
#include <EigenLinearSolvers/EigenSimplicialLDLT[CRS].inl>
#include <sofa/component/linearsolver/iterative/MatrixLinearSolver.inl>
#include <sofa/core/ObjectFactory.h>

namespace EigenLinearSolvers
{
using sofa::linearalgebra::eigen::EigenMatrix;
using sofa::linearalgebra::eigen::EigenVector;

template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::eigen::EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > >;
template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT<
    sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
    sofa::linearalgebra::eigen::EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > >;

int EigenSimplicialLDLTCRSClass = sofa::core::RegisterObject("Direct Linear Solver using a Sparse LDL^T factorization.")
.add< EigenSimplicialLDLT< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::eigen::EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > > >()
.add< EigenSimplicialLDLT< sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >, EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > > >()
;

}

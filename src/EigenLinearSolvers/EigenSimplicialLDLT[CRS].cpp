#define EIGENLINEARSOLVERS_EIGENEIGENSIMPLICIALLDLT_CRS_CPP
#include <EigenLinearSolvers/EigenSimplicialLDLT[CRS].inl>

#if __has_include(<sofa/component/linearsolver/iterative/MatrixLinearSolver.inl>)
#include <sofa/component/linearsolver/iterative/MatrixLinearSolver.inl>
#else
#include <SofaBaseLinearSolver/MatrixLinearSolver.inl>
#endif

#include <sofa/core/ObjectFactory.h>

namespace EigenLinearSolvers
{
template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> >;
template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT<
    sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
    sofa::linearalgebra::FullVector<SReal> >;

int EigenSimplicialLDLTCRSClass = sofa::core::RegisterObject("Direct Linear Solver using a Sparse LDL^T factorization.")
.add< EigenSimplicialLDLT< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> > >()
.add< EigenSimplicialLDLT< sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >, sofa::linearalgebra::FullVector<SReal> > >()
;

}

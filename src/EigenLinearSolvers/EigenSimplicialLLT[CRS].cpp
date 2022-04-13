#define EIGENLINEARSOLVERS_EIGENEIGENSIMPLICIALLLT_CRS_CPP
#include <EigenLinearSolvers/EigenSimplicialLLT[CRS].h>
#include <EigenLinearSolvers/EigenDirectSparseSolver[CRS].inl>

#include <sofa/core/ObjectFactory.h>

namespace EigenLinearSolvers
{
    template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLLT< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> >;
    template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLLT<
        sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
        sofa::linearalgebra::FullVector<SReal> >;

    int EigenSimplicialLLTCRSClass = sofa::core::RegisterObject("Direct Linear Solver using a Sparse LDL^T factorization.")
    .add< EigenSimplicialLLT< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> > >()
    .add< EigenSimplicialLLT< sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >, sofa::linearalgebra::FullVector<SReal> > >()
    ;

}

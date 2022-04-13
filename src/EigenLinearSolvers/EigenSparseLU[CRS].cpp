#define EIGENLINEARSOLVERS_EIGENSPARSELU_CRS_CPP
#include <EigenLinearSolvers/EigenSparseLU[CRS].h>
#include <EigenLinearSolvers/EigenDirectSparseSolver[CRS].inl>

#include <sofa/core/ObjectFactory.h>

namespace EigenLinearSolvers
{
    template class SOFA_EIGENLINEARSOLVERS_API EigenSparseLU< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> >;
    template class SOFA_EIGENLINEARSOLVERS_API EigenSparseLU<
        sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
        sofa::linearalgebra::FullVector<SReal> >;

    int EigenSparseLUCRSClass = sofa::core::RegisterObject("Direct Linear Solver using a Sparse LDL^T factorization.")
    .add< EigenSparseLU< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> > >()
    .add< EigenSparseLU< sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >, sofa::linearalgebra::FullVector<SReal> > >()
    ;

}

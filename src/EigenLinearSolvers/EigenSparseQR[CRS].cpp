#define EIGENLINEARSOLVERS_EIGENSPARSELU_CRS_CPP
#include <EigenLinearSolvers/EigenSparseQR[CRS].h>
#include <EigenLinearSolvers/EigenDirectSparseSolver[CRS].inl>

#include <sofa/core/ObjectFactory.h>

namespace EigenLinearSolvers
{
    template class SOFA_EIGENLINEARSOLVERS_API EigenSparseQR< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> >;
    template class SOFA_EIGENLINEARSOLVERS_API EigenSparseQR<
        sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
        sofa::linearalgebra::FullVector<SReal> >;

    int EigenSparseQRCRSClass = sofa::core::RegisterObject("Direct Linear Solver using a Sparse LDL^T factorization.")
    .add< EigenSparseQR< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> > >()
    .add< EigenSparseQR< sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >, sofa::linearalgebra::FullVector<SReal> > >()
    ;

}

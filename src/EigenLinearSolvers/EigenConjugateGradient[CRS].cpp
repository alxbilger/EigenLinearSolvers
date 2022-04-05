#define EIGENLINEARSOLVERS_EIGENCONJUGATEGRADIENT_CRS_CPP
#include <EigenLinearSolvers/EigenConjugateGradient[CRS].inl>
#include <sofa/component/linearsolver/iterative/MatrixLinearSolver.inl>
#include <sofa/core/ObjectFactory.h>

namespace EigenLinearSolvers
{

template class SOFA_EIGENLINEARSOLVERS_API EigenConjugateGradient< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> >;
template class SOFA_EIGENLINEARSOLVERS_API EigenConjugateGradient<
    sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
    sofa::linearalgebra::FullVector<SReal> >;

int EigenConjugateGradientCRSClass = sofa::core::RegisterObject("Linear system solver using the conjugate gradient iterative algorithm")
.add< EigenConjugateGradient< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> > >()
.add< EigenConjugateGradient< sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >, sofa::linearalgebra::FullVector<SReal> > >()
;

}


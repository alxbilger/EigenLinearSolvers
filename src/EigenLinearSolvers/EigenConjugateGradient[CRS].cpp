#define EIGENLINEARSOLVERS_EIGENCONJUGATEGRADIENT_CRS_CPP
#include <EigenLinearSolvers/EigenConjugateGradient[CRS].inl>
#include <sofa/component/linearsolver/iterative/MatrixLinearSolver.inl>
#include <sofa/core/ObjectFactory.h>

namespace EigenLinearSolvers
{
using sofa::linearalgebra::eigen::EigenVector;

template class SOFA_EIGENLINEARSOLVERS_API EigenConjugateGradient< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::eigen::EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > >;
template class SOFA_EIGENLINEARSOLVERS_API EigenConjugateGradient<
    sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
    sofa::linearalgebra::eigen::EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > >;

int EigenConjugateGradientCRSClass = sofa::core::RegisterObject("Linear system solver using the conjugate gradient iterative algorithm")
.add< EigenConjugateGradient< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::eigen::EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > > >()
.add< EigenConjugateGradient< sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >, EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > > >()
;

}


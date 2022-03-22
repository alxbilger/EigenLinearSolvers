#define EIGENLINEARSOLVERS_EIGENCONJUGATEGRADIENT_EIGEN_CPP
#include <EigenLinearSolvers/EigenConjugateGradient[Eigen].inl>

#include <sofa/core/ObjectFactory.h>

namespace EigenLinearSolvers
{
using sofa::linearalgebra::eigen::EigenMatrix;
using sofa::linearalgebra::eigen::EigenVector;

template class SOFA_EIGENLINEARSOLVERS_API EigenConjugateGradient< EigenMatrix<Eigen::SparseMatrix<SReal, Eigen::RowMajor> >, EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > >;


int EigenConjugateGradientEigenClass = sofa::core::RegisterObject("Linear system solver using the conjugate gradient iterative algorithm")
    .add< EigenConjugateGradient< EigenMatrix<Eigen::SparseMatrix<SReal, Eigen::RowMajor> >, EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > > >(true);

}

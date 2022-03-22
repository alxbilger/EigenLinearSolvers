#pragma once
#include <EigenLinearSolvers/config.h>

#include <EigenLinearSolvers/EigenSimplicialLDLT.h>
#include <sofa/component/linearsolver/iterative/MatrixLinearSolver.h>
#include <Eigen/SparseCore>

namespace EigenLinearSolvers
{

/**
 * Partial template specialization of EigenSimplicialLDLT for a matrix of type EigenMatrix
 */
template<class TEigenMatrix, class TEigenVector>
class EigenSimplicialLDLT<sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix>, sofa::linearalgebra::eigen::EigenVector<TEigenVector> >
    : public sofa::component::linearsolver::MatrixLinearSolver<
        sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix>, sofa::linearalgebra::eigen::EigenVector<TEigenVector> >
{
public:
    typedef sofa::linearalgebra::eigen::EigenMatrix<TEigenMatrix> Matrix;
    typedef sofa::linearalgebra::eigen::EigenVector<TEigenVector> Vector;

    SOFA_CLASS(SOFA_TEMPLATE2(EigenSimplicialLDLT, Matrix, Vector),SOFA_TEMPLATE2(sofa::component::linearsolver::MatrixLinearSolver, Matrix, Vector));

    using EigenSparseMatrix = typename Matrix::EigenType;

    void solve (Matrix& A, Vector& x, Vector& b) override;
    void invert(Matrix& A) override;

protected:
    Eigen::SimplicialLDLT<EigenSparseMatrix, Eigen::Lower> m_solver;

    bool m_analyzePattern { true };
};


#ifndef EIGENLINEARSOLVERS_EIGENEIGENSIMPLICIALLDLT_EIGEN_CPP
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT< sofa::linearalgebra::eigen::EigenMatrix<Eigen::SparseMatrix<SReal, Eigen::RowMajor> >, sofa::linearalgebra::eigen::EigenVector<Eigen::Matrix<SReal, Eigen::Dynamic, 1 > > >;
#endif

}

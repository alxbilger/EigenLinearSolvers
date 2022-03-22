#pragma once
#include <EigenLinearSolvers/config.h>
#include <sofa/core/objectmodel/BaseObject.h>

#include <Eigen/Sparse>
#include <sofa/helper/OptionsGroup.h>

namespace EigenLinearSolvers
{

/**
 * EigenConjugateGradient is a SOFA component allowing to solve a of linear equations. This is an essential component
 * in a SOFA simulation.
 *
 * The class is empty because it is partially specialized in other files.
 *
 * In all specializations, a linear solver from the Eigen library is used to solve the linear system.
 * In this class, the solver is Eigen::ConjugateGradient (https://eigen.tuxfamily.org/dox/classEigen_1_1ConjugateGradient.html)
 */
template<class TMatrix, class TVector>
class EigenConjugateGradient
{};

/**
 * A base class for all the spcializations of EigenConjugateGradient.
 * It contains the Data for the parameters for Eigen::ConjugateGradient. It also contains the linear solvers.
 * Multiple solvers are defined to be able to choose at run-time which preconditioner to use.
 */
template<class EigenSparseMatrix>
class EigenConjugateGradientImpl : virtual public sofa::core::objectmodel::BaseObject
{
public:
    using Scalar = typename EigenSparseMatrix::Scalar;
    SOFA_CLASS(EigenConjugateGradientImpl, sofa::core::objectmodel::BaseObject);

    sofa::Data<unsigned> d_maxIter; ///< maximum number of iterations of the Conjugate Gradient solution
    sofa::Data<SReal> d_tolerance; ///< desired precision of the Conjugate Gradient Solution (ratio of current residual norm over initial residual norm)
    sofa::Data<sofa::helper::OptionsGroup> d_preconditioner;

protected:

    EigenConjugateGradientImpl()
        : Inherit1()
        , d_maxIter(initData(&d_maxIter, 25u, "iterations","Maximum number of iterations of the Conjugate Gradient solution"))
        , d_tolerance(initData(&d_tolerance, (SReal)1e-5,"tolerance","Desired accuracy of the Conjugate Gradient solution evaluating: |r|²/|b|² (ratio of current residual norm over initial residual norm)"))
        , d_preconditioner(initData(&d_preconditioner, sofa::helper::OptionsGroup(3, "identity", "diagonal", "incompleteLUT"), "preconditioner", "The preconditioner used by this solver"))
    {
        sofa::helper::getWriteOnlyAccessor(d_preconditioner)->setSelectedItem(1);
    }

    Eigen::ConjugateGradient<EigenSparseMatrix, Eigen::Lower|Eigen::Upper, Eigen::IdentityPreconditioner> m_identityCG;
    Eigen::ConjugateGradient<EigenSparseMatrix, Eigen::Lower|Eigen::Upper, Eigen::IncompleteLUT<Scalar> > m_incompleteLUTCG;
    Eigen::ConjugateGradient<EigenSparseMatrix, Eigen::Lower|Eigen::Upper, Eigen::DiagonalPreconditioner<Scalar> > m_diagonalCG;

    unsigned int m_usedPreconditioner {};
};

}



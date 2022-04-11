#pragma once
#include <EigenLinearSolvers/config.h>

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

}



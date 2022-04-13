#pragma once

namespace EigenLinearSolvers
{

/**
 * EigenSparseQR is a SOFA component allowing to solve a set of linear equations. This is an essential component
 * in a SOFA simulation.
 *
 * The class is empty because it is partially specialized in other files.
 *
 * In all specializations, a linear solver from the Eigen library is used to solve the linear system.
 * In this class, the solver is Eigen::SparseLU (https://eigen.tuxfamily.org/dox/classEigen_1_1SparseQR.html)
 */
template<class TMatrix, class TVector>
class EigenSparseQR
{};

}

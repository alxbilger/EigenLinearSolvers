#pragma once
#include <EigenLinearSolvers/config.h>

#include <EigenLinearSolvers/EigenDirectSparseSolver.h>

#if __has_include(<sofa/component/linearsolver/iterative/MatrixLinearSolver.h>)
#include <sofa/component/linearsolver/iterative/MatrixLinearSolver.h>
#else
#include <SofaBaseLinearSolver/MatrixLinearSolver.h>
#endif

#include <variant>
#include <Eigen/SparseCore>

#include <sofa/helper/OptionsGroup.h>

namespace EigenLinearSolvers
{

/**
 * Partial template specialization of EigenDirectSparseSolver for a matrix of type CompressedRowSparseMatrix
 */
template<class TBlockType, class EigenSolver>
class EigenDirectSparseSolver<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
        sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>,
        EigenSolver >
    : public sofa::component::linearsolver::MatrixLinearSolver<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
        sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real> >
{
public:
    typedef sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType> Matrix;
    using Real = typename Matrix::Real;
    typedef sofa::linearalgebra::FullVector<Real> Vector;

    SOFA_ABSTRACT_CLASS(SOFA_TEMPLATE3(EigenDirectSparseSolver, Matrix, Vector, EigenSolver),
        SOFA_TEMPLATE2(sofa::component::linearsolver::MatrixLinearSolver, Matrix, Vector));

    using NaturalOrderSolver = typename EigenSolver::NaturalOrderSolver;
    using AMDOrderSolver     = typename EigenSolver::AMDOrderSolver;
    using COLAMDOrderSolver  = typename EigenSolver::COLAMDOrderSolver;


    ~EigenDirectSparseSolver() override = default;

    void init() override;
    void reinit() override;

    using EigenSparseMatrix = Eigen::SparseMatrix<Real, Eigen::RowMajor>;
    using EigenSparseMatrixMap = Eigen::Map<EigenSparseMatrix>;
    using EigenVectorXdMap = Eigen::Map<Eigen::Matrix<Real, Eigen::Dynamic, 1> >;

    void solve (Matrix& A, Vector& x, Vector& b) override;
    void invert(Matrix& A) override;

protected:

    sofa::core::objectmodel::Data<sofa::helper::OptionsGroup> d_orderingMethod;
    unsigned int m_selectedOrderingMethod;

    std::variant<NaturalOrderSolver, AMDOrderSolver, COLAMDOrderSolver> m_solver;

    Eigen::ComputationInfo getSolverInfo() const;
    void updateSolverOderingMethod();

    sofa::linearalgebra::CompressedRowSparseMatrix<Real> Mfiltered;
    std::unique_ptr<EigenSparseMatrixMap> m_map;

    typename sofa::linearalgebra::CompressedRowSparseMatrix<Real>::VecIndex MfilteredrowBegin;
    typename sofa::linearalgebra::CompressedRowSparseMatrix<Real>::VecIndex MfilteredcolsIndex;

    EigenDirectSparseSolver();
};

}

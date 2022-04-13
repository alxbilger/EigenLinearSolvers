#pragma once
#include <EigenLinearSolvers/config.h>

#include <EigenLinearSolvers/EigenSparseLU.h>
#include <EigenLinearSolvers/EigenDirectSparseSolver[CRS].h>
#include <EigenLinearSolvers/SparseLUTraits.h>

namespace EigenLinearSolvers
{

/**
 * Partial template specialization of EigenSparseLU for a matrix of type CompressedRowSparseMatrix
 */
template<class TBlockType>
class EigenSparseLU<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
        sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real> >
    : public EigenDirectSparseSolver<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
        sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>,
        SparseLUTraits<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>
    >
{
public:
    typedef sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType> Matrix;
    using Real = typename Matrix::Real;
    typedef sofa::linearalgebra::FullVector<Real> Vector;

    SOFA_CLASS(SOFA_TEMPLATE2(EigenSparseLU, Matrix, Vector), SOFA_TEMPLATE3(EigenDirectSparseSolver, Matrix, Vector, SparseLUTraits<Real>));

};

#ifndef EIGENLINEARSOLVERS_EIGENSPARSELU_CRS_CPP
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSparseLU< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> >;
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSparseLU<
        sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
        sofa::linearalgebra::FullVector<SReal> >;
#endif

}

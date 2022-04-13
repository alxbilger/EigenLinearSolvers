#pragma once
#include <EigenLinearSolvers/config.h>

#include <EigenLinearSolvers/EigenSimplicialLLT.h>
#include <EigenLinearSolvers/EigenDirectSparseSolver[CRS].h>
#include <EigenLinearSolvers/SimplicialLLTTraits.h>

namespace EigenLinearSolvers
{

/**
 * Partial template specialization of EigenSimplicialLLT for a matrix of type CompressedRowSparseMatrix
 */
template<class TBlockType>
class EigenSimplicialLLT<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
        sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real> >
    : public EigenDirectSparseSolver<
        sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>,
        sofa::linearalgebra::FullVector<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>,
        SimplicialLLTTraits<typename sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType>::Real>
    >
{
public:
    typedef sofa::linearalgebra::CompressedRowSparseMatrix<TBlockType> Matrix;
    using Real = typename Matrix::Real;
    typedef sofa::linearalgebra::FullVector<Real> Vector;

    SOFA_CLASS(SOFA_TEMPLATE2(EigenSimplicialLLT, Matrix, Vector), SOFA_TEMPLATE3(EigenDirectSparseSolver, Matrix, Vector, SimplicialLLTTraits<Real>));

};

#ifndef EIGENLINEARSOLVERS_EIGENEIGENSIMPLICIALLLT_CRS_CPP
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLLT< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> >;
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLLT<
        sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
        sofa::linearalgebra::FullVector<SReal> >;
#endif

}

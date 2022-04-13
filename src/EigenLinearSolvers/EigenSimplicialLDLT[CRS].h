#pragma once
#include <EigenLinearSolvers/config.h>

#include <EigenLinearSolvers/EigenSimplicialLDLT.h>
#include <EigenLinearSolvers/EigenDirectSparseSolver[CRS].h>
#include <EigenLinearSolvers/SimplicialLLTTraits.h>

namespace EigenLinearSolvers
{

/**
 * Partial template specialization of EigenSimplicialLDLT for a matrix of type CompressedRowSparseMatrix
 */
template<class TBlockType>
class EigenSimplicialLDLT<
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

    SOFA_CLASS(SOFA_TEMPLATE2(EigenSimplicialLDLT, Matrix, Vector),SOFA_TEMPLATE3(EigenDirectSparseSolver, Matrix, Vector, SimplicialLLTTraits<Real>));

};

#ifndef EIGENLINEARSOLVERS_EIGENEIGENSIMPLICIALLDLT_CRS_CPP
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT< sofa::linearalgebra::CompressedRowSparseMatrix<SReal>, sofa::linearalgebra::FullVector<SReal> >;
    extern template class SOFA_EIGENLINEARSOLVERS_API EigenSimplicialLDLT<
        sofa::linearalgebra::CompressedRowSparseMatrix< sofa::type::Mat<3,3,SReal> >,
        sofa::linearalgebra::FullVector<SReal> >;
#endif

}

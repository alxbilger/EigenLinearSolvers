# EigenLinearSolvers
SOFA plugin wrapping the Eigen linear solvers into SOFA components

## Components

### EigenConjugateGradient

This linear solver component is based on `Eigen::ConjugateGradient` (https://eigen.tuxfamily.org/dox/classEigen_1_1ConjugateGradient.html).
Its equivalent in SOFA is `CGLinearSolver`.

The available templates are:
- EigenSparseMatrixd
- CompressedRowSparseMatrixMat3x3d
- CompressedRowSparseMatrixd

### EigenSimplicialLDLT

This linear solver component is based on `Eigen::SimplicialLDLT` (https://eigen.tuxfamily.org/dox/classEigen_1_1SimplicialLDLT.html).
Its equivalent in SOFA is `SparseLDLSolver`.

The available templates are:
- EigenSparseMatrixd
- CompressedRowSparseMatrixMat3x3d
- CompressedRowSparseMatrixd

## Choice of the template

EigenConjugateGradient and EigenSimplicialLDLT can have the choice of a template based on an Eigen sparse matrix, or a SOFA type CompressedRowSparseMatrix.
Both templates have different approaches and can have an impact on the performances.
If possible, the use of `CompressedRowSparseMatrixMat3x3d` is preferable as it brings significant speed up of the matrix assembly.

## Performances

The following measures are given on a indicative basis.

### FEMBAR_EigenSimplicialLDLT.scn

Both solvers have been templated with `CompressedRowSparseMatrixMat3x3d`.
The measurements were made without GUI, running 1000 time steps.

| Measure               | SparseLDLSolver | EigenSimplicialLDLT |
|-----------------------|-----------------|---------------------|
| total (s)             | 3.79887         | 2.45837             |
| total (FPS)           | 263.236         | 406.774             |
| MBKBuild (average ms) | 0.53            | 0.52                |
| MBKSolve (average ms) | 3.07            | 1.74                |

### Cylinder_EigenSimplicialLDLT.scn

Both solvers have been templated with `CompressedRowSparseMatrixMat3x3d`.
The measurements were made without GUI, running 1000 time steps.

| Measure               | SparseLDLSolver | EigenSimplicialLDLT |
|-----------------------|-----------------|---------------------|
| total (s)             | 13.3605         | 10.5815             |
| total (FPS)           | 74.8476         | 94.5048             |
| MBKBuild (average ms) | 5.79            | 5.84                |
| MBKSolve (average ms) | 7.02            | 4.16                |



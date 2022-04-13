#pragma once
#include <EigenLinearSolvers/config.h>

namespace EigenLinearSolvers
{

template<class TMatrix, class TVector, class EigenSolver>
class EigenDirectSparseSolver
{
public:
    virtual ~EigenDirectSparseSolver() = default;
};

}

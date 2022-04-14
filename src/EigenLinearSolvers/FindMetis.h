#pragma once

#if __has_include("metis.h")
#define EIGENLINEARSOLVERS_HAS_METIS_INCLUDE 1
#include <Eigen/MetisSupport>
#else
#define EIGENLINEARSOLVERS_HAS_METIS_INCLUDE 0
#warning "metis.h cannot be included: the ordering method based on metis will not be available"
#endif


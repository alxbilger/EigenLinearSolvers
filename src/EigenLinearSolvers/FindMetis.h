#pragma once

/**
 * It seems that some binary versions of SOFA do not ship the metis.h include file.
 * See https://github.com/sofa-framework/sofa/issues/2866
 * Therefore, metis cannot be supported.
 */
#if __has_include("metis.h")
#define EIGENLINEARSOLVERS_HAS_METIS_INCLUDE 1
#include <Eigen/MetisSupport>
#else
#define EIGENLINEARSOLVERS_HAS_METIS_INCLUDE 0
#endif


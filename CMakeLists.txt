cmake_minimum_required(VERSION 3.12)
project(EigenLinearSolvers VERSION 1.0 LANGUAGES CXX)

find_package(SofaFramework REQUIRED)
find_package(Sofa.Component.LinearSolver.Direct QUIET)
if (NOT Sofa.Component.LinearSolver.Direct_FOUND)
    find_package(SofaSparseSolver QUIET)
endif()

# List all files
set(EIGENLINEARSOLVERS_SRC_DIR src/${PROJECT_NAME})
set(HEADER_FILES
    ${EIGENLINEARSOLVERS_SRC_DIR}/config.h.in

    ${EIGENLINEARSOLVERS_SRC_DIR}/SimplicialLDLTTraits.h
    ${EIGENLINEARSOLVERS_SRC_DIR}/SimplicialLLTTraits.h
    ${EIGENLINEARSOLVERS_SRC_DIR}/SparseLUTraits.h
    ${EIGENLINEARSOLVERS_SRC_DIR}/SparseQRTraits.h

    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenConjugateGradient.h
    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenConjugateGradient[CRS].h
    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenConjugateGradient[CRS].inl

    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenDirectSparseSolver.h
    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenDirectSparseSolver[CRS].h
    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenDirectSparseSolver[CRS].inl

    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenSimplicialLDLT.h
    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenSimplicialLDLT[CRS].h

    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenSimplicialLLT.h
    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenSimplicialLLT[CRS].h

    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenSparseLU.h
    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenSparseLU[CRS].h

    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenSparseQR.h
    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenSparseQR[CRS].h
)
set(SOURCE_FILES
    ${EIGENLINEARSOLVERS_SRC_DIR}/init.cpp

    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenConjugateGradient[CRS].cpp
    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenSimplicialLDLT[CRS].cpp
    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenSimplicialLLT[CRS].cpp
    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenSparseLU[CRS].cpp
    ${EIGENLINEARSOLVERS_SRC_DIR}/EigenSparseQR[CRS].cpp
)
set(README_FILES
    README.md
)

# Create the plugin library.
add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${README_FILES})

# Link the plugin library to its dependency(ies).
if (Sofa.Component.LinearSolver.Direct_FOUND)
    target_link_libraries(${PROJECT_NAME} Sofa.Component.LinearSolver.Direct)
elseif(SofaSparseSolver_FOUND)
    target_link_libraries(${PROJECT_NAME} SofaSparseSolver)
endif()

# Create package Config, Version & Target files.
# Deploy the headers, resources, scenes & examples.
# Set the plugin 'relocatable' if built within SOFA.
# --> see SofaMacros.cmake
sofa_create_package_with_targets(
    PACKAGE_NAME ${PROJECT_NAME}
    PACKAGE_VERSION ${PROJECT_VERSION}
    TARGETS ${PROJECT_NAME} AUTO_SET_TARGET_PROPERTIES
    INCLUDE_SOURCE_DIR "src"
    INCLUDE_INSTALL_DIR ${PROJECT_NAME}
    RELOCATABLE "plugins"
)

# Tests
# If SOFA_BUILD_TESTS exists and is OFF, then these tests will be auto-disabled
# cmake_dependent_option(EIGENLINEARSOLVERS_BUILD_TESTS "Compile the automatic tests" ON "SOFA_BUILD_TESTS OR NOT DEFINED SOFA_BUILD_TESTS" OFF)
# if(EIGENLINEARSOLVERS_BUILD_TESTS)
#     enable_testing()
#     add_subdirectory(EigenLinearSolvers_test)
# endif()

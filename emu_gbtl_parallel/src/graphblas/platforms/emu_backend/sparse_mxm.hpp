/* Copyright[2019] Copyright Owner <>
 * forked from GraphBLAS Template Library, Version 2.0
 * Copyright Pending - Will be updated soon.
 */

#ifndef GB_SEQUENTIAL_SPARSE_MXM_HPP
#define GB_SEQUENTIAL_SPARSE_MXM_HPP

#pragma once

#include <functional>
#include <utility>
#include <vector>
#include <iterator>
#include <iostream>
#include <tuple>
#include <graphblas/types.hpp>
#include <graphblas/algebra.hpp>

#include "sparse_helpers.hpp"
#include "LilSparseMatrix.hpp"
#include "cilk.h"

//****************************************************************************

namespace GraphBLAS {
namespace backend {

//**********************************************************************
/// Implementation of 4.3.1 mxm: Matrix-matrix multiply
template<typename CMatrixT,
         typename MMatrixT,
         typename AccumT,
         typename SemiringT,
         typename AMatrixT,
         typename BMatrixT>
inline Info mxm(CMatrixT            &C,
                MMatrixT    const   &M,
                AccumT      const   &accum,
                SemiringT            op,
                AMatrixT    const   &A,
                BMatrixT    const   &B,
                bool                 replace_flag = false) {
  // Dimension checks happen in front end
  IndexType nrow_A(A.nrows());
  IndexType ncol_B(B.ncols());
  // Frontend checks the dimensions, but use C explicitly
  IndexType nrow_C(C.nrows());
  IndexType ncol_C(C.ncols());

  typedef typename SemiringT::result_type D3ScalarType;
  typedef typename AMatrixT::ScalarType AScalarType;
  typedef typename BMatrixT::ScalarType BScalarType;
  typedef typename CMatrixT::ScalarType CScalarType;
  typedef std::vector<std::tuple<IndexType, CScalarType>> CColType;
  typedef std::vector<std::tuple<IndexType, D3ScalarType>> TColType;

  // =================================================================
  // Do the basic dot-product work with the semi-ring.
#ifdef DEBUG
  std::cout << "DEBUG: BEGIN compute T \n " << std::endl
            << "The below debug message will be in out of order"
            << " due to multithreading \n" << std::endl;
#endif

  LilSparseMatrix<D3ScalarType> T(nrow_A, ncol_B);
  // Build this completely based on the semiring
  if ((A.nvals() > 0) && (B.nvals() > 0)) {
    // create a row of result at a time
    TColType T_row;

    for (IndexType row_idx = 0; row_idx < nrow_A; ++row_idx) {
      typename AMatrixT::RowType A_row(A.getRow(row_idx));

      if (!A_row.empty()) {
        D3ScalarType T_val[ncol_B];
        memset(T_val, 0, ncol_B * sizeof(D3ScalarType));

        for (IndexType col_idx = 0; col_idx < ncol_B; ++col_idx) {
          typename BMatrixT::ColType B_col(B.getCol(col_idx));

          if (!B_col.empty()) {
#ifdef DEBUG
            std::cout << std:: endl
                      << "Dot Operation Started :"
                      << " RowID = " << row_idx
                      << " ColID = " << col_idx
                      << std::endl;
#endif
            // cilk_spawn_at(&A_row) dot(T_val, A_row, B_col, op, col_idx);
            cilk_spawn dot(T_val, A_row, B_col, op, col_idx);
          }
        }  // End of col_idx for loop
        cilk_sync;

#ifdef DEBUG
        std::cout << std::endl
                  << "Completed 1 entire row of dot product operation"
                  << std::endl << "Printing T_row array "
                  << '\t';
#endif

        for (IndexType col_idx = 0; col_idx < ncol_B; ++col_idx) {
          if (T_val[col_idx] != 0) {
#ifdef DEBUG
            std::cout << T_val[col_idx] << " ";
#endif
            T_row.push_back(std::make_tuple(col_idx, T_val[col_idx]));
          }
        }
        
        if (!T_row.empty()) {
#ifdef DEBUG
          std::cout << std:: endl
                    << "Pushing each T_row vector back to the big T Lil storage"
                    << std:: endl;
#endif
          T.setRow(row_idx, T_row);
          T_row.clear();
        }
      }
    }  // End of row_idx for loop
  }

#ifdef DEBUG
  T.printInfo(std::cout, "END compute T");
  // =================================================================
  // Accumulate into Z
  std::cout << "DEBUG: BEGIN compute Z" << std::endl;
#endif

  typedef typename std::conditional<
    std::is_same<AccumT, NoAccumulate>::value,
    D3ScalarType,
    typename AccumT::result_type>::type ZScalarType;
  LilSparseMatrix<ZScalarType> Z(nrow_C, ncol_C);

#ifdef DEBUG
  T.printInfo(std::cout, "(again) T");
#endif

  ewise_or_opt_accum(Z, C, T, accum);

#ifdef DEBUG
  Z.printInfo(std::cout, "END compute Z");
  // =================================================================
  // Copy Z into the final output considering mask and replace
  std::cout << "DEBUG: BEGIN compute C" << std::endl;
#endif

  write_with_opt_mask(C, Z, M, replace_flag);

#ifdef DEBUG
  C.printInfo(std::cout, "END compute C");
#endif

  return SUCCESS;
}  // end mxm
}  // end namespace backend
}  // end namespace GraphBLAS

#endif

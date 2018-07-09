/*
 * Copyright (c) 2015 Carnegie Mellon University and The Trustees of Indiana
 * University.
 * All Rights Reserved.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS," WITH NO WARRANTIES WHATSOEVER. CARNEGIE
 * MELLON UNIVERSITY AND THE TRUSTEES OF INDIANA UNIVERSITY EXPRESSLY DISCLAIM
 * TO THE FULLEST EXTENT PERMITTED BY LAW ALL EXPRESS, IMPLIED, AND STATUTORY
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT OF PROPRIETARY RIGHTS.
 *
 * This Program is distributed under a BSD license.  Please see LICENSE file or
 * permission@sei.cmu.edu for more information.  DM-0002659
 */

#ifndef GB_OPERATIONS_HPP
#define GB_OPERATIONS_HPP

#pragma once

#include <cstddef>
#include <vector>

#include <graphblas/algebra.hpp>
#include <graphblas/Matrix.hpp>
#include <graphblas/detail/logging.h>
#include <graphblas/detail/config.hpp>

//#include <graphblas/detail/checks.hpp>
//#include <graphblas/indices.hpp>

#define GB_INCLUDE_BACKEND_TRANSPOSE_VIEW 1
#define GB_INCLUDE_BACKEND_COMPLEMENT_VIEW 1
#define GB_INCLUDE_BACKEND_OPERATIONS 1

#include <backend_include.hpp>

//****************************************************************************
// New signatures to conform to GraphBLAS Specification
//****************************************************************************

namespace GraphBLAS
{
    //************************************************************************
    // mxm, vxm, mxv
    //************************************************************************

    // 4.3.1: Matrix-matrix multiply
    template<typename CMatrixT,
             typename MaskT,
             typename AccumT,
             typename SemiringT,
             typename AMatrixT,
             typename BMatrixT>
    inline void mxm(CMatrixT         &C,
                    MaskT      const &Mask,
                    AccumT            accum,
                    SemiringT         op,
                    AMatrixT   const &A,
                    BMatrixT   const &B,
                    bool              replace_flag = false)
    {
        GRB_LOG_FN_BEGIN("mxm - 4.3.1 - matrix-matrix multiply");
        GRB_LOG_VERBOSE("C in :" << C.m_mat);
        GRB_LOG_VERBOSE("Mask in : " << Mask.m_mat);
        GRB_LOG_VERBOSE_ACCUM(accum);
        GRB_LOG_VERBOSE_OP(op);
        GRB_LOG_VERBOSE("A in :" << A.m_mat);
        GRB_LOG_VERBOSE("B in :" << B.m_mat);
        GRB_LOG_VERBOSE_REPLACE(replace_flag);

 /*       check_nrows_nrows(C, Mask, "mxm: C.nrows != Mask.nrows");
        check_ncols_ncols(C, Mask, "mxm: C.ncols != Mask.ncols");
        check_nrows_nrows(C, A, "mxm: C.nrows != A.nrows");
        check_ncols_ncols(C, B, "mxm: C.ncols != B.ncols");
        check_ncols_nrows(A, B, "mxm: A.ncols != B.nrows");
*/
        backend::mxm(C.m_mat, Mask.m_mat, accum, op, A.m_mat, B.m_mat,
                     replace_flag);

        GRB_LOG_VERBOSE("C (Result): " << C.m_mat);
        GRB_LOG_FN_END("mxm - 4.3.1 - matrix-matrix multiply");
    }




    // 4.3.9.3: reduce - matrix-scalar variant
    /// @note We aren't supporting transpose of matrix here. The spec does not
    /// require support.
    template<typename ValueT,
             typename AccumT,
             typename MonoidT, // monoid only
             typename AScalarT,
             typename ...ATagsT>
    inline void reduce(
            ValueT                            &val,
            AccumT                             accum,
            MonoidT                            op,
            Matrix<AScalarT, ATagsT...> const &A)
    {
        GRB_LOG_FN_BEGIN("reduce - 4.3.9.3 - matrix to scalar variant");
        GRB_LOG_VERBOSE("val in: " << val);
        GRB_LOG_VERBOSE_ACCUM(accum);
        GRB_LOG_VERBOSE_OP(op);
        GRB_LOG_VERBOSE("A in: " << A.m_mat);

        backend::reduce_matrix_to_scalar(val, accum, op, A.m_mat);

        GRB_LOG_VERBOSE("val out: " << val);
        GRB_LOG_FN_END("reduce - 4.3.9.3 - matrix to scalar variant");
    }




 } // GraphBLAS


#endif

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

/**
 * Implementations of all GraphBLAS functions optimized for the sequential
 * (CPU) backend.
 */

#ifndef GB_SEQUENTIAL_OPERATIONS_HPP
#define GB_SEQUENTIAL_OPERATIONS_HPP

#pragma once

#include <functional>
#include <utility>
#include <vector>
#include <iterator>

#include <graphblas/algebra.hpp>
// Add individual operation files here
#include <graphblas/platforms/emu_backend/sparse_mxm.hpp>
#include <graphblas/platforms/emu_backend/sparse_reduce.hpp>

/*
#include <graphblas/platforms/sequential/TransposeView.hpp>
#include <graphblas/platforms/sequential/ComplementView.hpp>
#include <graphblas/platforms/sequential/sparse_mxv.hpp>
#include <graphblas/platforms/sequential/sparse_vxm.hpp>
#include <graphblas/platforms/sequential/sparse_ewisemult.hpp>
#include <graphblas/platforms/sequential/sparse_ewiseadd.hpp>
#include <graphblas/platforms/sequential/sparse_extract.hpp>
#include <graphblas/platforms/sequential/sparse_assign.hpp>
#include <graphblas/platforms/sequential/sparse_apply.hpp>
#include <graphblas/platforms/sequential/sparse_transpose.hpp>
*/


namespace GraphBLAS
{
    namespace backend
    {
       
        template<typename MatrixT>
        inline MatrixComplementView<MatrixT> matrix_complement(MatrixT const &Mask)
        {
            return MatrixComplementView<MatrixT>(Mask);
        }
#if 0
        template<typename VectorT>
        inline VectorComplementView<VectorT> vector_complement(VectorT const &mask)
        {
            return VectorComplementView<VectorT>(mask);
        }
#endif

        template<typename MatrixT>
        inline TransposeView<MatrixT> transpose(MatrixT const &A)
        {
            return TransposeView<MatrixT>(A);
        }

    } // backend
} // GraphBLAS

#endif // GB_SEQUENTIAL_OPERATIONS_HPP

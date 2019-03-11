#ifndef GB_SEQUENTIAL_OPERATIONS_HPP

#define GB_SEQUENTIAL_OPERATIONS_HPP
#pragma once
#include <functional>
#include <utility>
#include <vector>
#include <iterator>
#include <graphblas/algebra.hpp>
#include <graphblas/platforms/emu_backend/sparse_mxm.hpp>
#include <graphblas/platforms/emu_backend/sparse_reduce.hpp>
#include <graphblas/platforms/emu_backend/sparse_transpose.hpp>


namespace GraphBLAS
{
    namespace backend
    {

        template<typename MatrixT>
        inline TransposeView<MatrixT> transpose(MatrixT const &A)
        {
            return TransposeView<MatrixT>(A);
        }

    }  // end namespace backend
}  // end namespace GraphBLAS

#endif  // GB_SEQUENTIAL_OPERATIONS_HPP

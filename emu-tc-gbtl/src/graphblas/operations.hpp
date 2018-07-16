#ifndef GB_OPERATIONS_HPP
#define GB_OPERATIONS_HPP

#pragma once

#include <cstddef>
#include <vector>

#include <graphblas/algebra.hpp>
#include <graphblas/Matrix.hpp>

#define GB_INCLUDE_BACKEND_OPERATIONS 1

#include <backend_include.hpp>

namespace GraphBLAS
{
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
				backend::mxm(C.m_mat, Mask.m_mat, accum, op, A.m_mat, B.m_mat,
						replace_flag);

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
				backend::reduce_matrix_to_scalar(val, accum, op, A.m_mat);
			}


} // GraphBLAS


#endif

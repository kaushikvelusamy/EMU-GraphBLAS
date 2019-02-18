#ifndef GB_SEQUENTIAL_SPARSE_MXM_HPP
#define GB_SEQUENTIAL_SPARSE_MXM_HPP

#pragma once

#include <functional>
#include <utility>
#include <vector>
#include <iterator>
#include <iostream>
#include <chrono>

#include <graphblas/types.hpp>
#include <graphblas/algebra.hpp>

#include "sparse_helpers.hpp"
#include "LilSparseMatrix.hpp"


//****************************************************************************

namespace GraphBLAS
{
    namespace backend
    {
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
                        bool                 replace_flag = false)
        {
            // Dimension checks happen in front end
            IndexType nrow_A(A.nrows());
            IndexType ncol_B(B.ncols());
            //Frontend checks the dimensions, but use C explicitly
            IndexType nrow_C(C.nrows());
            IndexType ncol_C(C.ncols());

            typedef typename SemiringT::result_type D3ScalarType;
            typedef typename AMatrixT::ScalarType AScalarType;
            typedef typename BMatrixT::ScalarType BScalarType;
            typedef typename CMatrixT::ScalarType CScalarType;
            typedef std::vector<std::tuple<IndexType,CScalarType> > CColType;
            typedef std::vector<std::tuple<IndexType,D3ScalarType> > TColType;

            // =================================================================
            // Do the basic dot-product work with the semi-ring.
#ifdef DEBUG
            std::cout << "DEBUG: BEGIN compute T" << std::endl;
#endif
            LilSparseMatrix<D3ScalarType> T(nrow_A, ncol_B);

            // Build this completely based on the semiring
            if ((A.nvals() > 0) && (B.nvals() > 0))
            {
                // create a column of result at a time
                TColType T_col;
                for (IndexType col_idx = 0; col_idx < ncol_B; ++col_idx)
                {
                    typename BMatrixT::ColType B_col(B.getCol(col_idx));

                    if (!B_col.empty())
                    {
                        for (IndexType row_idx = 0; row_idx < nrow_A; ++row_idx)
                        {
                            typename AMatrixT::RowType A_row(A.getRow(row_idx));
                            if (!A_row.empty())
                            {
#ifdef DEBUG
                              std::cout << std:: endl << std:: endl <<" Operation Started";
#endif
                                D3ScalarType T_val;
                                if (dot(T_val, A_row, B_col, op))
                                {
#ifdef DEBUG
                                   std::cout << std:: endl <<"Pushing back to TCOL" << std:: endl ;
#endif
                                    T_col.push_back(
                                            std::make_tuple(row_idx, T_val));
                                }
                            }
                        }
#ifdef DEBUG
                        std::cout << std:: endl <<"end of row" << std:: endl ;
#endif
                        if (!T_col.empty())
                        {
#ifdef DEBUG
                            std::cout << std:: endl <<"Pushing back to T" << std:: endl ;
#endif
                            T.setCol(col_idx, T_col);
                            T_col.clear();
                        }
                    }
                }
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
        } // mxm
    } // backend
} // GraphBLAS

#endif

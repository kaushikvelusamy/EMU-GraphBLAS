#ifndef ALGORITHMS_TRIANGLE_COUNT_HPP
#define ALGORITHMS_TRIANGLE_COUNT_HPP

#include <iostream>
#include <chrono>

#include <graphblas/graphblas.hpp>

namespace algorithms

{
    template<typename MatrixT>
    typename MatrixT::ScalarType triangle_count_masked_v2(MatrixT const &L,
                                                          MatrixT const &U)
    {
        using T = typename MatrixT::ScalarType;
        GraphBLAS::IndexType rows(L.nrows());
        GraphBLAS::IndexType cols(L.ncols());

        MatrixT B(rows, cols);
        GraphBLAS::mxm(B,
                       L, GraphBLAS::NoAccumulate(),
                       GraphBLAS::ArithmeticSemiring<T>(),
                       L, U);

        T sum = 0;
        GraphBLAS::reduce(sum,
                          GraphBLAS::NoAccumulate(),
                          GraphBLAS::PlusMonoid<T>(),
                          B);
        return sum;
    }

  } // algorithms

#endif // ALGORITHMS_TRIANGLE_COUNT_HPP

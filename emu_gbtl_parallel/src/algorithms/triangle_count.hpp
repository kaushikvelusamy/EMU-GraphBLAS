#ifndef ALGORITHMS_TRIANGLE_COUNT_HPP
#define ALGORITHMS_TRIANGLE_COUNT_HPP

#include <iostream>
#include <chrono>

#include <graphblas/graphblas.hpp>


namespace algorithms

{
    template<typename MatrixT>
    typename MatrixT::ScalarType triangle_count_masked(MatrixT const &L)
    {
        using T = typename MatrixT::ScalarType;
        GraphBLAS::IndexType rows(L.nrows());
        GraphBLAS::IndexType cols(L.ncols());
#ifdef DEBUG
        std::cout << "DEBUG: allocating temporary matrix." << std::endl;
#endif
        MatrixT B(rows, cols);
#ifdef DEBUG
        std::cout << "DEBUG: before mxm function"<< std::endl;
#endif

#ifdef SIMULATOR
	starttiming();
#endif

        GraphBLAS::mxm(B,
                       L, GraphBLAS::NoAccumulate(),
                       GraphBLAS::ArithmeticSemiring<T>(),
                       L, GraphBLAS::transpose(L));
#ifdef DEBUG
        std::cout << "DEBUG: before reduce function"<< std::endl;
#endif
        T sum = 0;
        GraphBLAS::reduce(sum,
                          GraphBLAS::NoAccumulate(),
                          GraphBLAS::PlusMonoid<T>(),
                          B);
        return sum;
    }
} // algorithms

#endif // ALGORITHMS_TRIANGLE_COUNT_HPP

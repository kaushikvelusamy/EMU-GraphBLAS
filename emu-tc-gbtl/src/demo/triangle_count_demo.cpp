
#include "memoryweb.h"
#include <iostream>
#include <fstream>
#include <chrono>

#include <graphblas/graphblas.hpp>
#include <algorithms/triangle_count.hpp>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "ERROR: too few arguments." << std::endl;
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(1);
    }

    // Read the edgelist and create the tuple arrays
    std::string pathname(argv[1]);
    std::ifstream infile(pathname);
    GraphBLAS::IndexArrayType iL, iU;
    GraphBLAS::IndexArrayType jL, jU;
    int64_t num_rows = 0;
    int64_t max_id = 0;
    uint64_t src, dst;

    while (infile)
    {
        infile >> src >> dst;
        //std::cout << "Read: " << src << ", " << dst << std::endl;
        if (src > max_id) max_id = src;
        if (dst > max_id) max_id = dst;

        if (src < dst)
        {
            iU.push_back(src);
            jU.push_back(dst);
        }
        else if (dst < src)
        {
            iL.push_back(src);
            jL.push_back(dst);
        }
        // else ignore self loops

        ++num_rows;
    }
    std::cout << "Read " << num_rows << " rows." << std::endl;
    std::cout << "#Nodes = " << (max_id + 1) << std::endl;

    GraphBLAS::IndexType NUM_NODES(max_id + 1);
    typedef int32_t T;
    std::vector<T> vL(iL.size(), 1);
    std::vector<T> vU(iU.size(), 1);


    /// @todo change scalar type to unsigned int or GraphBLAS::IndexType
    typedef GraphBLAS::Matrix<T, GraphBLAS::DirectedMatrixTag> MatType;

    MatType L(NUM_NODES, NUM_NODES);
    MatType U(NUM_NODES, NUM_NODES);

    L.build(iL.begin(), jL.begin(), vL.begin(), iL.size());
    U.build(iU.begin(), jU.begin(), vU.begin(), iU.size());

    std::cout << "Running algorithm(s)..." << std::endl;
    T count(0);

    auto start = std::chrono::steady_clock::now();

    // Perform triangle counting with three different algorithms
    count = algorithms::triangle_count_masked_v2(L, U);

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::steady_clock::now() - start);

    std::cout << "# triangles = " << count << std::endl;
    std::cout << "Elapsed time: " << duration.count() << " msec." << std::endl;

    return 0;
}

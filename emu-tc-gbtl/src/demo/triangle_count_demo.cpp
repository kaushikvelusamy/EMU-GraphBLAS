#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>


#include <graphblas/graphblas.hpp>
#include <algorithms/triangle_count.hpp>

using namespace std;

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "ERROR: too few arguments." << std::endl;
		std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
		exit(1);
	}

	// Read the edgelist and create the tuple arrays
	GraphBLAS::IndexArrayType iL, iU, iA;
	GraphBLAS::IndexArrayType jL, jU, jA;
	int64_t num_rows = 0;
	int64_t max_id = 0;
	uint64_t src, dst;

	GraphBLAS::IndexArrayType :: iterator i;



	FILE *infile = fopen(argv[1], "r");
	if (!infile)
	{
		fprintf(stderr, "Unable to open file: %s\n", argv[1]);
		exit(1);
	}

	while ( fscanf(infile, "%ld %ld", &src, &dst) == 2)
	{
		printf("Read: %ld, %ld\n", src, dst);
		if (src > max_id) max_id = src;
		if (dst > max_id) max_id = dst;

		if (src < dst)
		{
			iA.push_back(src);
			jA.push_back(dst);

			iU.push_back(src);
			jU.push_back(dst);
		}
		else if (dst < src)
		{
			iA.push_back(src);
			jA.push_back(dst);

			iL.push_back(src);
			jL.push_back(dst);
		}
		// else ignore self loops

		++num_rows;
	}
	fclose(infile);
	std::cout << "Read " << num_rows << " rows." << std::endl;
	std::cout << "#Nodes = " << (max_id + 1) << std::endl;

	std::cout <<"iA Vector";
	for (i = iA.begin(); i != iA.end(); ++i)
		std::cout <<*i << '\t';
	std::cout<<std::endl;


	std::cout <<"jA Vector";
	for (i = jA.begin(); i != jA.end(); ++i)
		std::cout << *i << '\t';
	std::cout<<std::endl;


	std::cout <<"iU Vector";
	for (i = iU.begin(); i != iU.end(); ++i)
		std::cout <<*i << '\t';
	std::cout<<std::endl;


	std::cout <<"jU Vector";
	for (i = jU.begin(); i != jU.end(); ++i)
		std::cout <<*i << '\t';
	std::cout<<std::endl;


	std::cout <<"iL Vector";
	for (i = iL.begin(); i != iL.end(); ++i)
		std::cout <<*i << '\t';
	std::cout<<std::endl;


	std::cout <<"jL Vector";
	for (i = jL.begin(); i != jL.end(); ++i)
		std::cout <<*i << '\t';
	std::cout<<std::endl;


	GraphBLAS::IndexType NUM_NODES(max_id + 1);
	typedef int32_t T;
	std::vector<T> v(iA.size(), 1);

	/// @todo change scalar type to unsigned int or GraphBLAS::IndexType
	typedef GraphBLAS::Matrix<T, GraphBLAS::DirectedMatrixTag> MatType;

	MatType A(NUM_NODES, NUM_NODES);
	MatType L(NUM_NODES, NUM_NODES);
	MatType U(NUM_NODES, NUM_NODES);

	//	A.build(iA.begin(), jA.begin(), v.begin(), iA.size());
	L.build(iL.begin(), jL.begin(), v.begin(), iL.size());
	//	U.build(iU.begin(), jU.begin(), v.begin(), iU.size());

	std::cout << "Running algorithm(s)..." << std::endl;
	T count(0);

	auto start = std::chrono::steady_clock::now();

	//	count = algorithms::triangle_count_newGBTL(L, U);

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::steady_clock::now() - start);

	/* std::cout << "# triangles = " << count << std::endl;
	   std::cout << "Elapsed time: " << duration.count() << " msec." << std::endl;
	 */

	start = std::chrono::steady_clock::now();

	count = algorithms::triangle_count_masked(L);

	duration = std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::steady_clock::now() - start);
	std::cout << "# triangles (masked) = " << count << std::endl;
	std::cout << "Elapsed time: " << duration.count() << " msec." << std::endl;

	return 0;
}

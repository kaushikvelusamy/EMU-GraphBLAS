#include <iostream>
#include "emu_matrix_datastructure.hpp"
#include <assert.h>

//typedef uint64_t IndexType;

int main()
{

	//****************************************************************************
	// Test: emu_matrix_datastructure constructor

	std::cout<<"Test Case 1: EMU Matrix Dimension Constructor Test: Started \n";
	fflush(stdout);

	const IndexType M = 8;
	const IndexType N = 4;

	emu_matrix<long> m1(M,N); 

	IndexType num_rows(m1.getRowDim());
	IndexType num_cols(m1.getColDim());

	assert(num_rows == M);
	assert(num_cols == N);

	std::cout<<"\t\t RowDim= "<<m1.getRowDim()<<"\t ColDim ="<<m1.getColDim()<<"\n";
	fflush(stdout);


	std::cout<<"Test Case 1: EMU Matrix Dimension Constructor Test: Completed \n\n";
	fflush(stdout);


	//****************************************************************************
	// Test: Store my input 2D array into emu_matrix_datastructure

	std::cout<<"Test Case 2: Storing my input 2D array into emu_matrix_datastructure Test: Started \n";
	fflush(stdout);

	IndexType mat_size=0;
	
	long mat[M][N] = {{1, 0, 0, 4},
		{2, 0, 0, 0},
		{3, 0, 9, 4},
		{4, 5, 0, 3},
		{5, 0, 0, 1},
		{6, 0, 0, 0},
		{7, 1, 0, 2},
		{8, 2, 3, 4}};
	std::cout<<"Printing the 2D array\n";
	fflush(stdout);

	
	for ( IndexType i =0; i < num_rows; i++)
	{
		for( IndexType j =0; j < num_cols; j++)
		{

			std::cout<<mat[i][j]<<'\t';
			fflush(stdout);
			mat_size = mat_size +1;
		}
		std::cout<<'\n';
		fflush(stdout);
	}

	std::cout<<"Printing the array from emu_matrix_datastructure\n";
	fflush(stdout);


	m1.store_from_2d_array((long*) mat);
	m1.print_emu_matrix();

	std::cout<<"Test Case 2: Storing my input 2D array into emu_matrix_datastructure Test: Completed \n\n";
	fflush(stdout);


	//****************************************************************************
	// Test: Size or Total number of elements pushed to emu_matrix_datastructure

	std::cout<<"Test Case 3: Total number of elements pushed into emu_matrix_datastructure Test: Started \n";
	fflush(stdout);

	IndexType emu_mat_size(m1.size());

	assert(mat_size == emu_mat_size);
	
	std::cout<<"\t\t EMU Matrix Size= "<<emu_mat_size<<"\t 2D Matrix Size= "<<mat_size<<"\n";
	fflush(stdout);
	std::cout<<"Test Case 3: Total number of elements pushed into emu_matrix_datastructure Test: Completed \n\n";
	fflush(stdout);

	return 0;
}

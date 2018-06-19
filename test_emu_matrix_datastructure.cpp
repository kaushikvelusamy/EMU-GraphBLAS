#include <iostream>
#include "emu_matrix_datastructure.hpp"
#include <assert.h>
//#include <vector>

int main()
{

	//****************************************************************************
	// Test: emu_matrix_datastructure constructor

	std::cout<<"Test Case 1: Row Block Dense: EMU Matrix Dimension Constructor Test: Started \n";
	fflush(stdout);

	const IndexType M = 16;
	const IndexType N = 4;

	emu_matrix<long> m1(M,N); 

	IndexType num_rows(m1.getRowDim());
	IndexType num_cols(m1.getColDim());

	assert(num_rows == M);
	assert(num_cols == N);

	std::cout<<"\t\t RowDim= "<<m1.getRowDim()<<"\t ColDim ="<<m1.getColDim()<<"\n";
	fflush(stdout);


	std::cout<<"Test Case 1:Row Block Dense: EMU Matrix Dimension Constructor Test: Completed \n\n";
	fflush(stdout);


	//****************************************************************************
	// Test: Store my input 2D array into emu_matrix_datastructure

	std::cout<<"Test Case 2: Row Block Dense: Storing my input 2D array into emu_matrix_datastructure Test: Started \n";
	fflush(stdout);

	IndexType mat_size=0;
	
	long mat[M][N]={{1, 0, 0, 4},
	                {2, 0, 0, 0},
		        {3, 0, 9, 4},
                        {4, 5, 0, 3},
			{5, 0, 0, 1},
			{6, 0, 0, 0},
			{7, 1, 0, 2},
			{8, 2, 3, 4},
                	{1, 0, 0, 4},
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


	m1.row_block_dense_store((long*) mat);
	m1.row_block_dense_print();

	std::cout<<"Test Case 2: Row Block Dense: Storing my input 2D array into emu_matrix_datastructure Test: Completed \n\n";
	fflush(stdout);


	//****************************************************************************
	// Test: Size or Total number of elements pushed to emu_matrix_datastructure

	std::cout<<"Test Case 3: Row Block Dense: Total number of elements pushed into emu_matrix_datastructure Test: Started \n";
	fflush(stdout);

	IndexType emu_mat_size(m1.row_block_dense_size());

	assert(mat_size == emu_mat_size);
	
	std::cout<<"\t\t EMU Matrix Size= "<<emu_mat_size<<"\t 2D Matrix Size= "<<mat_size<<"\n";
	fflush(stdout);
	std::cout<<"Test Case 3: Row Block Dense: Total number of elements pushed into emu_matrix_datastructure Test: Completed \n\n";
	fflush(stdout);




		//****************************************************************************
	// Test: Compare the elements in input2D Array and the elements in emu_matrix_datastructure

	std::cout<<"Test Case 4: Row Block Dense:  Compare the elements in input2D Array and the elements in emu_matrix_datastructure Test: Started \n";
	fflush(stdout);

	bool result = m1.compare_with_input((long*) mat); 

	std::cout<<"\t\t Comparison Result = "<<std::boolalpha<<result<<"\n";
	fflush(stdout);

	std::cout<<"Test Case 4: Row Block Dense:  Compare the elements in input2D Array and the elements in emu_matrix_datastructure Test: Completed \n\n";
	fflush(stdout);


		//****************************************************************************
	// Test: Compare the elements in input2D Array and the elements in emu_matrix_datastructure

		std::cout<<"Test Case 5:Block Sparse Store:  Storing my input 2D array into emu_matrix_datastructure Test: Started \n";
	fflush(stdout);

	IndexType mat_size_nz=0;
	std::cout<<"Printing the 2D array\n";
	fflush(stdout);

	
	for ( IndexType i =0; i < num_rows; i++)
	{
		for( IndexType j =0; j < num_cols; j++)
		{

			std::cout<<mat[i][j]<<'\t';
			fflush(stdout);
			if (mat[i][j] != 0)
			  mat_size_nz++;
		}
		std::cout<<'\n';
		fflush(stdout);
	}

	std::cout<<"Printing the array from emu_matrix_datastructure\n";
	fflush(stdout);


	m1.row_block_sparse_store((long*) mat);
	m1.row_block_sparse_print();

	std::cout<<"Test Case 5:Sparse Block Store: Storing my input 2D array into emu_matrix_datastructure Test: Completed \n\n";
	fflush(stdout);

	//****************************************************************************
	// Test: Row Block Sparse : Size or Total number of elements pushed to emu_matrix_datastructure

	std::cout<<"Test Case 6: Row Block Sparse: Total number of elements pushed into emu_matrix_datastructure Test: Started \n";
	fflush(stdout);

	IndexType emu_mat_size1(m1.row_block_sparse_size());

	assert(mat_size_nz == emu_mat_size1);
	
	std::cout<<"\t\t EMU Matrix Size= "<<emu_mat_size<<"\t 2D Matrix Size= "<<mat_size<<"\n";
	fflush(stdout);
	std::cout<<"Test Case 6: Row Block sparse: Total number of elements pushed into emu_matrix_datastructure Test: Completed \n\n";
	fflush(stdout);

		/***************************************************************************
	// Test: Compare the elements in input2D Array and the elements in emu_matrix_datastructure

		std::cout<<"Test Case 7:Cyclic Dense Store:  Storing my input 2D array into emu_matrix_datastructure Test: Started \n";
	fflush(stdout);

	std::cout<<"Printing the 2D array\n";
	fflush(stdout);

	
	for ( IndexType i =0; i < num_rows; i++)
	{
		for( IndexType j =0; j < num_cols; j++)
		{

			std::cout<<mat[i][j]<<'\t';
			fflush(stdout);
		}
		std::cout<<'\n';
		fflush(stdout);
	}

	std::cout<<"Printing the array from emu_matrix_datastructure\n";
	fflush(stdout);


	m1.row_cyclic_dense_store((long*) mat);
	m1.row_cyclic_dense_print();

	std::cout<<"Test Case 7:Cyclic Dense Store: Storing my input 2D array into emu_matrix_datastructure Test: Completed \n\n";
	fflush(stdout);

	****************************************************************************/


	
	return 0;
}

#include "distributed.h"
#include <tuple>
#include "cilk.h"

#pragma once
typedef uint64_t IndexType;

template <class ScalarType>
class emu_matrix {

	IndexType m_num_rows;
	IndexType m_nvals_dense=0;
	IndexType m_nvals_sparse=0;
        IndexType m_nvals_cyclic_dense=0;
	IndexType m_num_cols;
	IndexType rpn;
	IndexType repn;



	typedef std::tuple <IndexType, IndexType, ScalarType> matrixElement;

	matrixElement **denseBlockMatrix;
	matrixElement **sparseBlockMatrix;
	matrixElement **denseCyclicMatrix;
	matrixElement **sparseCyclicMatrix;

	public:
	emu_matrix(IndexType rows, IndexType cols)
	{
		m_num_rows=rows;
		m_num_cols=cols;
	}



	IndexType getRowDim();
	IndexType getColDim();

	void row_block_dense_store(ScalarType *arr);
	IndexType row_block_dense_size();
	void row_block_dense_print();

	void row_block_sparse_store(ScalarType *arr);
	IndexType row_block_sparse_size();
	void row_block_sparse_print();


	void row_cyclic_dense_store(ScalarType *arr);
	IndexType row_cyclic_dense_size();
	void row_cyclic_dense_print();

	void row_cyclic_sparse_store(ScalarType *arr);
	IndexType row_cyclic_sparse_size();
	void row_cyclic_sparse_print();



	bool compare_with_input(ScalarType *arr);

};


	template <class ScalarType>
IndexType emu_matrix<ScalarType>::getRowDim()
{
	return m_num_rows;  
}

	template <class ScalarType>
IndexType emu_matrix<ScalarType>::getColDim()
{
	return m_num_cols;  
}

	template <class ScalarType>
void emu_matrix<ScalarType>::row_block_dense_store(ScalarType *arr)
{
	rpn = m_num_rows / NODELETS();
	repn = rpn * m_num_cols;
	denseBlockMatrix  = (matrixElement **) mw_malloc2d(NODELETS(), repn * sizeof(matrixElement));
	for (IndexType i =0; i < NODELETS(); i++)
	{
		for(IndexType j =0; j < repn; j++)
		{
			denseBlockMatrix[i][j] = std::make_tuple((i*rpn+(j/m_num_cols)),(j%m_num_cols),*((arr+i*repn)+j));
			m_nvals_dense = m_nvals_dense + 1;
		}
	}
}


	template <class ScalarType>
IndexType emu_matrix<ScalarType>::row_block_dense_size()
{
	return m_nvals_dense;  
}


	template <class ScalarType>
void emu_matrix<ScalarType>::row_block_dense_print()
{
	for ( IndexType i =0; i < NODELETS(); i++)
	{
		for( IndexType j =0; j < repn; j++)
		{
			std::cout<<std::get<0>(denseBlockMatrix[i][j])<<','<<std::get<1>(denseBlockMatrix[i][j])<<" "<<std::get<2>(denseBlockMatrix[i][j])<<'\t';
			fflush(stdout);

		}
		std::cout<<'\n';
		fflush(stdout);
	}
}




	template <class ScalarType>
void emu_matrix<ScalarType>::row_block_sparse_store(ScalarType *arr)
{
	rpn = m_num_rows / NODELETS();
	repn = rpn * m_num_cols;
	sparseBlockMatrix  = (matrixElement **) mw_malloc2d(NODELETS(), repn * sizeof(matrixElement));
	IndexType nz_col_counter;
	for (IndexType i =0; i < NODELETS(); i++)
	{
		nz_col_counter = 0;
		for(IndexType j =0; j < repn; j++)
		{
			if ((*((arr+i*repn)+j)) != 0)
			{
				sparseBlockMatrix[i][nz_col_counter] = std::make_tuple((i*rpn+(j/m_num_cols)),(j%m_num_cols),*((arr+i*repn)+j));		
				m_nvals_sparse = m_nvals_sparse + 1;
				nz_col_counter++;
			}
		}
	}
}


	template <class ScalarType>
IndexType emu_matrix<ScalarType>::row_block_sparse_size()
{
	return m_nvals_sparse;  
}


	template <class ScalarType>
void emu_matrix<ScalarType>::row_block_sparse_print()
{
	for ( IndexType i =0; i < NODELETS(); i++)
	{
		for( IndexType j =0; j < repn; j++)
		{
			if(std::get<2>(sparseBlockMatrix[i][j]) != 0)
			{
				std::cout<<std::get<0>(sparseBlockMatrix[i][j])<<','<<std::get<1>(sparseBlockMatrix[i][j])<<" "<<std::get<2>(sparseBlockMatrix[i][j])<<'\t';
				fflush(stdout);
			}
		}

		std::cout<<'\n';
		fflush(stdout);
	}
}

	template <class ScalarType>
bool emu_matrix<ScalarType>::compare_with_input(ScalarType *arr)
{

	for ( IndexType i =0; i < NODELETS(); i++)
	{
		for( IndexType j =0; j < repn; j++)
		{
			if( std::get<2>(denseBlockMatrix[i][j]) != *((arr+i*repn)+j))
				return false;
		}
	}
	return true;
}

	template <class ScalarType>
void emu_matrix<ScalarType>::row_cyclic_dense_store(ScalarType *arr)
{
	rpn = m_num_rows / NODELETS();
	repn = rpn * m_num_cols;
	denseCyclicMatrix  = (matrixElement **) mw_malloc2d(NODELETS(), repn * sizeof(matrixElement));
	for (IndexType i =0; i < m_num_rows; i++)
	{
		for(IndexType j =0; j < m_num_cols; j++)
		{
		  denseBlockMatrix[(i % 8)][j] = std::make_tuple(i,j,*((arr+i*repn)+j));
			m_nvals_cyclic_dense = m_nvals_cyclic_dense + 1;
		}
	}
}


	template <class ScalarType>
IndexType emu_matrix<ScalarType>::row_cyclic_dense_size()
{
	return m_nvals_cyclic_dense;  
}


	template <class ScalarType>
void emu_matrix<ScalarType>::row_cyclic_dense_print()
{
	for ( IndexType i =0; i < NODELETS(); i++)
	{
		for( IndexType j =0; j < repn; j++)
		{
			std::cout<<std::get<0>(denseBlockMatrix[i][j])<<','<<std::get<1>(denseBlockMatrix[i][j])<<" "<<std::get<2>(denseBlockMatrix[i][j])<<'\t';
			fflush(stdout);

		}
		std::cout<<'\n';
		fflush(stdout);
	}
}


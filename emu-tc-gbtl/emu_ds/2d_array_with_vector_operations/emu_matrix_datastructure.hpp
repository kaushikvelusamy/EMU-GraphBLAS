#include "distributed.h"
#include <tuple>
#include "cilk.h"
#include <vector>

#pragma once
typedef uint64_t IndexType;

template <class ScalarType>
class emu_matrix {

	IndexType m_num_rows;
	IndexType m_num_cols;
	IndexType m_nvals_dense=0;
	IndexType rpn;
	IndexType repn;

	typedef std::tuple <IndexType, IndexType, ScalarType> matrixElement;

	matrixElement **denseBlockMatrix;
	
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

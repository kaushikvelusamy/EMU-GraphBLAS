#include "distributed.h"
#include <tuple>

#pragma once
typedef uint64_t IndexType;

template <class ScalarType>
class emu_matrix {

	IndexType m_num_rows;
	IndexType m_nvals=0;
	IndexType m_num_cols;
	IndexType rpn;
	IndexType repn;
	ScalarType **A;

	public:
	emu_matrix(IndexType rows, IndexType cols)
	{
		m_num_rows=rows;
		m_num_cols=cols;
	}
	IndexType getRowDim();
	IndexType getColDim();
	void store_from_2d_array(ScalarType *arr);
	IndexType size();
	void print_emu_matrix();
  
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
void emu_matrix<ScalarType>::store_from_2d_array(ScalarType *arr)
{
	rpn = m_num_rows / NODELETS();
	repn = rpn * m_num_cols;
	A = (ScalarType **) mw_malloc2d(NODELETS(), repn * sizeof(ScalarType));

	for (IndexType i =0; i < NODELETS(); i++)
	{
		for(IndexType j =0; j < repn; j++)
		{

			A[i][j] = *((arr+i*repn)+j);
			m_nvals = m_nvals + 1;
		}

	}

}


template <class ScalarType>
IndexType emu_matrix<ScalarType>::size()
{
	return m_nvals;  
}


template <class ScalarType>
void emu_matrix<ScalarType>::print_emu_matrix()
{
	for ( IndexType i =0; i < NODELETS(); i++)
	{
		for( IndexType j =0; j < repn; j++)
		{
			std::cout<<A[i][j]<<'\t';
			fflush(stdout);

		}
		std::cout<<'\n';
		fflush(stdout);
	}
}


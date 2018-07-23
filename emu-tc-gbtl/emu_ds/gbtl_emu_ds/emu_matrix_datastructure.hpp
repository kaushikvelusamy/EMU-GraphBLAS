#include "distributed.h"
#include <tuple>
#include "cilk.h"
#include <vector>
#include <iostream>
#include <tuple>
#include <functional>

#include <algorithm> 


#pragma once
typedef uint64_t IndexType;
typedef uint64_t ScalarType;
typedef std::vector<IndexType> IndexArrayType;

template <class ScalarType>
class emu_matrix {
	IndexType m_num_rows;
	IndexType m_num_cols;
	IndexType m_nvals_dense=0;
	IndexType m_nvals_sparse=0;
	IndexType m_nvals_cyclic_dense=0;
	IndexType rpn;
	unsigned long nodelets1;
	typedef std::vector<std::tuple <IndexType, ScalarType>> matrixElement;

	matrixElement **denseBlockMatrix;

	public:
	emu_matrix(IndexType rows, IndexType cols)
	{
		m_num_rows=rows;
		m_num_cols=cols;
	}



	IndexType getRowDim();
	IndexType getColDim();
	
	void setElement(IndexType i_it, IndexType j_it, ScalarType val, IndexType i, IndexType j);
	void row_block_dense_build(IndexArrayType :: iterator  i_it, 
			IndexArrayType :: iterator j_it,
			IndexArrayType :: iterator v_it,
			IndexType    n,
			int nodelets);
	IndexType row_block_dense_size();
	void row_block_dense_print();
};


template<class ScalarType>
void emu_matrix<ScalarType>::setElement(IndexType irow, IndexType icol, ScalarType val, IndexType i,IndexType j)
{

	if (irow >= m_num_rows || icol >= m_num_cols)
	{   
		std::cerr<<"throw IndexOutOfBoundsException(\"setElement(merge): index out of bounds\")";
	}

	if (denseBlockMatrix[i][j].empty())
	{
		denseBlockMatrix[i][j].push_back(std::make_tuple(icol, val));
		m_nvals_dense = m_nvals_dense + 1;
	}
	else
	{
		typename std::vector<std::tuple<IndexType, ScalarType>>::iterator it;
		for (it = denseBlockMatrix[i][j].begin(); it != denseBlockMatrix[i][j].end(); it++)
		{
			if (std::get<0>(*it) == icol)
			{
				std::get<1>(*it) = std::get<1>(*it);
			//	std::get<1>(*it) = std::merge(std::get<1>(*it), val);
				return;
			}
			else if (std::get<0>(*it) > icol)
			{
				denseBlockMatrix[i][j].insert(it, std::make_tuple(icol, val));
				m_nvals_dense = m_nvals_dense + 1;
				return;
			}
		}
		denseBlockMatrix[i][j].push_back(std::make_tuple(icol, val));
		m_nvals_dense = m_nvals_dense + 1;
	}
}




template<class ScalarType>
void emu_matrix<ScalarType>::row_block_dense_build(IndexArrayType :: iterator  i_it,
                        IndexArrayType :: iterator j_it,
                        IndexArrayType :: iterator v_it,
                        IndexType    n_rows_iL,
                        int nodelets)
{
	nodelets1 = nodelets;
	rpn = n_rows_iL / nodelets1;
	denseBlockMatrix  = (matrixElement **) mw_malloc2d(nodelets1, rpn * sizeof(matrixElement));

 for (IndexType i =0; i < nodelets1; i++)
        {
                for(IndexType j =0; j < rpn; j++)
                {
			emu_matrix<ScalarType>::setElement(*i_it, *j_it, *v_it,i,j);
			++i_it; ++j_it; ++v_it;
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
	// Used to print data in storage format instead of like a matrix
	std::cout<< "LilSparseMatrix<" << typeid(ScalarType).name() << ">"
		<< std::endl;
	std::cout<< "dimensions: " << m_num_rows << " x " << m_num_cols
		<< std::endl;
	std::cout<< "num stored values = " << m_nvals_dense << std::endl;
		
	std::cout<< "rpn = " << rpn << std::endl;

	for ( IndexType i =0; i < nodelets1; i++)
	{
		for( IndexType j =0; j < rpn; j++)
		{
			for (auto it = denseBlockMatrix[i][j].begin();it != denseBlockMatrix[i][j].end();++it)
				{
					std::cout<<"Nodele"<<i<<std::endl<<std::get<0>(*it)<< ":" << std::get<1>(*it);
					std::cout<<std::endl;
				}
		}
		std::cout<<std::endl;
		fflush(stdout);
	}
}



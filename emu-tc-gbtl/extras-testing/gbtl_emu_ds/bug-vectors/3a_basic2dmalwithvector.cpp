#include <iostream>
#include "distributed.h"
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
	typedef std::vector<int> matrixElement;
	matrixElement **denseBlockMatrix;
	matrixElement :: iterator itera;

	int m_nvals_dense = 0;

	denseBlockMatrix  = (matrixElement **) mw_malloc2d(4, 2 * sizeof(matrixElement));

	for ( int i =0; i < 4; i++)
	{
		for( int j =0; j < 2; j++)
		{
			denseBlockMatrix[i][j].push_back(1);
			denseBlockMatrix[i][j].push_back(2);
			m_nvals_dense = m_nvals_dense + 1;
		}
	}


	cout<<"Hello"<<endl;

	for ( int i =0; i < 4; i++)
	{
		for( int j =0; j < 2; j++)
		{
			cout<<"Nodele"<<i<<endl;
			for (itera = denseBlockMatrix[i][j].begin();itera != denseBlockMatrix[i][j].end();++itera)
			{
				cout<<"\t"<<*itera;

			}
			cout<<endl;
		}
		std::cout<<std::endl;
		fflush(stdout);
	}
	std::cout<<m_nvals_dense<<std::endl;
	return 0;

}

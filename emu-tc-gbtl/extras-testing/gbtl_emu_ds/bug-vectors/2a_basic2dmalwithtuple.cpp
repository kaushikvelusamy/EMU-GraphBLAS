#include <iostream>
#include <tuple>
#include "distributed.h"
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
	typedef tuple <int, int> matrixElement;

	int n= 32;
	long epn = n/NODELETS();
	cout<<epn<<endl;

	matrixElement** A = (matrixElement **) mw_malloc2d(NODELETS(), epn * sizeof(matrixElement));

	int m_nvals_dense = 0;



	for (long i=0; i<NODELETS(); i++)
	{
		for (long j=0; j<epn; j++)
		{
			A[i][j] = make_tuple(1, 1);
		}
	}

	cout<<"Hello"<<endl;


	for (long i=0; i<NODELETS(); i++)
	{
		cout<<"Nodele"<<i<<'\t';
		for (long j=0; j<epn; j++)
		{
			cout<<"\t"<<std::get<0>(A[i][j])<< ":" << std::get<1>(A[i][j]);				
		}
		cout<<endl;
	}

	cout<<m_nvals_dense;
	return 0;

}

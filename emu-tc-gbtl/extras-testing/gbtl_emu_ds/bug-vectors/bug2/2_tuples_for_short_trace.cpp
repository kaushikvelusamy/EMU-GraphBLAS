#include <iostream>
#include <tuple>
#include "distributed.h"
#include <tuple>

using namespace std;

int main(int argc, char **argv)
{
	starttiming();
	typedef tuple <int, int> matrixElement;
	int n= 16;
	long epn = n/NODELETS();

	matrixElement** A = (matrixElement **) mw_malloc2d(NODELETS(), epn * sizeof(matrixElement));


	for (long i=0; i<NODELETS(); i++)
	{
		for (long j=0; j<epn; j++)
		{
			A[i][j] = make_tuple(1, 1);
		}
	}


	for (long i=0; i<NODELETS(); i++)
	{
		cout<<"Nodele"<<i<<endl;
		for (long j=0; j<epn; j++)
		{
			int val1 = std::get<0>(A[i][j]);
			int val2 = std::get<1>(A[i][j]);						 		  
			cout << "\t" << val1<<":"<<val2<< endl;

		}	
		cout<<endl;
	}

	return 0;

}

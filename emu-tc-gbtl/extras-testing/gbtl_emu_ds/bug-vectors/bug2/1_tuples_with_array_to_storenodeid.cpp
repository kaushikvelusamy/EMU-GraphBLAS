#include <iostream>
#include <tuple>
#include "distributed.h"
#include <tuple>

using namespace std;

int main(int argc, char **argv)
{
//	starttiming();
	typedef tuple <int, int> matrixElement;
	int s_nodelet_arr[8][4];
	int e_nodelet_arr[8][4];

	int n= 16;
	long epn = n/NODELETS();

	matrixElement** A = (matrixElement **) mw_malloc2d(NODELETS(), epn * sizeof(matrixElement));

	for (long i=0; i<NODELETS(); i++)
	{
		for (long j=0; j<epn; j++)
		{
			s_nodelet_arr[i][j] = NODE_ID();
			A[i][j] = make_tuple(1, 1);
			e_nodelet_arr[i][j] = NODE_ID();
		}
	}

cout<<"Printing the starting nodeID array"<<endl;
	for (long i=0; i<NODELETS(); i++)
	{
		for (long j=0; j<epn; j++)
		{
			cout<<s_nodelet_arr[i][j]<<"\t";
			
		}
			
		cout<<endl;
	}

cout<<"Printing the ending nodeID array"<<endl;
	for (long i=0; i<NODELETS(); i++)
	{
		for (long j=0; j<epn; j++)
		{
			cout<<e_nodelet_arr[i][j]<<"\t";;
		}
		cout<<endl;
	}



cout<<"Printing the elements from each nodelet"<<endl;
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

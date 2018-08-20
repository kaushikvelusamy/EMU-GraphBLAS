#include <iostream>
#include <tuple>
#include "distributed.h"
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{

  int n= 32;
  long epn = n/NODELETS();
  cout<<epn<<endl;
  long ** A = (long **) mw_malloc2d(NODELETS(), epn * sizeof(long));

  int m_nvals_dense = 0;
  
  

  for (long i=0; i<NODELETS(); i++)
    {
       for (long j=0; j<epn; j++)
	 {
	   A[i][j] = i;
	 }
    }
  
  cout<<"Hello"<<endl;


   for (long i=0; i<NODELETS(); i++)
     {
       cout<<"Nodele"<<i<<'\t';
       for (long j=0; j<epn; j++)
	 {
	   cout<<A[i][j];				
	 }
       cout<<endl;
     }
   

  return 0;

}

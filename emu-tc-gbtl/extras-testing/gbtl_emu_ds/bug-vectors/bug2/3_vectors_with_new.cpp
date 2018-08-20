#include <iostream>
#include "distributed.h"
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
	starttiming();
	typedef std::vector<int>* pmatrixElement;
	pmatrixElement **denseBlockMatrix;

	denseBlockMatrix  = (pmatrixElement **) mw_malloc2d(4, 2 * sizeof(pmatrixElement));

	for ( int i =0; i < 4; i++)
	{
		for( int j =0; j < 2; j++)
		{
			denseBlockMatrix[i][j] = new vector<int>(); 
					
			unsigned long nid = NODE_ID();
			
			denseBlockMatrix[i][j]->push_back(1);
			denseBlockMatrix[i][j]->push_back(2);

			unsigned long nidend = NODE_ID();

			if (nid != nidend) 
				std::cout<<"timing problem"<<nid<<'\t'<<nidend<<std::endl;
 
		}
	}


	for ( int i =0; i < 4; i++)
	{
		for( int j =0; j < 2; j++)
		{
			cout<<"Nodele"<<i<<endl;
			for ( auto itera = denseBlockMatrix[i][j]->begin(); itera != denseBlockMatrix[i][j]->end(); ++itera)
			{
                                 unsigned long nid = NODE_ID();
                                 int val = *itera;
                                 unsigned long nidend = NODE_ID();
                                 cout << "\t" << nid << " : " << val << " : " << nidend << endl;
			}
			cout<<endl;
		}
		std::cout<<std::endl;
		fflush(stdout);
	}
	return 0;

}

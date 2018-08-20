#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include <getopt.h>
#include "memoryweb.h"

#include "emu_matrix_datastructure.hpp"


using namespace std;

int main(int argc, char **argv)
{
	unsigned long nnodes1 = NODELETS();
	unsigned long nthreads = 16;
	unsigned long printflag = 0;
	double clockrate = 150.0;
	std::string filename;

	int c;
	while ((c = getopt(argc, argv, "hn:t:c:p:f:")) != -1)
	{
		switch (c)
		{
			case 'h':
				std::cout<<"Optional argument: <file> (prompted if not present)"<<std::endl;
				std::cout<<"Program flag options: -hfntcp"<<std::endl;
				std::cout<<"  -h print this help and exit"<<std::endl;
				std::cout<<"  -f <file> enter the input file"<<std::endl;
				std::cout<<"  -n <N> for nodelets (power of 2), default NODELETS()"<<std::endl;
				std::cout<<"  -t <N> for number of threads, default 16"<<std::endl;
				std::cout<<"  -c <N> for clock rate, default 150.0MHz"<<std::endl;
				std::cout<<"  -p <N> for debug level > 0"<<std::endl;

				exit(0);
				break;
			case 'f': filename = optarg; break;
			case 'n': nnodes1 = atol(optarg); break;
			case 't': nthreads = atol(optarg); break;
			case 'c': clockrate = atof(optarg); break;
			case 'p': printflag = atol(optarg); break;
		}
	}

	std::cout<<"The Filename Entered is"<<filename<<std::endl;
	std::cout<<"The Number of Nodelets Entered is"<<nnodes1<<std::endl;
	std::cout<<"The Number of Threads Entered is"<<nthreads<<std::endl;
	std::cout<<"The ClockRate Entered is"<<clockrate<<std::endl;
	std::cout<<"The printFlag Entered is"<<printflag<<std::endl;

	IndexArrayType iL, iU, iA;
	IndexArrayType jL, jU, jA;

	uint64_t src, dst;
	int64_t num_rows = 0;
	int64_t max_id = 0;

	FILE *infile = fopen(filename.c_str(), "r");
	if (!infile)
	{
		fprintf(stderr, "Unable to open file: %s\n", argv[1]);
		exit(1);
	}

	while ( fscanf(infile, "%ld %ld", &src, &dst) == 2)
	{
		printf("Read: %ld, %ld\n", src, dst);
		if (src > max_id) max_id = src;
		if (dst > max_id) max_id = dst;

		if (src < dst)
		{
			iA.push_back(src);
			jA.push_back(dst);

			iU.push_back(src);
			jU.push_back(dst);
		}
		else if (dst < src)
		{
			iA.push_back(src);
			jA.push_back(dst);

			iL.push_back(src);
			jL.push_back(dst);
		}
		// else ignore self loops

		++num_rows;
	}


	IndexArrayType :: iterator i;
	fclose(infile);
	std::cout << "Read Input File Lines" << num_rows << " rows." << std::endl;
	std::cout << "#Nodes In The Input Graph= " << (max_id + 1) << std::endl;

	std::cout<<"iA Vector"<<std::endl;
	for (i = iA.begin(); i != iA.end(); ++i)
		std::cout << *i << '\t';
	std::cout<<std::endl;

	std::cout<<"jA Vector"<<std::endl;
	for (i = jA.begin(); i != jA.end(); ++i)
		std::cout << *i << '\t';
	std::cout<<std::endl;

	std::cout<<"iU Vector"<<std::endl;
	for (i = iU.begin(); i != iU.end(); ++i)
		std::cout << *i << '\t';
	std::cout<<std::endl;

	std::cout<<"jU Vector"<<std::endl;
	for (i = jU.begin(); i != jU.end(); ++i)
		std::cout << *i << '\t';
	std::cout<<std::endl;

	std::cout<<"iL Vector"<<std::endl;
	for (i = iL.begin(); i != iL.end(); ++i)
		std::cout << *i << '\t';
	std::cout<<std::endl;

	std::cout<<"jL Vector"<<std::endl;
	for (i = jL.begin(); i != jL.end(); ++i)
		std::cout << *i << '\t';
	std::cout<<std::endl;

	IndexType NUM_NODES(max_id + 1);
        IndexArrayType v(iA.size(), 1);
	
	emu_matrix<ScalarType> L(NUM_NODES, NUM_NODES);

	
	if(nnodes1 > NUM_NODES) 
		nnodes1=3;
	
	std::cout<<"Updated Nodelets:"<<'\t'<<nnodes1<<std::endl;

	L.row_block_dense_build(iL.begin(),jL.begin(), v.begin(), iL.size(),nnodes1);
	L.row_block_dense_print();

	//#ifndef SIM0
	//starttiming();
	unsigned long nid = NODE_ID();
	unsigned long starttime = CLOCK();
	//#endif


	//The GBTL Algorithm running on the distributed data layout goes here


	unsigned long endtime = CLOCK();
	unsigned long nidend = NODE_ID();
	if (nid != nidend) std::cout<<"timing problem"<<nid<<'\t'<<nidend<<std::endl;
	unsigned long totaltime = endtime - starttime;
	double ms = ((double) totaltime / clockrate) / 1000.0;
	std::cout<<std::endl;
	std::cout<<"Updated Nodelets:"<<'\t'<<nnodes1<<std::endl;
	std::cout<<"Nthreads:"<<'\t'<<nthreads<<std::endl;
	std::cout<<"ClockRate:"<<'\t'<<clockrate<<std::endl;
	std::cout<<"TotalClockCycles:"<<'\t'<<totaltime<<std::endl;
	std::cout<<"TotalTimeTaken:"<<'\t'<<ms<<std::endl;

	return 0;

}

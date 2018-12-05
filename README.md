# EMU-GraphBLAS
The EMU Backend for the graphBLAS template Library (GBTL)

## About

The implementation of this backend is currently focused on correctness
over performance.  

Working on the Development of Triangle Counting Algorithm and MXM

## Compile and Run
make
make run
make clean

or 

Check the emu-compile.sh script

/usr/local/emu-18.08.1/bin/emusim.x --ignore_starttiming run_emu_tc.mwx ./tc_demo/tc-small-data.tsv

## EMU-GBTL GOALS:
* Implement the Row Vector and the CSR Data Layout for EMU
* Implement Row and NonZero Work Distribution Strategy Across the Nodelets
* Implement matrix Reordering techniques
* Use Atomic and Remote Operations

## Acknowledgments and Disclaimers

This project is adapted from CMU SEI GBTL Repository. 

This project is still in the developmental stage. 

Once the Project is nearing the completion, the LICENSE, ACKNOWLEDGMENTS and other details will be updated. 


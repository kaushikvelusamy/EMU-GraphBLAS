# EMU-GraphBLAS
The EMU Backend for the graphBLAS template Library

## GraphBLAS Template Library (GBTL)

This is Version 2.0 of the C++ implementation that is mathematically
equivalent to the GraphBLAS C API.  Unlike the first version (which
predates the GraphBLAS C API Specification), this only contains the
backend written for a single CPU and development for emu-backend. 

The implementation of this backend is currently focused on correctness
over performance.  

## Compile and Run

Check the emu-compile.sh script in the /emu-tc-gbtl/src/demo/ directory
emusim.x ./a.out.mwx /emu-tc-gbtl/src/demo/dataset/tc-small-data.tsv

## Installation

The current library is set up as a header only library.  To install
this library, copy the graphblas directory (and its subfolders) to a
location in your include path.

## Project Goals

* Complete, mathematically equivalent implementation of the GraphBLAS C API
specification in C++ (specification http://graphblas.org) for EMU Migratory Thread Parallel Computer.
* Graph algorithm library supporting commonly used graph algorithms.
* Graph input/output library (TBD).

EMU-GBTL GOALS:
* Distribute the Matrix Across the Nodelets
* Use Atomic and Remote Operations

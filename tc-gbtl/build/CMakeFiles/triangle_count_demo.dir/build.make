# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/build

# Include any dependencies generated for this target.
include CMakeFiles/triangle_count_demo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/triangle_count_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/triangle_count_demo.dir/flags.make

CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o: CMakeFiles/triangle_count_demo.dir/flags.make
CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o: /home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/src/demo/triangle_count_demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o -c /home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/src/demo/triangle_count_demo.cpp

CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/src/demo/triangle_count_demo.cpp > CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.i

CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/src/demo/triangle_count_demo.cpp -o CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.s

CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o.requires:

.PHONY : CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o.requires

CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o.provides: CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o.requires
	$(MAKE) -f CMakeFiles/triangle_count_demo.dir/build.make CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o.provides.build
.PHONY : CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o.provides

CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o.provides.build: CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o


# Object files for target triangle_count_demo
triangle_count_demo_OBJECTS = \
"CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o"

# External object files for target triangle_count_demo
triangle_count_demo_EXTERNAL_OBJECTS =

bin/triangle_count_demo: CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o
bin/triangle_count_demo: CMakeFiles/triangle_count_demo.dir/build.make
bin/triangle_count_demo: CMakeFiles/triangle_count_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/triangle_count_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/triangle_count_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/triangle_count_demo.dir/build: bin/triangle_count_demo

.PHONY : CMakeFiles/triangle_count_demo.dir/build

CMakeFiles/triangle_count_demo.dir/requires: CMakeFiles/triangle_count_demo.dir/demo/triangle_count_demo.cpp.o.requires

.PHONY : CMakeFiles/triangle_count_demo.dir/requires

CMakeFiles/triangle_count_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/triangle_count_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/triangle_count_demo.dir/clean

CMakeFiles/triangle_count_demo.dir/depend:
	cd /home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/src /home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/src /home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/build /home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/build /home/kaushik/Desktop/EMU-GraphBLAS/tc-gbtl/gbtl/build/CMakeFiles/triangle_count_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/triangle_count_demo.dir/depend


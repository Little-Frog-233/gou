# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/zxh/2018数学建模/code/version2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zxh/2018数学建模/code/version2/build

# Include any dependencies generated for this target.
include CMakeFiles/linerSolve_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/linerSolve_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/linerSolve_lib.dir/flags.make

CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o: CMakeFiles/linerSolve_lib.dir/flags.make
CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o: ../src/linerSolver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zxh/2018数学建模/code/version2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o -c /home/zxh/2018数学建模/code/version2/src/linerSolver.cpp

CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zxh/2018数学建模/code/version2/src/linerSolver.cpp > CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.i

CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zxh/2018数学建模/code/version2/src/linerSolver.cpp -o CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.s

CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o.requires:

.PHONY : CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o.requires

CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o.provides: CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o.requires
	$(MAKE) -f CMakeFiles/linerSolve_lib.dir/build.make CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o.provides.build
.PHONY : CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o.provides

CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o.provides.build: CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o


# Object files for target linerSolve_lib
linerSolve_lib_OBJECTS = \
"CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o"

# External object files for target linerSolve_lib
linerSolve_lib_EXTERNAL_OBJECTS =

liblinerSolve_lib.so: CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o
liblinerSolve_lib.so: CMakeFiles/linerSolve_lib.dir/build.make
liblinerSolve_lib.so: CMakeFiles/linerSolve_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zxh/2018数学建模/code/version2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library liblinerSolve_lib.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/linerSolve_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/linerSolve_lib.dir/build: liblinerSolve_lib.so

.PHONY : CMakeFiles/linerSolve_lib.dir/build

CMakeFiles/linerSolve_lib.dir/requires: CMakeFiles/linerSolve_lib.dir/src/linerSolver.cpp.o.requires

.PHONY : CMakeFiles/linerSolve_lib.dir/requires

CMakeFiles/linerSolve_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/linerSolve_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/linerSolve_lib.dir/clean

CMakeFiles/linerSolve_lib.dir/depend:
	cd /home/zxh/2018数学建模/code/version2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zxh/2018数学建模/code/version2 /home/zxh/2018数学建模/code/version2 /home/zxh/2018数学建模/code/version2/build /home/zxh/2018数学建模/code/version2/build /home/zxh/2018数学建模/code/version2/build/CMakeFiles/linerSolve_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/linerSolve_lib.dir/depend


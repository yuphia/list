# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/lev/Documents/spiski/tools

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lev/Documents/spiski/tools

# Include any dependencies generated for this target.
include tests/CMakeFiles/tests.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/tests.dir/flags.make

tests/CMakeFiles/tests.dir/logtest.o: tests/CMakeFiles/tests.dir/flags.make
tests/CMakeFiles/tests.dir/logtest.o: tests/logtest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lev/Documents/spiski/tools/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/tests.dir/logtest.o"
	cd /home/lev/Documents/spiski/tools/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tests.dir/logtest.o -c /home/lev/Documents/spiski/tools/tests/logtest.cpp

tests/CMakeFiles/tests.dir/logtest.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests.dir/logtest.i"
	cd /home/lev/Documents/spiski/tools/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lev/Documents/spiski/tools/tests/logtest.cpp > CMakeFiles/tests.dir/logtest.i

tests/CMakeFiles/tests.dir/logtest.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests.dir/logtest.s"
	cd /home/lev/Documents/spiski/tools/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lev/Documents/spiski/tools/tests/logtest.cpp -o CMakeFiles/tests.dir/logtest.s

# Object files for target tests
tests_OBJECTS = \
"CMakeFiles/tests.dir/logtest.o"

# External object files for target tests
tests_EXTERNAL_OBJECTS =

tests/tests: tests/CMakeFiles/tests.dir/logtest.o
tests/tests: tests/CMakeFiles/tests.dir/build.make
tests/tests: tests/CMakeFiles/tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lev/Documents/spiski/tools/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tests"
	cd /home/lev/Documents/spiski/tools/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/tests.dir/build: tests/tests

.PHONY : tests/CMakeFiles/tests.dir/build

tests/CMakeFiles/tests.dir/clean:
	cd /home/lev/Documents/spiski/tools/tests && $(CMAKE_COMMAND) -P CMakeFiles/tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/tests.dir/clean

tests/CMakeFiles/tests.dir/depend:
	cd /home/lev/Documents/spiski/tools && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lev/Documents/spiski/tools /home/lev/Documents/spiski/tools/tests /home/lev/Documents/spiski/tools /home/lev/Documents/spiski/tools/tests /home/lev/Documents/spiski/tools/tests/CMakeFiles/tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/tests.dir/depend


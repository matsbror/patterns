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
CMAKE_SOURCE_DIR = /home/mats/embe/patterns/map

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mats/embe/patterns/map/cmake-build-release

# Include any dependencies generated for this target.
include CMakeFiles/map_tests.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/map_tests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/map_tests.dir/flags.make

CMakeFiles/map_tests.dir/test_map.cpp.o: CMakeFiles/map_tests.dir/flags.make
CMakeFiles/map_tests.dir/test_map.cpp.o: ../test_map.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mats/embe/patterns/map/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/map_tests.dir/test_map.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/map_tests.dir/test_map.cpp.o -c /home/mats/embe/patterns/map/test_map.cpp

CMakeFiles/map_tests.dir/test_map.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/map_tests.dir/test_map.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mats/embe/patterns/map/test_map.cpp > CMakeFiles/map_tests.dir/test_map.cpp.i

CMakeFiles/map_tests.dir/test_map.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/map_tests.dir/test_map.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mats/embe/patterns/map/test_map.cpp -o CMakeFiles/map_tests.dir/test_map.cpp.s

# Object files for target map_tests
map_tests_OBJECTS = \
"CMakeFiles/map_tests.dir/test_map.cpp.o"

# External object files for target map_tests
map_tests_EXTERNAL_OBJECTS =

map_tests: CMakeFiles/map_tests.dir/test_map.cpp.o
map_tests: CMakeFiles/map_tests.dir/build.make
map_tests: libmaplib.a
map_tests: /usr/local/lib/libtbb.so
map_tests: /usr/lib/gcc/x86_64-linux-gnu/10/libgomp.so
map_tests: /usr/lib/x86_64-linux-gnu/libpthread.so
map_tests: CMakeFiles/map_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mats/embe/patterns/map/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable map_tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/map_tests.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -D TEST_TARGET=map_tests -D TEST_EXECUTABLE=/home/mats/embe/patterns/map/cmake-build-release/map_tests -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/mats/embe/patterns/map/cmake-build-release -D TEST_SPEC= -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_LIST=map_tests_TESTS -D CTEST_FILE=/home/mats/embe/patterns/map/cmake-build-release/map_tests_tests-b858cb2.cmake -P /usr/lib/cmake/Catch2/CatchAddTests.cmake

# Rule to build all files generated by this target.
CMakeFiles/map_tests.dir/build: map_tests

.PHONY : CMakeFiles/map_tests.dir/build

CMakeFiles/map_tests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/map_tests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/map_tests.dir/clean

CMakeFiles/map_tests.dir/depend:
	cd /home/mats/embe/patterns/map/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mats/embe/patterns/map /home/mats/embe/patterns/map /home/mats/embe/patterns/map/cmake-build-release /home/mats/embe/patterns/map/cmake-build-release /home/mats/embe/patterns/map/cmake-build-release/CMakeFiles/map_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/map_tests.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/cmake-build-debug

# Include any dependencies generated for this target.
include tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/flags.make

tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.o: tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/flags.make
tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.o: ../tests/kb_tests.cpp
tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.o: tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.o"
	cd /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/cmake-build-debug/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.o -MF CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.o.d -o CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.o -c /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/tests/kb_tests.cpp

tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.i"
	cd /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/cmake-build-debug/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/tests/kb_tests.cpp > CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.i

tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.s"
	cd /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/cmake-build-debug/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/tests/kb_tests.cpp -o CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.s

# Object files for target ex4Tests_UnreachableFrames
ex4Tests_UnreachableFrames_OBJECTS = \
"CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.o"

# External object files for target ex4Tests_UnreachableFrames
ex4Tests_UnreachableFrames_EXTERNAL_OBJECTS =

tests/ex4Tests_UnreachableFrames: tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/kb_tests.cpp.o
tests/ex4Tests_UnreachableFrames: tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/build.make
tests/ex4Tests_UnreachableFrames: libUnreachableFramesVirtualMemory.a
tests/ex4Tests_UnreachableFrames: lib/libgtest_main.a
tests/ex4Tests_UnreachableFrames: lib/libgtest.a
tests/ex4Tests_UnreachableFrames: tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ex4Tests_UnreachableFrames"
	cd /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/cmake-build-debug/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex4Tests_UnreachableFrames.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/build: tests/ex4Tests_UnreachableFrames
.PHONY : tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/build

tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/clean:
	cd /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/cmake-build-debug/tests && $(CMAKE_COMMAND) -P CMakeFiles/ex4Tests_UnreachableFrames.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/clean

tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/depend:
	cd /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/tests /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/cmake-build-debug /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/cmake-build-debug/tests /mnt/c/Users/galva/CLionProjects/OS_ex4/OS_Memory_Manegment/cmake-build-debug/tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/ex4Tests_UnreachableFrames.dir/depend


# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/spacegaori/dev/hello/examples/cli

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/spacegaori/dev/hello/examples/cli/build

# Include any dependencies generated for this target.
include CMakeFiles/cli.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cli.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cli.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cli.dir/flags.make

CMakeFiles/cli.dir/src/main.cpp.o: CMakeFiles/cli.dir/flags.make
CMakeFiles/cli.dir/src/main.cpp.o: /Users/spacegaori/dev/hello/examples/cli/src/main.cpp
CMakeFiles/cli.dir/src/main.cpp.o: CMakeFiles/cli.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/spacegaori/dev/hello/examples/cli/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cli.dir/src/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cli.dir/src/main.cpp.o -MF CMakeFiles/cli.dir/src/main.cpp.o.d -o CMakeFiles/cli.dir/src/main.cpp.o -c /Users/spacegaori/dev/hello/examples/cli/src/main.cpp

CMakeFiles/cli.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cli.dir/src/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/spacegaori/dev/hello/examples/cli/src/main.cpp > CMakeFiles/cli.dir/src/main.cpp.i

CMakeFiles/cli.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cli.dir/src/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/spacegaori/dev/hello/examples/cli/src/main.cpp -o CMakeFiles/cli.dir/src/main.cpp.s

# Object files for target cli
cli_OBJECTS = \
"CMakeFiles/cli.dir/src/main.cpp.o"

# External object files for target cli
cli_EXTERNAL_OBJECTS =

cli: CMakeFiles/cli.dir/src/main.cpp.o
cli: CMakeFiles/cli.dir/build.make
cli: CMakeFiles/cli.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/spacegaori/dev/hello/examples/cli/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cli"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cli.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cli.dir/build: cli
.PHONY : CMakeFiles/cli.dir/build

CMakeFiles/cli.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cli.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cli.dir/clean

CMakeFiles/cli.dir/depend:
	cd /Users/spacegaori/dev/hello/examples/cli/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/spacegaori/dev/hello/examples/cli /Users/spacegaori/dev/hello/examples/cli /Users/spacegaori/dev/hello/examples/cli/build /Users/spacegaori/dev/hello/examples/cli/build /Users/spacegaori/dev/hello/examples/cli/build/CMakeFiles/cli.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/cli.dir/depend

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "/Users/christopher/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/212.5284.51/CLion.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/christopher/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/212.5284.51/CLion.app/Contents/bin/cmake/mac/bin/cmake" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/christopher/CLionProjects/ProjectChristopherRomano

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/christopher/CLionProjects/ProjectChristopherRomano/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ProjectChristopherRomano.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/ProjectChristopherRomano.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProjectChristopherRomano.dir/flags.make

CMakeFiles/ProjectChristopherRomano.dir/main.c.o: CMakeFiles/ProjectChristopherRomano.dir/flags.make
CMakeFiles/ProjectChristopherRomano.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/christopher/CLionProjects/ProjectChristopherRomano/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ProjectChristopherRomano.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ProjectChristopherRomano.dir/main.c.o -c /Users/christopher/CLionProjects/ProjectChristopherRomano/main.c

CMakeFiles/ProjectChristopherRomano.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProjectChristopherRomano.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/christopher/CLionProjects/ProjectChristopherRomano/main.c > CMakeFiles/ProjectChristopherRomano.dir/main.c.i

CMakeFiles/ProjectChristopherRomano.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProjectChristopherRomano.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/christopher/CLionProjects/ProjectChristopherRomano/main.c -o CMakeFiles/ProjectChristopherRomano.dir/main.c.s

# Object files for target ProjectChristopherRomano
ProjectChristopherRomano_OBJECTS = \
"CMakeFiles/ProjectChristopherRomano.dir/main.c.o"

# External object files for target ProjectChristopherRomano
ProjectChristopherRomano_EXTERNAL_OBJECTS =

ProjectChristopherRomano: CMakeFiles/ProjectChristopherRomano.dir/main.c.o
ProjectChristopherRomano: CMakeFiles/ProjectChristopherRomano.dir/build.make
ProjectChristopherRomano: CMakeFiles/ProjectChristopherRomano.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/christopher/CLionProjects/ProjectChristopherRomano/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ProjectChristopherRomano"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProjectChristopherRomano.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProjectChristopherRomano.dir/build: ProjectChristopherRomano
.PHONY : CMakeFiles/ProjectChristopherRomano.dir/build

CMakeFiles/ProjectChristopherRomano.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProjectChristopherRomano.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProjectChristopherRomano.dir/clean

CMakeFiles/ProjectChristopherRomano.dir/depend:
	cd /Users/christopher/CLionProjects/ProjectChristopherRomano/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/christopher/CLionProjects/ProjectChristopherRomano /Users/christopher/CLionProjects/ProjectChristopherRomano /Users/christopher/CLionProjects/ProjectChristopherRomano/cmake-build-debug /Users/christopher/CLionProjects/ProjectChristopherRomano/cmake-build-debug /Users/christopher/CLionProjects/ProjectChristopherRomano/cmake-build-debug/CMakeFiles/ProjectChristopherRomano.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProjectChristopherRomano.dir/depend

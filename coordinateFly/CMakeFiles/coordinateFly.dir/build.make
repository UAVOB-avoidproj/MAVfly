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
CMAKE_SOURCE_DIR = /opt/dev/MAVfly/coordinateFly

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /opt/dev/MAVfly/coordinateFly

# Include any dependencies generated for this target.
include CMakeFiles/coordinateFly.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/coordinateFly.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/coordinateFly.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/coordinateFly.dir/flags.make

CMakeFiles/coordinateFly.dir/coordinateFly.cpp.o: CMakeFiles/coordinateFly.dir/flags.make
CMakeFiles/coordinateFly.dir/coordinateFly.cpp.o: coordinateFly.cpp
CMakeFiles/coordinateFly.dir/coordinateFly.cpp.o: CMakeFiles/coordinateFly.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/opt/dev/MAVfly/coordinateFly/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/coordinateFly.dir/coordinateFly.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/coordinateFly.dir/coordinateFly.cpp.o -MF CMakeFiles/coordinateFly.dir/coordinateFly.cpp.o.d -o CMakeFiles/coordinateFly.dir/coordinateFly.cpp.o -c /opt/dev/MAVfly/coordinateFly/coordinateFly.cpp

CMakeFiles/coordinateFly.dir/coordinateFly.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/coordinateFly.dir/coordinateFly.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /opt/dev/MAVfly/coordinateFly/coordinateFly.cpp > CMakeFiles/coordinateFly.dir/coordinateFly.cpp.i

CMakeFiles/coordinateFly.dir/coordinateFly.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/coordinateFly.dir/coordinateFly.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /opt/dev/MAVfly/coordinateFly/coordinateFly.cpp -o CMakeFiles/coordinateFly.dir/coordinateFly.cpp.s

# Object files for target coordinateFly
coordinateFly_OBJECTS = \
"CMakeFiles/coordinateFly.dir/coordinateFly.cpp.o"

# External object files for target coordinateFly
coordinateFly_EXTERNAL_OBJECTS =

coordinateFly: CMakeFiles/coordinateFly.dir/coordinateFly.cpp.o
coordinateFly: CMakeFiles/coordinateFly.dir/build.make
coordinateFly: /usr/lib/libmavsdk.so.2.6.0
coordinateFly: CMakeFiles/coordinateFly.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/opt/dev/MAVfly/coordinateFly/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable coordinateFly"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/coordinateFly.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/coordinateFly.dir/build: coordinateFly
.PHONY : CMakeFiles/coordinateFly.dir/build

CMakeFiles/coordinateFly.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/coordinateFly.dir/cmake_clean.cmake
.PHONY : CMakeFiles/coordinateFly.dir/clean

CMakeFiles/coordinateFly.dir/depend:
	cd /opt/dev/MAVfly/coordinateFly && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /opt/dev/MAVfly/coordinateFly /opt/dev/MAVfly/coordinateFly /opt/dev/MAVfly/coordinateFly /opt/dev/MAVfly/coordinateFly /opt/dev/MAVfly/coordinateFly/CMakeFiles/coordinateFly.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/coordinateFly.dir/depend


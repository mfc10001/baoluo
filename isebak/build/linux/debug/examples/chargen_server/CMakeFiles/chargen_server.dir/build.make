# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_SOURCE_DIR = /home/ll/baoluo/ise/build/linux

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ll/baoluo/ise/build/linux/debug

# Include any dependencies generated for this target.
include examples/chargen_server/CMakeFiles/chargen_server.dir/depend.make

# Include the progress variables for this target.
include examples/chargen_server/CMakeFiles/chargen_server.dir/progress.make

# Include the compile flags for this target's objects.
include examples/chargen_server/CMakeFiles/chargen_server.dir/flags.make

examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o: examples/chargen_server/CMakeFiles/chargen_server.dir/flags.make
examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o: /home/ll/baoluo/ise/examples/chargen_server/chargen_server.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ll/baoluo/ise/build/linux/debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/chargen_server && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/chargen_server.dir/chargen_server.cpp.o -c /home/ll/baoluo/ise/examples/chargen_server/chargen_server.cpp

examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chargen_server.dir/chargen_server.cpp.i"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/chargen_server && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ll/baoluo/ise/examples/chargen_server/chargen_server.cpp > CMakeFiles/chargen_server.dir/chargen_server.cpp.i

examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chargen_server.dir/chargen_server.cpp.s"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/chargen_server && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ll/baoluo/ise/examples/chargen_server/chargen_server.cpp -o CMakeFiles/chargen_server.dir/chargen_server.cpp.s

examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o.requires:
.PHONY : examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o.requires

examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o.provides: examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o.requires
	$(MAKE) -f examples/chargen_server/CMakeFiles/chargen_server.dir/build.make examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o.provides.build
.PHONY : examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o.provides

examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o.provides.build: examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o

# Object files for target chargen_server
chargen_server_OBJECTS = \
"CMakeFiles/chargen_server.dir/chargen_server.cpp.o"

# External object files for target chargen_server
chargen_server_EXTERNAL_OBJECTS =

bin/chargen_server: examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o
bin/chargen_server: examples/chargen_server/CMakeFiles/chargen_server.dir/build.make
bin/chargen_server: lib/libise.a
bin/chargen_server: examples/chargen_server/CMakeFiles/chargen_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/chargen_server"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/chargen_server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chargen_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/chargen_server/CMakeFiles/chargen_server.dir/build: bin/chargen_server
.PHONY : examples/chargen_server/CMakeFiles/chargen_server.dir/build

examples/chargen_server/CMakeFiles/chargen_server.dir/requires: examples/chargen_server/CMakeFiles/chargen_server.dir/chargen_server.cpp.o.requires
.PHONY : examples/chargen_server/CMakeFiles/chargen_server.dir/requires

examples/chargen_server/CMakeFiles/chargen_server.dir/clean:
	cd /home/ll/baoluo/ise/build/linux/debug/examples/chargen_server && $(CMAKE_COMMAND) -P CMakeFiles/chargen_server.dir/cmake_clean.cmake
.PHONY : examples/chargen_server/CMakeFiles/chargen_server.dir/clean

examples/chargen_server/CMakeFiles/chargen_server.dir/depend:
	cd /home/ll/baoluo/ise/build/linux/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ll/baoluo/ise/build/linux /home/ll/baoluo/ise/examples/chargen_server /home/ll/baoluo/ise/build/linux/debug /home/ll/baoluo/ise/build/linux/debug/examples/chargen_server /home/ll/baoluo/ise/build/linux/debug/examples/chargen_server/CMakeFiles/chargen_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/chargen_server/CMakeFiles/chargen_server.dir/depend


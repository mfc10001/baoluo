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
include examples/server_inspector/CMakeFiles/server_inspector.dir/depend.make

# Include the progress variables for this target.
include examples/server_inspector/CMakeFiles/server_inspector.dir/progress.make

# Include the compile flags for this target's objects.
include examples/server_inspector/CMakeFiles/server_inspector.dir/flags.make

examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o: examples/server_inspector/CMakeFiles/server_inspector.dir/flags.make
examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o: /home/ll/baoluo/ise/examples/server_inspector/app_business.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ll/baoluo/ise/build/linux/debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/server_inspector && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/server_inspector.dir/app_business.cpp.o -c /home/ll/baoluo/ise/examples/server_inspector/app_business.cpp

examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_inspector.dir/app_business.cpp.i"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/server_inspector && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ll/baoluo/ise/examples/server_inspector/app_business.cpp > CMakeFiles/server_inspector.dir/app_business.cpp.i

examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_inspector.dir/app_business.cpp.s"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/server_inspector && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ll/baoluo/ise/examples/server_inspector/app_business.cpp -o CMakeFiles/server_inspector.dir/app_business.cpp.s

examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o.requires:
.PHONY : examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o.requires

examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o.provides: examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o.requires
	$(MAKE) -f examples/server_inspector/CMakeFiles/server_inspector.dir/build.make examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o.provides.build
.PHONY : examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o.provides

examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o.provides.build: examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o

examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o: examples/server_inspector/CMakeFiles/server_inspector.dir/flags.make
examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o: /home/ll/baoluo/ise/examples/server_inspector/svr_mod_inspector.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ll/baoluo/ise/build/linux/debug/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/server_inspector && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o -c /home/ll/baoluo/ise/examples/server_inspector/svr_mod_inspector.cpp

examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.i"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/server_inspector && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ll/baoluo/ise/examples/server_inspector/svr_mod_inspector.cpp > CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.i

examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.s"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/server_inspector && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ll/baoluo/ise/examples/server_inspector/svr_mod_inspector.cpp -o CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.s

examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o.requires:
.PHONY : examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o.requires

examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o.provides: examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o.requires
	$(MAKE) -f examples/server_inspector/CMakeFiles/server_inspector.dir/build.make examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o.provides.build
.PHONY : examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o.provides

examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o.provides.build: examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o

# Object files for target server_inspector
server_inspector_OBJECTS = \
"CMakeFiles/server_inspector.dir/app_business.cpp.o" \
"CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o"

# External object files for target server_inspector
server_inspector_EXTERNAL_OBJECTS =

bin/server_inspector: examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o
bin/server_inspector: examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o
bin/server_inspector: examples/server_inspector/CMakeFiles/server_inspector.dir/build.make
bin/server_inspector: lib/libise.a
bin/server_inspector: examples/server_inspector/CMakeFiles/server_inspector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/server_inspector"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/server_inspector && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server_inspector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/server_inspector/CMakeFiles/server_inspector.dir/build: bin/server_inspector
.PHONY : examples/server_inspector/CMakeFiles/server_inspector.dir/build

examples/server_inspector/CMakeFiles/server_inspector.dir/requires: examples/server_inspector/CMakeFiles/server_inspector.dir/app_business.cpp.o.requires
examples/server_inspector/CMakeFiles/server_inspector.dir/requires: examples/server_inspector/CMakeFiles/server_inspector.dir/svr_mod_inspector.cpp.o.requires
.PHONY : examples/server_inspector/CMakeFiles/server_inspector.dir/requires

examples/server_inspector/CMakeFiles/server_inspector.dir/clean:
	cd /home/ll/baoluo/ise/build/linux/debug/examples/server_inspector && $(CMAKE_COMMAND) -P CMakeFiles/server_inspector.dir/cmake_clean.cmake
.PHONY : examples/server_inspector/CMakeFiles/server_inspector.dir/clean

examples/server_inspector/CMakeFiles/server_inspector.dir/depend:
	cd /home/ll/baoluo/ise/build/linux/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ll/baoluo/ise/build/linux /home/ll/baoluo/ise/examples/server_inspector /home/ll/baoluo/ise/build/linux/debug /home/ll/baoluo/ise/build/linux/debug/examples/server_inspector /home/ll/baoluo/ise/build/linux/debug/examples/server_inspector/CMakeFiles/server_inspector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/server_inspector/CMakeFiles/server_inspector.dir/depend

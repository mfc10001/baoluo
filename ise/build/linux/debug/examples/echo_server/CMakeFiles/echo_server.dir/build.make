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
include examples/echo_server/CMakeFiles/echo_server.dir/depend.make

# Include the progress variables for this target.
include examples/echo_server/CMakeFiles/echo_server.dir/progress.make

# Include the compile flags for this target's objects.
include examples/echo_server/CMakeFiles/echo_server.dir/flags.make

examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o: examples/echo_server/CMakeFiles/echo_server.dir/flags.make
examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o: /home/ll/baoluo/ise/examples/echo_server/echo_server.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ll/baoluo/ise/build/linux/debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/echo_server.dir/echo_server.cpp.o -c /home/ll/baoluo/ise/examples/echo_server/echo_server.cpp

examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_server.dir/echo_server.cpp.i"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ll/baoluo/ise/examples/echo_server/echo_server.cpp > CMakeFiles/echo_server.dir/echo_server.cpp.i

examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_server.dir/echo_server.cpp.s"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ll/baoluo/ise/examples/echo_server/echo_server.cpp -o CMakeFiles/echo_server.dir/echo_server.cpp.s

examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o.requires:
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o.requires

examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o.provides: examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o.requires
	$(MAKE) -f examples/echo_server/CMakeFiles/echo_server.dir/build.make examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o.provides.build
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o.provides

examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o.provides.build: examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o

examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o: examples/echo_server/CMakeFiles/echo_server.dir/flags.make
examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o: /home/ll/baoluo/ise/examples/echo_server/client_msg.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ll/baoluo/ise/build/linux/debug/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/echo_server.dir/client_msg.cpp.o -c /home/ll/baoluo/ise/examples/echo_server/client_msg.cpp

examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_server.dir/client_msg.cpp.i"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ll/baoluo/ise/examples/echo_server/client_msg.cpp > CMakeFiles/echo_server.dir/client_msg.cpp.i

examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_server.dir/client_msg.cpp.s"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ll/baoluo/ise/examples/echo_server/client_msg.cpp -o CMakeFiles/echo_server.dir/client_msg.cpp.s

examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o.requires:
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o.requires

examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o.provides: examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o.requires
	$(MAKE) -f examples/echo_server/CMakeFiles/echo_server.dir/build.make examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o.provides.build
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o.provides

examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o.provides.build: examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o

examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o: examples/echo_server/CMakeFiles/echo_server.dir/flags.make
examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o: /home/ll/baoluo/ise/examples/echo_server/game_core/ConfigManager.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ll/baoluo/ise/build/linux/debug/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o -c /home/ll/baoluo/ise/examples/echo_server/game_core/ConfigManager.cpp

examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.i"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ll/baoluo/ise/examples/echo_server/game_core/ConfigManager.cpp > CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.i

examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.s"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ll/baoluo/ise/examples/echo_server/game_core/ConfigManager.cpp -o CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.s

examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o.requires:
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o.requires

examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o.provides: examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o.requires
	$(MAKE) -f examples/echo_server/CMakeFiles/echo_server.dir/build.make examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o.provides.build
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o.provides

examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o.provides.build: examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o

examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o: examples/echo_server/CMakeFiles/echo_server.dir/flags.make
examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o: /home/ll/baoluo/ise/examples/echo_server/game_core/GamePlayer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ll/baoluo/ise/build/linux/debug/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o -c /home/ll/baoluo/ise/examples/echo_server/game_core/GamePlayer.cpp

examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.i"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ll/baoluo/ise/examples/echo_server/game_core/GamePlayer.cpp > CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.i

examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.s"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ll/baoluo/ise/examples/echo_server/game_core/GamePlayer.cpp -o CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.s

examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o.requires:
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o.requires

examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o.provides: examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o.requires
	$(MAKE) -f examples/echo_server/CMakeFiles/echo_server.dir/build.make examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o.provides.build
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o.provides

examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o.provides.build: examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o

examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o: examples/echo_server/CMakeFiles/echo_server.dir/flags.make
examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o: /home/ll/baoluo/ise/examples/echo_server/game_core/GamePlayerManager.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ll/baoluo/ise/build/linux/debug/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o -c /home/ll/baoluo/ise/examples/echo_server/game_core/GamePlayerManager.cpp

examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.i"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ll/baoluo/ise/examples/echo_server/game_core/GamePlayerManager.cpp > CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.i

examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.s"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ll/baoluo/ise/examples/echo_server/game_core/GamePlayerManager.cpp -o CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.s

examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o.requires:
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o.requires

examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o.provides: examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o.requires
	$(MAKE) -f examples/echo_server/CMakeFiles/echo_server.dir/build.make examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o.provides.build
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o.provides

examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o.provides.build: examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o

# Object files for target echo_server
echo_server_OBJECTS = \
"CMakeFiles/echo_server.dir/echo_server.cpp.o" \
"CMakeFiles/echo_server.dir/client_msg.cpp.o" \
"CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o" \
"CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o" \
"CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o"

# External object files for target echo_server
echo_server_EXTERNAL_OBJECTS =

bin/echo_server: examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o
bin/echo_server: examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o
bin/echo_server: examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o
bin/echo_server: examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o
bin/echo_server: examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o
bin/echo_server: examples/echo_server/CMakeFiles/echo_server.dir/build.make
bin/echo_server: lib/libise.a
bin/echo_server: lib/libise_utils_json.a
bin/echo_server: examples/echo_server/CMakeFiles/echo_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/echo_server"
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/echo_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/echo_server/CMakeFiles/echo_server.dir/build: bin/echo_server
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/build

examples/echo_server/CMakeFiles/echo_server.dir/requires: examples/echo_server/CMakeFiles/echo_server.dir/echo_server.cpp.o.requires
examples/echo_server/CMakeFiles/echo_server.dir/requires: examples/echo_server/CMakeFiles/echo_server.dir/client_msg.cpp.o.requires
examples/echo_server/CMakeFiles/echo_server.dir/requires: examples/echo_server/CMakeFiles/echo_server.dir/game_core/ConfigManager.cpp.o.requires
examples/echo_server/CMakeFiles/echo_server.dir/requires: examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayer.cpp.o.requires
examples/echo_server/CMakeFiles/echo_server.dir/requires: examples/echo_server/CMakeFiles/echo_server.dir/game_core/GamePlayerManager.cpp.o.requires
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/requires

examples/echo_server/CMakeFiles/echo_server.dir/clean:
	cd /home/ll/baoluo/ise/build/linux/debug/examples/echo_server && $(CMAKE_COMMAND) -P CMakeFiles/echo_server.dir/cmake_clean.cmake
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/clean

examples/echo_server/CMakeFiles/echo_server.dir/depend:
	cd /home/ll/baoluo/ise/build/linux/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ll/baoluo/ise/build/linux /home/ll/baoluo/ise/examples/echo_server /home/ll/baoluo/ise/build/linux/debug /home/ll/baoluo/ise/build/linux/debug/examples/echo_server /home/ll/baoluo/ise/build/linux/debug/examples/echo_server/CMakeFiles/echo_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/echo_server/CMakeFiles/echo_server.dir/depend


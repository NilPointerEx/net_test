# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zodiac/git/net_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zodiac/git/net_test

# Include any dependencies generated for this target.
include CMakeFiles/net_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/net_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/net_test.dir/flags.make

CMakeFiles/net_test.dir/test_echo.cpp.o: CMakeFiles/net_test.dir/flags.make
CMakeFiles/net_test.dir/test_echo.cpp.o: test_echo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zodiac/git/net_test/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/net_test.dir/test_echo.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/net_test.dir/test_echo.cpp.o -c /home/zodiac/git/net_test/test_echo.cpp

CMakeFiles/net_test.dir/test_echo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_test.dir/test_echo.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zodiac/git/net_test/test_echo.cpp > CMakeFiles/net_test.dir/test_echo.cpp.i

CMakeFiles/net_test.dir/test_echo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_test.dir/test_echo.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zodiac/git/net_test/test_echo.cpp -o CMakeFiles/net_test.dir/test_echo.cpp.s

CMakeFiles/net_test.dir/test_echo.cpp.o.requires:
.PHONY : CMakeFiles/net_test.dir/test_echo.cpp.o.requires

CMakeFiles/net_test.dir/test_echo.cpp.o.provides: CMakeFiles/net_test.dir/test_echo.cpp.o.requires
	$(MAKE) -f CMakeFiles/net_test.dir/build.make CMakeFiles/net_test.dir/test_echo.cpp.o.provides.build
.PHONY : CMakeFiles/net_test.dir/test_echo.cpp.o.provides

CMakeFiles/net_test.dir/test_echo.cpp.o.provides.build: CMakeFiles/net_test.dir/test_echo.cpp.o

CMakeFiles/net_test.dir/test_epoll.cpp.o: CMakeFiles/net_test.dir/flags.make
CMakeFiles/net_test.dir/test_epoll.cpp.o: test_epoll.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zodiac/git/net_test/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/net_test.dir/test_epoll.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/net_test.dir/test_epoll.cpp.o -c /home/zodiac/git/net_test/test_epoll.cpp

CMakeFiles/net_test.dir/test_epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_test.dir/test_epoll.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zodiac/git/net_test/test_epoll.cpp > CMakeFiles/net_test.dir/test_epoll.cpp.i

CMakeFiles/net_test.dir/test_epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_test.dir/test_epoll.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zodiac/git/net_test/test_epoll.cpp -o CMakeFiles/net_test.dir/test_epoll.cpp.s

CMakeFiles/net_test.dir/test_epoll.cpp.o.requires:
.PHONY : CMakeFiles/net_test.dir/test_epoll.cpp.o.requires

CMakeFiles/net_test.dir/test_epoll.cpp.o.provides: CMakeFiles/net_test.dir/test_epoll.cpp.o.requires
	$(MAKE) -f CMakeFiles/net_test.dir/build.make CMakeFiles/net_test.dir/test_epoll.cpp.o.provides.build
.PHONY : CMakeFiles/net_test.dir/test_epoll.cpp.o.provides

CMakeFiles/net_test.dir/test_epoll.cpp.o.provides.build: CMakeFiles/net_test.dir/test_epoll.cpp.o

CMakeFiles/net_test.dir/test_main.cpp.o: CMakeFiles/net_test.dir/flags.make
CMakeFiles/net_test.dir/test_main.cpp.o: test_main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zodiac/git/net_test/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/net_test.dir/test_main.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/net_test.dir/test_main.cpp.o -c /home/zodiac/git/net_test/test_main.cpp

CMakeFiles/net_test.dir/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_test.dir/test_main.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zodiac/git/net_test/test_main.cpp > CMakeFiles/net_test.dir/test_main.cpp.i

CMakeFiles/net_test.dir/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_test.dir/test_main.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zodiac/git/net_test/test_main.cpp -o CMakeFiles/net_test.dir/test_main.cpp.s

CMakeFiles/net_test.dir/test_main.cpp.o.requires:
.PHONY : CMakeFiles/net_test.dir/test_main.cpp.o.requires

CMakeFiles/net_test.dir/test_main.cpp.o.provides: CMakeFiles/net_test.dir/test_main.cpp.o.requires
	$(MAKE) -f CMakeFiles/net_test.dir/build.make CMakeFiles/net_test.dir/test_main.cpp.o.provides.build
.PHONY : CMakeFiles/net_test.dir/test_main.cpp.o.provides

CMakeFiles/net_test.dir/test_main.cpp.o.provides.build: CMakeFiles/net_test.dir/test_main.cpp.o

CMakeFiles/net_test.dir/test_poll.cpp.o: CMakeFiles/net_test.dir/flags.make
CMakeFiles/net_test.dir/test_poll.cpp.o: test_poll.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/zodiac/git/net_test/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/net_test.dir/test_poll.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/net_test.dir/test_poll.cpp.o -c /home/zodiac/git/net_test/test_poll.cpp

CMakeFiles/net_test.dir/test_poll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net_test.dir/test_poll.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/zodiac/git/net_test/test_poll.cpp > CMakeFiles/net_test.dir/test_poll.cpp.i

CMakeFiles/net_test.dir/test_poll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net_test.dir/test_poll.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/zodiac/git/net_test/test_poll.cpp -o CMakeFiles/net_test.dir/test_poll.cpp.s

CMakeFiles/net_test.dir/test_poll.cpp.o.requires:
.PHONY : CMakeFiles/net_test.dir/test_poll.cpp.o.requires

CMakeFiles/net_test.dir/test_poll.cpp.o.provides: CMakeFiles/net_test.dir/test_poll.cpp.o.requires
	$(MAKE) -f CMakeFiles/net_test.dir/build.make CMakeFiles/net_test.dir/test_poll.cpp.o.provides.build
.PHONY : CMakeFiles/net_test.dir/test_poll.cpp.o.provides

CMakeFiles/net_test.dir/test_poll.cpp.o.provides.build: CMakeFiles/net_test.dir/test_poll.cpp.o

# Object files for target net_test
net_test_OBJECTS = \
"CMakeFiles/net_test.dir/test_echo.cpp.o" \
"CMakeFiles/net_test.dir/test_epoll.cpp.o" \
"CMakeFiles/net_test.dir/test_main.cpp.o" \
"CMakeFiles/net_test.dir/test_poll.cpp.o"

# External object files for target net_test
net_test_EXTERNAL_OBJECTS =

net_test: CMakeFiles/net_test.dir/test_echo.cpp.o
net_test: CMakeFiles/net_test.dir/test_epoll.cpp.o
net_test: CMakeFiles/net_test.dir/test_main.cpp.o
net_test: CMakeFiles/net_test.dir/test_poll.cpp.o
net_test: CMakeFiles/net_test.dir/build.make
net_test: CMakeFiles/net_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable net_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/net_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/net_test.dir/build: net_test
.PHONY : CMakeFiles/net_test.dir/build

CMakeFiles/net_test.dir/requires: CMakeFiles/net_test.dir/test_echo.cpp.o.requires
CMakeFiles/net_test.dir/requires: CMakeFiles/net_test.dir/test_epoll.cpp.o.requires
CMakeFiles/net_test.dir/requires: CMakeFiles/net_test.dir/test_main.cpp.o.requires
CMakeFiles/net_test.dir/requires: CMakeFiles/net_test.dir/test_poll.cpp.o.requires
.PHONY : CMakeFiles/net_test.dir/requires

CMakeFiles/net_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/net_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/net_test.dir/clean

CMakeFiles/net_test.dir/depend:
	cd /home/zodiac/git/net_test && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zodiac/git/net_test /home/zodiac/git/net_test /home/zodiac/git/net_test /home/zodiac/git/net_test /home/zodiac/git/net_test/CMakeFiles/net_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/net_test.dir/depend


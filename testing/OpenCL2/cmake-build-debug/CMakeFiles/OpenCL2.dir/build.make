# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Studium\Masterarbeit\MA-FrameworkLatency\pixel_reader_wip\OpenCL2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Studium\Masterarbeit\MA-FrameworkLatency\pixel_reader_wip\OpenCL2\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/OpenCL2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenCL2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenCL2.dir/flags.make

CMakeFiles/OpenCL2.dir/main.cpp.obj: CMakeFiles/OpenCL2.dir/flags.make
CMakeFiles/OpenCL2.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Studium\Masterarbeit\MA-FrameworkLatency\pixel_reader_wip\OpenCL2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenCL2.dir/main.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\OpenCL2.dir\main.cpp.obj -c D:\Studium\Masterarbeit\MA-FrameworkLatency\pixel_reader_wip\OpenCL2\main.cpp

CMakeFiles/OpenCL2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenCL2.dir/main.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Studium\Masterarbeit\MA-FrameworkLatency\pixel_reader_wip\OpenCL2\main.cpp > CMakeFiles\OpenCL2.dir\main.cpp.i

CMakeFiles/OpenCL2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenCL2.dir/main.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Studium\Masterarbeit\MA-FrameworkLatency\pixel_reader_wip\OpenCL2\main.cpp -o CMakeFiles\OpenCL2.dir\main.cpp.s

# Object files for target OpenCL2
OpenCL2_OBJECTS = \
"CMakeFiles/OpenCL2.dir/main.cpp.obj"

# External object files for target OpenCL2
OpenCL2_EXTERNAL_OBJECTS =

OpenCL2.exe: CMakeFiles/OpenCL2.dir/main.cpp.obj
OpenCL2.exe: CMakeFiles/OpenCL2.dir/build.make
OpenCL2.exe: CMakeFiles/OpenCL2.dir/linklibs.rsp
OpenCL2.exe: CMakeFiles/OpenCL2.dir/objects1.rsp
OpenCL2.exe: CMakeFiles/OpenCL2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Studium\Masterarbeit\MA-FrameworkLatency\pixel_reader_wip\OpenCL2\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable OpenCL2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\OpenCL2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenCL2.dir/build: OpenCL2.exe

.PHONY : CMakeFiles/OpenCL2.dir/build

CMakeFiles/OpenCL2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\OpenCL2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/OpenCL2.dir/clean

CMakeFiles/OpenCL2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Studium\Masterarbeit\MA-FrameworkLatency\pixel_reader_wip\OpenCL2 D:\Studium\Masterarbeit\MA-FrameworkLatency\pixel_reader_wip\OpenCL2 D:\Studium\Masterarbeit\MA-FrameworkLatency\pixel_reader_wip\OpenCL2\cmake-build-debug D:\Studium\Masterarbeit\MA-FrameworkLatency\pixel_reader_wip\OpenCL2\cmake-build-debug D:\Studium\Masterarbeit\MA-FrameworkLatency\pixel_reader_wip\OpenCL2\cmake-build-debug\CMakeFiles\OpenCL2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenCL2.dir/depend

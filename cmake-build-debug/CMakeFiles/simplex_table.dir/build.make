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
CMAKE_SOURCE_DIR = C:\MPSU\Simlex-Table

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\MPSU\Simlex-Table\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/simplex_table.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/simplex_table.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/simplex_table.dir/flags.make

CMakeFiles/simplex_table.dir/main.cpp.obj: CMakeFiles/simplex_table.dir/flags.make
CMakeFiles/simplex_table.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\MPSU\Simlex-Table\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/simplex_table.dir/main.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simplex_table.dir\main.cpp.obj -c C:\MPSU\Simlex-Table\main.cpp

CMakeFiles/simplex_table.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simplex_table.dir/main.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\MPSU\Simlex-Table\main.cpp > CMakeFiles\simplex_table.dir\main.cpp.i

CMakeFiles/simplex_table.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simplex_table.dir/main.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\MPSU\Simlex-Table\main.cpp -o CMakeFiles\simplex_table.dir\main.cpp.s

CMakeFiles/simplex_table.dir/SimplexTable.cpp.obj: CMakeFiles/simplex_table.dir/flags.make
CMakeFiles/simplex_table.dir/SimplexTable.cpp.obj: ../SimplexTable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\MPSU\Simlex-Table\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/simplex_table.dir/SimplexTable.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simplex_table.dir\SimplexTable.cpp.obj -c C:\MPSU\Simlex-Table\SimplexTable.cpp

CMakeFiles/simplex_table.dir/SimplexTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simplex_table.dir/SimplexTable.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\MPSU\Simlex-Table\SimplexTable.cpp > CMakeFiles\simplex_table.dir\SimplexTable.cpp.i

CMakeFiles/simplex_table.dir/SimplexTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simplex_table.dir/SimplexTable.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\MPSU\Simlex-Table\SimplexTable.cpp -o CMakeFiles\simplex_table.dir\SimplexTable.cpp.s

CMakeFiles/simplex_table.dir/Fraction.cpp.obj: CMakeFiles/simplex_table.dir/flags.make
CMakeFiles/simplex_table.dir/Fraction.cpp.obj: ../Fraction.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\MPSU\Simlex-Table\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/simplex_table.dir/Fraction.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\simplex_table.dir\Fraction.cpp.obj -c C:\MPSU\Simlex-Table\Fraction.cpp

CMakeFiles/simplex_table.dir/Fraction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simplex_table.dir/Fraction.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\MPSU\Simlex-Table\Fraction.cpp > CMakeFiles\simplex_table.dir\Fraction.cpp.i

CMakeFiles/simplex_table.dir/Fraction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simplex_table.dir/Fraction.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\MPSU\Simlex-Table\Fraction.cpp -o CMakeFiles\simplex_table.dir\Fraction.cpp.s

# Object files for target simplex_table
simplex_table_OBJECTS = \
"CMakeFiles/simplex_table.dir/main.cpp.obj" \
"CMakeFiles/simplex_table.dir/SimplexTable.cpp.obj" \
"CMakeFiles/simplex_table.dir/Fraction.cpp.obj"

# External object files for target simplex_table
simplex_table_EXTERNAL_OBJECTS =

simplex_table.exe: CMakeFiles/simplex_table.dir/main.cpp.obj
simplex_table.exe: CMakeFiles/simplex_table.dir/SimplexTable.cpp.obj
simplex_table.exe: CMakeFiles/simplex_table.dir/Fraction.cpp.obj
simplex_table.exe: CMakeFiles/simplex_table.dir/build.make
simplex_table.exe: CMakeFiles/simplex_table.dir/linklibs.rsp
simplex_table.exe: CMakeFiles/simplex_table.dir/objects1.rsp
simplex_table.exe: CMakeFiles/simplex_table.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\MPSU\Simlex-Table\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable simplex_table.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\simplex_table.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/simplex_table.dir/build: simplex_table.exe

.PHONY : CMakeFiles/simplex_table.dir/build

CMakeFiles/simplex_table.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\simplex_table.dir\cmake_clean.cmake
.PHONY : CMakeFiles/simplex_table.dir/clean

CMakeFiles/simplex_table.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\MPSU\Simlex-Table C:\MPSU\Simlex-Table C:\MPSU\Simlex-Table\cmake-build-debug C:\MPSU\Simlex-Table\cmake-build-debug C:\MPSU\Simlex-Table\cmake-build-debug\CMakeFiles\simplex_table.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/simplex_table.dir/depend

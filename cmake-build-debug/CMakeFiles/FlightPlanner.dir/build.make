# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/FlightPlanner.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FlightPlanner.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FlightPlanner.dir/flags.make

CMakeFiles/FlightPlanner.dir/main.cpp.obj: CMakeFiles/FlightPlanner.dir/flags.make
CMakeFiles/FlightPlanner.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/FlightPlanner.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FlightPlanner.dir\main.cpp.obj -c C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\main.cpp

CMakeFiles/FlightPlanner.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FlightPlanner.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\main.cpp > CMakeFiles\FlightPlanner.dir\main.cpp.i

CMakeFiles/FlightPlanner.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FlightPlanner.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\main.cpp -o CMakeFiles\FlightPlanner.dir\main.cpp.s

CMakeFiles/FlightPlanner.dir/parser.cpp.obj: CMakeFiles/FlightPlanner.dir/flags.make
CMakeFiles/FlightPlanner.dir/parser.cpp.obj: ../parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/FlightPlanner.dir/parser.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FlightPlanner.dir\parser.cpp.obj -c C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\parser.cpp

CMakeFiles/FlightPlanner.dir/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FlightPlanner.dir/parser.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\parser.cpp > CMakeFiles\FlightPlanner.dir\parser.cpp.i

CMakeFiles/FlightPlanner.dir/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FlightPlanner.dir/parser.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\parser.cpp -o CMakeFiles\FlightPlanner.dir\parser.cpp.s

CMakeFiles/FlightPlanner.dir/porter2_stemmer.cpp.obj: CMakeFiles/FlightPlanner.dir/flags.make
CMakeFiles/FlightPlanner.dir/porter2_stemmer.cpp.obj: ../porter2_stemmer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/FlightPlanner.dir/porter2_stemmer.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FlightPlanner.dir\porter2_stemmer.cpp.obj -c C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\porter2_stemmer.cpp

CMakeFiles/FlightPlanner.dir/porter2_stemmer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FlightPlanner.dir/porter2_stemmer.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\porter2_stemmer.cpp > CMakeFiles\FlightPlanner.dir\porter2_stemmer.cpp.i

CMakeFiles/FlightPlanner.dir/porter2_stemmer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FlightPlanner.dir/porter2_stemmer.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\porter2_stemmer.cpp -o CMakeFiles\FlightPlanner.dir\porter2_stemmer.cpp.s

CMakeFiles/FlightPlanner.dir/wordobject.cpp.obj: CMakeFiles/FlightPlanner.dir/flags.make
CMakeFiles/FlightPlanner.dir/wordobject.cpp.obj: ../wordobject.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/FlightPlanner.dir/wordobject.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\FlightPlanner.dir\wordobject.cpp.obj -c C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\wordobject.cpp

CMakeFiles/FlightPlanner.dir/wordobject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/FlightPlanner.dir/wordobject.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\wordobject.cpp > CMakeFiles\FlightPlanner.dir\wordobject.cpp.i

CMakeFiles/FlightPlanner.dir/wordobject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/FlightPlanner.dir/wordobject.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\wordobject.cpp -o CMakeFiles\FlightPlanner.dir\wordobject.cpp.s

# Object files for target FlightPlanner
FlightPlanner_OBJECTS = \
"CMakeFiles/FlightPlanner.dir/main.cpp.obj" \
"CMakeFiles/FlightPlanner.dir/parser.cpp.obj" \
"CMakeFiles/FlightPlanner.dir/porter2_stemmer.cpp.obj" \
"CMakeFiles/FlightPlanner.dir/wordobject.cpp.obj"

# External object files for target FlightPlanner
FlightPlanner_EXTERNAL_OBJECTS =

FlightPlanner.exe: CMakeFiles/FlightPlanner.dir/main.cpp.obj
FlightPlanner.exe: CMakeFiles/FlightPlanner.dir/parser.cpp.obj
FlightPlanner.exe: CMakeFiles/FlightPlanner.dir/porter2_stemmer.cpp.obj
FlightPlanner.exe: CMakeFiles/FlightPlanner.dir/wordobject.cpp.obj
FlightPlanner.exe: CMakeFiles/FlightPlanner.dir/build.make
FlightPlanner.exe: CMakeFiles/FlightPlanner.dir/linklibs.rsp
FlightPlanner.exe: CMakeFiles/FlightPlanner.dir/objects1.rsp
FlightPlanner.exe: CMakeFiles/FlightPlanner.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable FlightPlanner.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\FlightPlanner.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FlightPlanner.dir/build: FlightPlanner.exe

.PHONY : CMakeFiles/FlightPlanner.dir/build

CMakeFiles/FlightPlanner.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\FlightPlanner.dir\cmake_clean.cmake
.PHONY : CMakeFiles/FlightPlanner.dir/clean

CMakeFiles/FlightPlanner.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\cmake-build-debug C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\cmake-build-debug C:\Users\Mcuzz\OneDrive\Documents\GitHub\CS2341-SearchEngine-MikeCuzzo\cmake-build-debug\CMakeFiles\FlightPlanner.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FlightPlanner.dir/depend


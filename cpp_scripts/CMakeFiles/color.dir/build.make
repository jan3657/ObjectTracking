# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.24.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.24.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jandrole/projects/ObjectTracking/cpp_scripts

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jandrole/projects/ObjectTracking/cpp_scripts

# Include any dependencies generated for this target.
include CMakeFiles/color.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/color.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/color.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/color.dir/flags.make

CMakeFiles/color.dir/colotracker.cpp.o: CMakeFiles/color.dir/flags.make
CMakeFiles/color.dir/colotracker.cpp.o: colotracker.cpp
CMakeFiles/color.dir/colotracker.cpp.o: CMakeFiles/color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jandrole/projects/ObjectTracking/cpp_scripts/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/color.dir/colotracker.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/color.dir/colotracker.cpp.o -MF CMakeFiles/color.dir/colotracker.cpp.o.d -o CMakeFiles/color.dir/colotracker.cpp.o -c /Users/jandrole/projects/ObjectTracking/cpp_scripts/colotracker.cpp

CMakeFiles/color.dir/colotracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/color.dir/colotracker.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jandrole/projects/ObjectTracking/cpp_scripts/colotracker.cpp > CMakeFiles/color.dir/colotracker.cpp.i

CMakeFiles/color.dir/colotracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/color.dir/colotracker.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jandrole/projects/ObjectTracking/cpp_scripts/colotracker.cpp -o CMakeFiles/color.dir/colotracker.cpp.s

CMakeFiles/color.dir/histogram.cpp.o: CMakeFiles/color.dir/flags.make
CMakeFiles/color.dir/histogram.cpp.o: histogram.cpp
CMakeFiles/color.dir/histogram.cpp.o: CMakeFiles/color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jandrole/projects/ObjectTracking/cpp_scripts/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/color.dir/histogram.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/color.dir/histogram.cpp.o -MF CMakeFiles/color.dir/histogram.cpp.o.d -o CMakeFiles/color.dir/histogram.cpp.o -c /Users/jandrole/projects/ObjectTracking/cpp_scripts/histogram.cpp

CMakeFiles/color.dir/histogram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/color.dir/histogram.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jandrole/projects/ObjectTracking/cpp_scripts/histogram.cpp > CMakeFiles/color.dir/histogram.cpp.i

CMakeFiles/color.dir/histogram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/color.dir/histogram.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jandrole/projects/ObjectTracking/cpp_scripts/histogram.cpp -o CMakeFiles/color.dir/histogram.cpp.s

CMakeFiles/color.dir/region.cpp.o: CMakeFiles/color.dir/flags.make
CMakeFiles/color.dir/region.cpp.o: region.cpp
CMakeFiles/color.dir/region.cpp.o: CMakeFiles/color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jandrole/projects/ObjectTracking/cpp_scripts/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/color.dir/region.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/color.dir/region.cpp.o -MF CMakeFiles/color.dir/region.cpp.o.d -o CMakeFiles/color.dir/region.cpp.o -c /Users/jandrole/projects/ObjectTracking/cpp_scripts/region.cpp

CMakeFiles/color.dir/region.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/color.dir/region.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jandrole/projects/ObjectTracking/cpp_scripts/region.cpp > CMakeFiles/color.dir/region.cpp.i

CMakeFiles/color.dir/region.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/color.dir/region.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jandrole/projects/ObjectTracking/cpp_scripts/region.cpp -o CMakeFiles/color.dir/region.cpp.s

CMakeFiles/color.dir/MeanShiftImp.cpp.o: CMakeFiles/color.dir/flags.make
CMakeFiles/color.dir/MeanShiftImp.cpp.o: MeanShiftImp.cpp
CMakeFiles/color.dir/MeanShiftImp.cpp.o: CMakeFiles/color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jandrole/projects/ObjectTracking/cpp_scripts/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/color.dir/MeanShiftImp.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/color.dir/MeanShiftImp.cpp.o -MF CMakeFiles/color.dir/MeanShiftImp.cpp.o.d -o CMakeFiles/color.dir/MeanShiftImp.cpp.o -c /Users/jandrole/projects/ObjectTracking/cpp_scripts/MeanShiftImp.cpp

CMakeFiles/color.dir/MeanShiftImp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/color.dir/MeanShiftImp.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jandrole/projects/ObjectTracking/cpp_scripts/MeanShiftImp.cpp > CMakeFiles/color.dir/MeanShiftImp.cpp.i

CMakeFiles/color.dir/MeanShiftImp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/color.dir/MeanShiftImp.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jandrole/projects/ObjectTracking/cpp_scripts/MeanShiftImp.cpp -o CMakeFiles/color.dir/MeanShiftImp.cpp.s

CMakeFiles/color.dir/CamShiftImp.cpp.o: CMakeFiles/color.dir/flags.make
CMakeFiles/color.dir/CamShiftImp.cpp.o: CamShiftImp.cpp
CMakeFiles/color.dir/CamShiftImp.cpp.o: CMakeFiles/color.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jandrole/projects/ObjectTracking/cpp_scripts/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/color.dir/CamShiftImp.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/color.dir/CamShiftImp.cpp.o -MF CMakeFiles/color.dir/CamShiftImp.cpp.o.d -o CMakeFiles/color.dir/CamShiftImp.cpp.o -c /Users/jandrole/projects/ObjectTracking/cpp_scripts/CamShiftImp.cpp

CMakeFiles/color.dir/CamShiftImp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/color.dir/CamShiftImp.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jandrole/projects/ObjectTracking/cpp_scripts/CamShiftImp.cpp > CMakeFiles/color.dir/CamShiftImp.cpp.i

CMakeFiles/color.dir/CamShiftImp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/color.dir/CamShiftImp.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jandrole/projects/ObjectTracking/cpp_scripts/CamShiftImp.cpp -o CMakeFiles/color.dir/CamShiftImp.cpp.s

# Object files for target color
color_OBJECTS = \
"CMakeFiles/color.dir/colotracker.cpp.o" \
"CMakeFiles/color.dir/histogram.cpp.o" \
"CMakeFiles/color.dir/region.cpp.o" \
"CMakeFiles/color.dir/MeanShiftImp.cpp.o" \
"CMakeFiles/color.dir/CamShiftImp.cpp.o"

# External object files for target color
color_EXTERNAL_OBJECTS =

libcolor.a: CMakeFiles/color.dir/colotracker.cpp.o
libcolor.a: CMakeFiles/color.dir/histogram.cpp.o
libcolor.a: CMakeFiles/color.dir/region.cpp.o
libcolor.a: CMakeFiles/color.dir/MeanShiftImp.cpp.o
libcolor.a: CMakeFiles/color.dir/CamShiftImp.cpp.o
libcolor.a: CMakeFiles/color.dir/build.make
libcolor.a: CMakeFiles/color.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jandrole/projects/ObjectTracking/cpp_scripts/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libcolor.a"
	$(CMAKE_COMMAND) -P CMakeFiles/color.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/color.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/color.dir/build: libcolor.a
.PHONY : CMakeFiles/color.dir/build

CMakeFiles/color.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/color.dir/cmake_clean.cmake
.PHONY : CMakeFiles/color.dir/clean

CMakeFiles/color.dir/depend:
	cd /Users/jandrole/projects/ObjectTracking/cpp_scripts && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jandrole/projects/ObjectTracking/cpp_scripts /Users/jandrole/projects/ObjectTracking/cpp_scripts /Users/jandrole/projects/ObjectTracking/cpp_scripts /Users/jandrole/projects/ObjectTracking/cpp_scripts /Users/jandrole/projects/ObjectTracking/cpp_scripts/CMakeFiles/color.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/color.dir/depend


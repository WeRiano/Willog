# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\WeRiano\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\WeRiano\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\211.7442.42\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Dev\Cpp\CLion\willog

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Dev\Cpp\CLion\willog\bin\debug

# Include any dependencies generated for this target.
include src\willog\CMakeFiles\Core.dir\depend.make

# Include the progress variables for this target.
include src\willog\CMakeFiles\Core.dir\progress.make

# Include the compile flags for this target's objects.
include src\willog\CMakeFiles\Core.dir\flags.make

# Object files for target Core
Core_OBJECTS =

# External object files for target Core
Core_EXTERNAL_OBJECTS =

src\willog\Core.lib: src\willog\CMakeFiles\Core.dir\build.make
src\willog\Core.lib: src\willog\CMakeFiles\Core.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Dev\Cpp\CLion\willog\bin\debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking CXX static library Core.lib"
	cd C:\Dev\Cpp\CLion\willog\bin\debug\src\willog
	$(CMAKE_COMMAND) -P CMakeFiles\Core.dir\cmake_clean_target.cmake
	cd C:\Dev\Cpp\CLion\willog\bin\debug
	cd C:\Dev\Cpp\CLion\willog\bin\debug\src\willog
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1426~1.288\bin\Hostx64\x64\lib.exe /nologo /machine:x64 /out:Core.lib @CMakeFiles\Core.dir\objects1.rsp 
	cd C:\Dev\Cpp\CLion\willog\bin\debug

# Rule to build all files generated by this target.
src\willog\CMakeFiles\Core.dir\build: src\willog\Core.lib

.PHONY : src\willog\CMakeFiles\Core.dir\build

src\willog\CMakeFiles\Core.dir\clean:
	cd C:\Dev\Cpp\CLion\willog\bin\debug\src\willog
	$(CMAKE_COMMAND) -P CMakeFiles\Core.dir\cmake_clean.cmake
	cd C:\Dev\Cpp\CLion\willog\bin\debug
.PHONY : src\willog\CMakeFiles\Core.dir\clean

src\willog\CMakeFiles\Core.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Dev\Cpp\CLion\willog C:\Dev\Cpp\CLion\willog\src\willog C:\Dev\Cpp\CLion\willog\bin\debug C:\Dev\Cpp\CLion\willog\bin\debug\src\willog C:\Dev\Cpp\CLion\willog\bin\debug\src\willog\CMakeFiles\core.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src\willog\CMakeFiles\Core.dir\depend

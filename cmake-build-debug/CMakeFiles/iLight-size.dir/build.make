# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.3.4\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.3.4\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Users\Ju'\Google Drive\Works\iLight"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Users\Ju'\Google Drive\Works\iLight\cmake-build-debug"

# Utility rule file for iLight-size.

# Include the progress variables for this target.
include CMakeFiles/iLight-size.dir/progress.make

CMakeFiles/iLight-size: iLight.elf
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="D:\Users\Ju'\Google Drive\Works\iLight\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Calculating iLight image size"
	"C:\Program Files\JetBrains\CLion 2017.3.4\bin\cmake\bin\cmake.exe" "-DFIRMWARE_IMAGE=D:/Users/Ju'/Google Drive/Works/iLight/cmake-build-debug/iLight.elf" -DMCU=atmega328p "-DEEPROM_IMAGE=D:/Users/Ju'/Google Drive/Works/iLight/cmake-build-debug/iLight.eep" -P "D:/Users/Ju'/Google Drive/Works/iLight/cmake-build-debug/CMakeFiles/FirmwareSize.cmake"

iLight-size: CMakeFiles/iLight-size
iLight-size: CMakeFiles/iLight-size.dir/build.make

.PHONY : iLight-size

# Rule to build all files generated by this target.
CMakeFiles/iLight-size.dir/build: iLight-size

.PHONY : CMakeFiles/iLight-size.dir/build

CMakeFiles/iLight-size.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\iLight-size.dir\cmake_clean.cmake
.PHONY : CMakeFiles/iLight-size.dir/clean

CMakeFiles/iLight-size.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Users\Ju'\Google Drive\Works\iLight" "D:\Users\Ju'\Google Drive\Works\iLight" "D:\Users\Ju'\Google Drive\Works\iLight\cmake-build-debug" "D:\Users\Ju'\Google Drive\Works\iLight\cmake-build-debug" "D:\Users\Ju'\Google Drive\Works\iLight\cmake-build-debug\CMakeFiles\iLight-size.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/iLight-size.dir/depend


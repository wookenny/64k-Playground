# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/combi/gellert/local/SoftwareProjekte/64k-Playground

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/combi/gellert/local/SoftwareProjekte/64k-Playground

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /homes/combi/gellert/local/SoftwareProjekte/64k-Playground/CMakeFiles /homes/combi/gellert/local/SoftwareProjekte/64k-Playground/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /homes/combi/gellert/local/SoftwareProjekte/64k-Playground/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Intro

# Build rule for target.
Intro: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Intro
.PHONY : Intro

# fast build rule for target.
Intro/fast:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/build
.PHONY : Intro/fast

ApplicationWindow.o: ApplicationWindow.cpp.o
.PHONY : ApplicationWindow.o

# target to build an object file
ApplicationWindow.cpp.o:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/ApplicationWindow.cpp.o
.PHONY : ApplicationWindow.cpp.o

ApplicationWindow.i: ApplicationWindow.cpp.i
.PHONY : ApplicationWindow.i

# target to preprocess a source file
ApplicationWindow.cpp.i:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/ApplicationWindow.cpp.i
.PHONY : ApplicationWindow.cpp.i

ApplicationWindow.s: ApplicationWindow.cpp.s
.PHONY : ApplicationWindow.s

# target to generate assembly for a file
ApplicationWindow.cpp.s:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/ApplicationWindow.cpp.s
.PHONY : ApplicationWindow.cpp.s

Color.o: Color.cpp.o
.PHONY : Color.o

# target to build an object file
Color.cpp.o:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/Color.cpp.o
.PHONY : Color.cpp.o

Color.i: Color.cpp.i
.PHONY : Color.i

# target to preprocess a source file
Color.cpp.i:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/Color.cpp.i
.PHONY : Color.cpp.i

Color.s: Color.cpp.s
.PHONY : Color.s

# target to generate assembly for a file
Color.cpp.s:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/Color.cpp.s
.PHONY : Color.cpp.s

Image.o: Image.cpp.o
.PHONY : Image.o

# target to build an object file
Image.cpp.o:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/Image.cpp.o
.PHONY : Image.cpp.o

Image.i: Image.cpp.i
.PHONY : Image.i

# target to preprocess a source file
Image.cpp.i:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/Image.cpp.i
.PHONY : Image.cpp.i

Image.s: Image.cpp.s
.PHONY : Image.s

# target to generate assembly for a file
Image.cpp.s:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/Image.cpp.s
.PHONY : Image.cpp.s

ImageStack.o: ImageStack.cpp.o
.PHONY : ImageStack.o

# target to build an object file
ImageStack.cpp.o:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/ImageStack.cpp.o
.PHONY : ImageStack.cpp.o

ImageStack.i: ImageStack.cpp.i
.PHONY : ImageStack.i

# target to preprocess a source file
ImageStack.cpp.i:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/ImageStack.cpp.i
.PHONY : ImageStack.cpp.i

ImageStack.s: ImageStack.cpp.s
.PHONY : ImageStack.s

# target to generate assembly for a file
ImageStack.cpp.s:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/ImageStack.cpp.s
.PHONY : ImageStack.cpp.s

Main.o: Main.cpp.o
.PHONY : Main.o

# target to build an object file
Main.cpp.o:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/Main.cpp.o
.PHONY : Main.cpp.o

Main.i: Main.cpp.i
.PHONY : Main.i

# target to preprocess a source file
Main.cpp.i:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/Main.cpp.i
.PHONY : Main.cpp.i

Main.s: Main.cpp.s
.PHONY : Main.s

# target to generate assembly for a file
Main.cpp.s:
	$(MAKE) -f CMakeFiles/Intro.dir/build.make CMakeFiles/Intro.dir/Main.cpp.s
.PHONY : Main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... Intro"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... ApplicationWindow.o"
	@echo "... ApplicationWindow.i"
	@echo "... ApplicationWindow.s"
	@echo "... Color.o"
	@echo "... Color.i"
	@echo "... Color.s"
	@echo "... Image.o"
	@echo "... Image.i"
	@echo "... Image.s"
	@echo "... ImageStack.o"
	@echo "... ImageStack.i"
	@echo "... ImageStack.s"
	@echo "... Main.o"
	@echo "... Main.i"
	@echo "... Main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

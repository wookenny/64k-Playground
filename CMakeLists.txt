cmake_minimum_required(VERSION 2.6)

#project name
project(Intro)

#specific compiler settings
#-Os = optimze for small size
#-s = strip
set(CMAKE_CXX_FLAGS "-Os -g -pedantic -Wall -std=c++0x  -lpng -lm -lGL -lGLU -lSDL  ")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
# collect all sources (copy from 'ls -1 *.h *.cpp')
SET(IntroSources
Color.cpp
Color.h
Image.cpp
Image.h
ImageStack.cpp
ImageStack.h
Main.cpp
ApplicationWindow.cpp
ApplicationWindow.h
)

# display status message for important variables
MESSAGE( STATUS )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS "building with flags: " )
MESSAGE( STATUS "${CMAKE_CXX_FLAGS}" )
MESSAGE( STATUS "-------------------------------------------------------------------------------" )
MESSAGE( STATUS )

#define executable
ADD_EXECUTABLE(Intro ${IntroSources} )

#afterwards:
# strip Intro && upx -9 Intro
#ADD_CUSTOM_COMMAND(TARGET Intro
#		   POST_BUILD
#		   COMMAND du -bh Intro && upx -9 Intro > /dev/null && du -bh Intro)


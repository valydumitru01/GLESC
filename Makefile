
RELEASE_MACRO	:=-D RELEASE
DEBUG_MACRO		:=-D DEBUG
OS_MACRO		:=-D

#bin folder: binaries and executables
BIN_DIR     	:=bin

#src folder: include folder of internal headers
INCLUDE_DIR     	:=include

#lib folder: static libraries to link
LIB_STATIC_DIR	:=lib/lib

#include folder: headers of external libraries
LIB_INCLUDE_DIR :=lib/include

#Include folders, where to search for headers
INCLUDE 		:=-I$(INCLUDE_DIR) -I$(LIB_INCLUDE_DIR)

#Lib folders, where to search for the static libraries
LIB     		:=-L$(LIB_STATIC_DIR)

#Check the OS
ifeq ($(OS),Windows_NT)

# the compiler: gcc for C program, define as g++ for C++
CC	:= g++

# The windows command for delete
DEL := del

# The windows slash for directory
SLASH := "\"

# Overriding to empty, indicating that we dont need wine, unlike in linux
WINE := 

# Creating own macro for windows
OS_MACRO +=__WINDOWS__

# Source files for cpp files in tbe project, we only search for them up to 4 depth. Every /* is a new depth.
# To add a depth add another item to the list with another /*
SOURCES := $(wildcard *.cpp */*.cpp */*/*.cpp */*/*/*.cpp)

# better?
# SOURCES := $(shell find . -name '*.cpp' -type f)

# compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
CFLAGS:= -g -Wall

# libraries to link to the project
LIBRARIES   :=-lmingw32 -lSDL2main -lSDL2 -lSDL2_net -lSDL2_mixer -lmingw32 -lopengl32 -lglew32 -lglu32 -lSDL2main -lSDL2 -lSDL2_image 

# the build target executable
EXECUTABLE  := game

else
# CURRENTLY NOT WORKING
# Linux compiler for windows executables (64 bits)
CC	:= x86_64-w64-mingw32-g++
# Linux command for delete (rm -f)
DEL := $(RM)
# Linux slash for directory
SLASH := '/'
# Wine, program for executing windows apps .exe
WINE := wine
OS_MACRO +=__LINUX__
SOURCES := $(shell dir . -r *.cpp)
endif



#---------------------------------------------
# All builds and runs
all: build-and-run

#---------------------------------------------
# Show source files for debugging purposes
showfiles:
	@echo $(SOURCES)


#---------------------------------------------
# Builds the executable game
build:
	echo "Building..."
	$(CC) $(CFLAGS)  $(INCLUDE) $(LIB) $(OS_MACRO) $(DEBUG_MACRO) -o $(BIN_DIR)/$(EXECUTABLE) $(SOURCES) $(LIBRARIES) 


#---------------------------------------------
# Run the game 
run:
	echo "Executing..."
	$(WINE) $(BIN_DIR)/$(EXECUTABLE)


#---------------------------------------------
# Build then run the game
build-and-run: clean build run


#---------------------------------------------
# Remove the executable
clean:
	echo "Clearing..."
	$(DEL) bin$(SLASH)$(EXECUTABLE).exe




############################################
# ------------FOLDER LOCATIONS-------------#
# -----------------------------------------#
# -----------------------------------------#

#bin folder: binaries and executables
BIN_DIR     	:= bin
#src folder: Source code, implementations
SRC_DIR 		:= src
#src folder: include folder of internal headers
INCLUDE_DIR     := include
#lib folder: static libraries to link
LIB_STATIC_DIR	:=lib/lib
#include folder: headers of external libraries
LIB_INCLUDE_DIR :=lib/include

# Location of source files
# Searches recursively
SRC_FILES  		:= $(shell dir /s /b $(SRC_DIR)\*.cpp)
# Name of executable file
EXE_FILE  := game

# -----------------------------------------#
# -----------------------------------------#
############################################


############################################
# ------------MACRO DEFINITIONS------------#
# -----------------------------------------#
# -----------------------------------------#

MACROS :=
OS_MACRO :=

# Operating system macro definition
# Will also be used throughout the makefile
ifeq ($(OS),Windows_NT)
	OS_MACRO:= __WINDOWS__
else
	UNAME := $(shell uname)
	ifeq ($(UNAME),Linux)
		OS_MACRO:= __LINUX__
	else ifeq ($(UNAME), Darwin)
		OS_MACRO:= __MAC__
	endif
endif

MACROS 	+= -D $(OS_MACRO)
MACROS	+= -D RELEASE
MACROS	+= -D DEBUG

# -----------------------------------------#
# -----------------------------------------#
############################################


############################################
# ----------------COMPILER-----------------#
# -----------------------------------------#
# -----------------------------------------#
ifeq ($(OS_MACRO),__WINDOWS__)
	CXX:=g++
else ifeq ($(OS_MACRO),__LINUX__)
	CXX	:= x86_64-w64-mingw32-g++
else ifeq ($(OS_MACRO),__MAC__)
	# TODO
endif

# -----------------------------------------#
# -----------------------------------------#
############################################





############################################
# ------------------FLAGS------------------#
# -----------------------------------------#
# -----------------------------------------#

# C++ flags
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -O3 -g
# Include flags
INCFLAGS:= -I$(INCLUDE_DIR) -I$(LIB_INCLUDE_DIR)
# Linker flags
LDFLAGS:= -L$(LIB_STATIC_DIR)
# Linked libraries flags
LDLIBS:=-lmingw32
LDLIBS+=-lSDL2 -lSDL2main -lSDL2main -lSDL2_net -lSDL2_mixer -lSDL2_image
LDLIBS+=-lopengl32 -lglew32 -lglu32
# Object flags
OBJFLAGS= -o $(BIN_DIR)/$(EXE_FILE)

# -----------------------------------------#
# -----------------------------------------#
############################################


############################################
# ------------------EXECUTE----------------#

# Wine is needed to execute .exe in linux
WINE := wine

############################################


############################################
# ------------------CLEAN------------------#
# -----------------------------------------#

ifeq ($(OS_MACRO),__WINDOWS__)
# Windows uses backwards slash '\'
RM_EXE := del $(BIN_DIR)\$(EXE_FILE)
else ifeq ($(OS_MACRO),__LINUX__)
RM_EXE := rm -f $(BIN_DIR)/$(EXE_FILE)
else ifeq ($(OS_MACRO),__MAC__)
# TODO
endif

# -----------------------------------------#
############################################




# Phony targets, do not output files
.PHONY: clean run


#---------------------------------------------
# All builds and runs
all: build

#---------------------------------------------
# Builds the executable game
build:
	echo "Building..."
	$(CXX) $(CXXFLAGS) $(INCFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJFLAGS) $(SRC_FILES)


#---------------------------------------------
# Run the game
run:
	echo "Executing..."
	$(WINE) $(BIN_DIR)\$(EXE_FILE)


#---------------------------------------------
# Build then run the game
build-and-run: clean build run


#---------------------------------------------
# Remove the executable
clean:
	echo "Clearing..."
	$(RM_EXE)
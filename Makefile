


############################################
# ------------FOLDER LOCATIONS-------------#
# -----------------------------------------#
# -----------------------------------------#

#bin folder: binaries and executables
BIN_DIR     	:= bin

#res-mng folders
#paths need to use backslashes as they are going to be used for windows commands
#src folder: Source code, implementations
SRC_DIR 		:= src
#src lib folder: Source code of external libraries
LIB_SRC_DIR		:= lib\src

#src folder: include folder of internal headers
INCLUDE_DIR     := include
#lib folder: static libraries to link
LIB_STATIC_DIR	:=lib/lib
#include folder: headers of external libraries
LIB_INCLUDE_DIR :=lib/include

# Location of source files
# Searches recursively
SRC_FILES  		:= $(shell dir /s /b $(SRC_DIR)\*.cpp)
SRC_FILES 		+= $(shell dir /s /b $(LIB_SRC_DIR)\*.cpp)
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
# Add the operating system macro to the list of macros
MACROS 	+= -D $(OS_MACRO)
# Add the macro for Glew static linking
# It is needed to link glew32s.lib
MACROS	+= -DGLEW_STATIC


# Define the release macro
MACRO_RELEASE	+= -D RELEASE
# Define the debug macro
MACRO_DEBUG	+= -D DEBUG

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
	CXX := g++
endif

# -----------------------------------------#
# -----------------------------------------#
############################################





############################################
# ------------------FLAGS------------------#
# -----------------------------------------#
# -----------------------------------------#

# C++ flags
CXXFLAGS_RELEASE := -O3
CXXFLAGS_DEBUG := -O0
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -g -Wno-unused-function
# Include flags
INCFLAGS:= -I$(INCLUDE_DIR) -I$(LIB_INCLUDE_DIR)
# Linker flags
LDFLAGS:= -L$(LIB_STATIC_DIR)
# Linked libraries flags
LDLIBS:=-lmingw32
LDLIBS+=-lSDL2main -lSDL2 -lSDL2_net -lSDL2_mixer -lSDL2_image
LDLIBS+=-lglew32s -lopengl32 -lglu32

# Object flags
OBJFLAGS= -o $(BIN_DIR)/$(EXE_FILE)

# -----------------------------------------#
# -----------------------------------------#
############################################


############################################
# ------------------EXECUTE----------------#
ifeq ($(OS_MACRO),__WINDOWS__)
WINE :=
else ifeq ($(OS_MACRO),__LINUX__)
# Wine is needed to execute .exe in linux
WINE := wine
else ifeq ($(OS_MACRO),__MAC__)

endif

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
RM_EXE := rm -f $(BIN_DIR)/$(EXE_FILE)
endif

# -----------------------------------------#
############################################




# Phony targets, do not output files
.PHONY: clean run build-and-run


#---------------------------------------------
# All builds and runs
all: build-debug run


# When the GNU linker sees a library, it discards all symbols that it doesn't need.
# That's why, you need to specify the libraries in the order that they depend on each other and
# at the end of the command.

#---------------------------------------------
# Builds the executable game in release mode
build-release:
	echo "Building..."
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) $(CXXFLAGS_RELEASE) $(MACROS) $(MACRO_RELEASE) $(INCFLAGS) $(SRC_FILES) $(LDFLAGS) $(LDLIBS)

#---------------------------------------------
# Builds the executable game in release mode
build-debug:
	echo "Building..."
	$(CXX) $(CXXFLAGS) $(OBJFLAGS) $(CXXFLAGS_DEBUG) $(MACROS) $(MACRO_DEBUG) $(INCFLAGS) $(SRC_FILES) $(LDFLAGS) $(LDLIBS)

#---------------------------------------------
# Run the game
run:
	echo "Executing..."
	$(WINE) $(BIN_DIR)\$(EXE_FILE)


#---------------------------------------------
# Build then run the game
build-run-release:
	clean build-release run


# Remove the executable
clean:
	echo "Clearing..."
	$(RM_EXE)

# the compiler: gcc for C program, define as g++ for C++
CC	:= g++

# compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
CFLAGS:= -g -Wall

BIN     := bin
SRC     := src
INCLUDE := include
LIB     := lib
# libraries to link to the project
LIBRARIES   := -lmingw32 -lSDL2main -lSDL2  -lmingw32 -lopengl32 -lglew32 -lglu32 -lSDL2main -lSDL2 -lSDL2_image
# the build target executable
EXECUTABLE  := game


all: build

# Builds the executable game
build:
	@echo "Building..."
	$(CC) $(CFLAGS) -I $(INCLUDE) -L $(LIB) -o $(BIN)/$(EXECUTABLE) $(SRC)/*.cpp $(LIBRARIES)

# Run the game
run: clean all
	@echo "Executing..."
	$(BIN)/$(EXECUTABLE)

# Remove the executable
clean:
	@echo "Clearing..."
	del bin\$(EXECUTABLE).exe

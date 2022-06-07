# create the game executable

#g++ -I ./src/include -L ./src/lib -o ./Builds/Win_Build/engine main.cpp -lmingw32 -lSDL2main -lSDL2  -lmingw32 -lopengl32 -lglew32 -lglu32 -lSDL2main -lSDL2 -lSDL2_image --verbose

# the compiler: gcc for C program, define as g++ for C++
CC	:= g++

# compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
CFLAGS:= -g -Wall

BIN     := ./bin
SRC     := ./src
INCLUDE := ./include
LIB     := ./lib
LIBRARIES   := -lmingw32 -lSDL2main -lSDL2  -lmingw32 -lopengl32 -lglew32 -lglu32 -lSDL2main -lSDL2 -lSDL2_image
# the build target executable
EXECUTABLE  := ./bin/engine


all: executable

executable:
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -L $(LIB) -o $(EXECUTABLE) $(SRC)/*.cpp $(LIBRARIES)


run: 
	./$(EXECUTABLE)

clean:
	$(RM) $(EXECUTABLE)

all:
	g++ -I ./src/include -L ./src/lib -o ./Builds/Win_Build/engine main.cpp Game.cpp -lmingw32 -lSDL2main -lSDL2  -lmingw32 -lopengl32 -lglew32 -lglu32 -lSDL2main -lSDL2 -lSDL2_image --verbose
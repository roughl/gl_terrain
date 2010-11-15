# Project: gl_terrain

CPP  = g++
CC   = gcc
OBJ  = src/main.o src/OpenGL.o src/Terrain.o src/HMapReader.o src/LuaFuncs.o src/Cube.o src/world.o src/Object.o src/Particle.o src/Config.o src/VectorCalc.o src/sphere.o
LINKOBJ  = src/main.o src/OpenGL.o src/Terrain.o src/HMapReader.o src/LuaFuncs.o src/Cube.o src/world.o src/Object.o src/Particle.o src/Config.o src/VectorCalc.o src/sphere.o
LIBS = lua sdl gl glu
BIN  = gl_terrain
LOGS = ReadBMP.log Terrain.log
CXXFLAGS += `pkg-config --cflags --libs $(LIBS)` $(CXXINCS)   -fexpensive-optimizations -O3 -std=c++0x
CFLAGS += `pkg-config --cflags --libs $(LIBS)` -I/usr/include -Dmain=SDL_main   -fexpensive-optimizations -O3
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before gl_terrain all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN) $(LOGS)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "gl_terrain" -Dmain=SDL_main $(CXXFLAGS)

src/main.o: src/main.c
	$(CPP) -c src/main.c -o src/main.o $(CXXFLAGS)

src/OpenGL.o: src/OpenGL.c
	$(CPP) -c src/OpenGL.c -o src/OpenGL.o $(CXXFLAGS)

src/Terrain.o: src/Terrain.cpp
	$(CPP) -c src/Terrain.cpp -o src/Terrain.o $(CXXFLAGS)

src/HMapReader.o: src/HMapReader.cpp
	$(CPP) -c src/HMapReader.cpp -o src/HMapReader.o $(CXXFLAGS)

src/LuaFuncs.o: src/LuaFuncs.c
	$(CPP) -c src/LuaFuncs.c -o src/LuaFuncs.o $(CXXFLAGS)

src/Cube.o: src/Cube.cpp
	$(CPP) -c src/Cube.cpp -o src/Cube.o $(CXXFLAGS)

src/world.o: src/world.cpp
	$(CPP) -c src/world.cpp -o src/world.o $(CXXFLAGS)

src/Object.o: src/Object.cpp
	$(CPP) -c src/Object.cpp -o src/Object.o $(CXXFLAGS)

src/Particle.o: src/Particle.cpp
	$(CPP) -c src/Particle.cpp -o src/Particle.o $(CXXFLAGS)

src/Config.o: src/Config.cpp
	$(CPP) -c src/Config.cpp -o src/Config.o $(CXXFLAGS)

src/VectorCalc.o: src/VectorCalc.cpp
	$(CPP) -c src/VectorCalc.cpp -o src/VectorCalc.o $(CXXFLAGS)

src/sphere.o: src/sphere.cpp
	$(CPP) -c src/sphere.cpp -o src/sphere.o $(CXXFLAGS)


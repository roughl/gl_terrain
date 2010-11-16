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

%.o: %.cpp
	$(CPP) -c $(CXXFLAGS) $< -o $@


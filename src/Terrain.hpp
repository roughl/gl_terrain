// Terain.hpp

#ifndef __TERAIN_HPP
#define __TERAIN_HPP

#include <vector>
#include <iostream>
#include <lua.hpp>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include "HMapReader.hpp"
#include "Object.hpp"
#include "Cube.hpp"
#include "Particle.hpp"


class terrvertex 
{
	public:
	GLfloat x,y,z;
	GLfloat normalVector[3];
	GLfloat color[3];
};

#define ind(x, z, sizeofx) ((x) + ((z) * (sizeofx))) 

class zTerrain 
{
public:
	zTerrain(lua_State *L, World *world);
	~zTerrain();

	bool Create(const char* name);
	float GetMapY(float x, float z);
	float GetMapY(int x, int z);

	void Draw(void);
	void DrawChildren(void);
	void Update (Uint32  milliseconds, Uint8 *keystate);
	void Update (SDL_MouseMotionEvent *mouse);
	void Update (SDL_KeyboardEvent *keyevent);
	float GetDepth();
	
	int GetWidth()  {return width;}
	int GetHeight() {return height;}

private:
	lua_State *L;
	std::vector<Hmap *> hmap;
	std::vector<Particle *> particles; // array of particles
	
	//terrvertex *aterr;
	Uint8 *aheightmap;
	float posx, posy, posz, posyoffset; // offset is walking bounce
	float anglex, angley, anglez;
   
	float waterlevel;
	float wave;
   
	Uint32 maxFontains;

	World *motherWorld;
   
	int width, height;
	GLuint dispList;
}; 

#endif // __TERAIN_HPP


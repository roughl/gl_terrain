// World.hpp

#ifndef __WORLD_HPP
#define __WORLD_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

#include <SDL/SDL.h>
#include <lua.hpp>
#include <GL/gl.h>

#include "Terrain.hpp"

class IObject;

class World
{
public:
    World(lua_State *luaState);
    ~World();

    bool Create(const char* fileName);

    void Update();
    void Update (SDL_KeyboardEvent *keyevent);
    void Update(SDL_MouseMotionEvent *mouse);
    void Update (Uint32  milliseconds, Uint8 *keystate);
    
    void Draw(void);
    void DrawChildren(void);
    float GetDepth();
    void GetCamAngle(Angle *destangle){
        destangle->x=this->angle.x;
        destangle->y=this->angle.y;
        destangle->z=this->angle.z;
    }
    void GetCamPos(Pos *destPos){
        destPos->x=this->pos.x;
        destPos->y=this->pos.y;
        destPos->z=this->pos.z;
    }
    lua_State *getLuaState();

private:
   lua_State *L;
   std::vector<zTerrain *>terrain;
   std::vector<IObject *> objects; // array of objects
   
   Angle angle;
   Pos oldpos;
   Pos pos;
   float posyoffset; // offset is walking bounce
   
   float zspeed, xspeed, yspeed, turnspeed, mousespeed;
   float maxheight, gravity;
   float waterlevel;
   
   float jumpvelocity; // velocity when you jump
   
   bool drawtop, drawbuttom, drawright, drawleft;
};


#endif // __WORLD_HPP

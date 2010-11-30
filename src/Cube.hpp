// Cube.hpp

#ifndef __CUBE_HPP
#define __CUBE_HPP

#include <lua.hpp>
#include "Object.hpp"

class Cube : public Object
{
public:
    //Cube(lua_State *L);
    Cube(World *world);
    Cube();
    Uint8 Create(float posx, float posy, float posz, float size);
    void Update(Uint32 milliseconds, Uint8 *keystate);
private:
    float speedx, speedy, speedz;
    float size;
    
};

    
#endif // __CUBE_HPP

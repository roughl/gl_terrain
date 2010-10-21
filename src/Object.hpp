// Object.hppp

#ifndef __OBJECT_HPP
#define __OBJECT_HPP

#include <lua.hpp>
#include <GL/gl.h>
#include <SDL/SDL.h>

class World;

class Object
{
public:
    Object();
    Object(World *world);
    virtual void Draw(); // Do Render
    virtual void Update(Uint32 milliseconds, Uint8 *keystate){} // per default do not any update
    
  //  static GLuint CreateCube();
    
    float getPosX(){return posx;}
    float getPosY(){return posy;}
    float getPosZ(){return posz;}
    
    float getAngleX(){return anglex;}
    float getAngleY(){return angley;}
    float getAngleZ(){return anglez;}
    
protected:
    bool visible;
    float posx, posy, posz;
    float anglex, angley, anglez;
    GLuint dispList;
    World *motherWorld;
};

#endif // __OBJECT_HPP

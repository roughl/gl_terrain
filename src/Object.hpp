// Object.hppp

#ifndef __OBJECT_HPP
#define __OBJECT_HPP

#include <lua.hpp>
#include <GL/gl.h>
#include <SDL/SDL.h>

#include "IObject.hpp"

class World;

class Object : public IObject
{
public:
    Object(World *world=NULL);
    virtual void Draw(); // Do Render
    virtual void Update(Uint32 milliseconds, Uint8 *keystate){} // per default do not any update
    
  	const Pos &getPos(){return pos;}
  	const Angle &getAngle(){return angle;}
    
protected:
    bool visible;
	Pos pos;
	Angle angle;
    GLuint dispList;
    World *motherWorld;
};

#endif // __OBJECT_HPP

// Object.hpp

#ifndef __IOBJECT_HPP
#define __IOBJECT_HPP

#include <GL/gl.h>
#include <SDL/SDL.h>

class World;

struct Angle
{
	Angle(float x, float y, float z):
		x(x),
		y(y),
		z(z)
	{}
	float x,y,z;
};
struct Pos
{
	Pos(float x, float y, float z):
		x(x),
		y(y),
		z(z)
	{}
	float x,y,z;
};


class IObject
{
public:
	virtual ~IObject(){};
	virtual void Draw() = 0; // Do Render
	virtual void Update(Uint32 milliseconds, Uint8 *keystate) = 0; // per default do not any update
    
	virtual const Pos& getPos() = 0;
	virtual const Angle& getAngle() = 0;
};

#endif // __IOBJECT_HPP

// Sphere.hpp

#ifndef __SPHERE_HPP
#define __SPHERE_HPP

#include <GL/gl.h>
#include <GL/glu.h>
#include <lua.hpp>
#include "Object.hpp"

class Sphere : public Object
{
public:
    Sphere(World *world=NULL);
    ~Sphere();
    Uint8 Create(float posx, float posy, float posz, float size);
    void Update(Uint32 milliseconds, Uint8 *keystate);
    void Draw();
private:
    float speedx, speedy, speedz;
    float size;
    GLUquadricObj *quadratic;				// Storage For Our Quadratic Objects ( NEW )
};

#endif // __SPHERE_HPP


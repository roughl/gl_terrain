// Sphere.cpp

#include <iostream>

#include "sphere.hpp"
#include <lua.hpp>
#include <SDL/SDL.h>

#include "VectorCalc.hpp"
#include "World.hpp"

Sphere::Sphere(World *world):
	Object(),
    quadratic(NULL),
	speedx(0),
	speedy(0),
	speedz(0),
	size(0)
{
}

Sphere::~Sphere()
{
    gluDeleteQuadric(quadratic);
}


Uint8 Sphere::Create(float posx, float posy, float posz, float newsize=2.0f)
{
    this->size=newsize;
    this->pos.x=posx;
    this->pos.y=posy;
    this->pos.z=posz;

	quadratic=gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
	if(quadratic==NULL)
	{
        // failed
        return 0;
    }
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )
    return 1;
}

void Sphere::Update(Uint32 milliseconds, Uint8 *keystate)
{
    #ifdef __DEBUG__
    std::cout << "Updateing Sphere\n";
    #endif
    angle.x+=milliseconds*0.2f;
    angle.y+=milliseconds*0.1f;
    
    if(angle.x>360.0f)
        angle.x=angle.x-360.0f;
        
    if(angle.y>360.0f)
        angle.y=angle.y-360.0f;
}

void Sphere::Draw()
{
    glPushMatrix();
    glTranslatef (pos.x, pos.y, pos.z);							// Translate to Object Position
/*    glRotatef (anglex, 1.0f, 0.0f, 0.0f);						// Rotate On The X-Axis By angle
    glRotatef (angley, 0.0f, 1.0f, 0.0f);						// Rotate On The Y-Axis By angle
    glRotatef (anglez, 0.0f, 0.0f, 1.0f);						// Rotate On The Z-Axis By angle
*/    gluSphere(quadratic,size,32,32);		// Draw A Sphere
    glPopMatrix();
}


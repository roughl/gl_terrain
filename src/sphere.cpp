// Sphere.cpp

#include <iostream>

#include "sphere.hpp"
#include <lua.hpp>
#include <SDL/SDL.h>

#include "VectorCalc.hpp"
#include "World.hpp"

Sphere::Sphere()
{
   posx=3.0f;
   posy=2.0f;
   posz=16.0f;
   
   anglex=0.0f;
   angley=0.0f;
   anglez=0.0f;

   
   dispList=0;

}

Sphere::Sphere(World *world):
    speedx(0.0f),
    speedy(0.0f),
    speedz(0.0f),
    quadratic(0)
{
}

Sphere::~Sphere()
{
    gluDeleteQuadric(quadratic);
}


Uint8 Sphere::Create(float posx, float posy, float posz, float newsize=2.0f)
{
    this->size=newsize;
    this->posx=posx;
    this->posy=posy;
    this->posz=posz;

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
    anglex+=milliseconds*0.2f;
    angley+=milliseconds*0.1f;
    
    if(anglex>360.0f)
        anglex=anglex-360.0f;
        
    if(angley>360.0f)
        angley=angley-360.0f;

    
}

void Sphere::Draw()
{
    glPushMatrix();
    glTranslatef (posx, posy, posz);							// Translate to Object Position
/*    glRotatef (anglex, 1.0f, 0.0f, 0.0f);						// Rotate On The X-Axis By angle
    glRotatef (angley, 0.0f, 1.0f, 0.0f);						// Rotate On The Y-Axis By angle
    glRotatef (anglez, 0.0f, 0.0f, 1.0f);						// Rotate On The Z-Axis By angle
*/    gluSphere(quadratic,size,32,32);		// Draw A Sphere
    glPopMatrix();
}


// Object.cpp

#include <iostream>

#include "Object.hpp"
#include <lua.hpp>

#include "World.hpp"

using namespace std;


Object::Object()
{
    posx=0.0f;
    posy=0.0f;
    posz=0.0f;    
    visible=true;
}

Object::Object(World *world):
    motherWorld(world),
    posx(0.0f),
    posy(0.0f),
    posz(0.0f),
    anglex(0.0f),
    angley(0.0f),
    anglez(0.0f),
    visible(true)
{
}


void Object::Draw()
{
    if(visible)
    {
        //cout << "Draw Object at " << posx << " / " << posy << " / " << posz<<"\n";
        glPushMatrix();
    	glTranslatef (posx, posy, posz);							// Translate to Object Position
    	glRotatef (anglex, 1.0f, 0.0f, 0.0f);						// Rotate On The X-Axis By angle
    	glRotatef (angley, 0.0f, 1.0f, 0.0f);						// Rotate On The Y-Axis By angle
    	glRotatef (anglez, 0.0f, 0.0f, 1.0f);						// Rotate On The Z-Axis By angle
        glCallList(dispList);
        glPopMatrix();
    }
}

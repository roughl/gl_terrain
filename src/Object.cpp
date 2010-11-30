// Object.cpp

#include <iostream>

#include "Object.hpp"
#include <lua.hpp>

#include "World.hpp"

using namespace std;


Object::Object()
{
    pos.x=0.0f;
    pos.y=0.0f;
    pos.z=0.0f;    
    angle.x=0.0f;
    angle.y=0.0f;
    angle.z=0.0f;
    visible=true;
	dispList = 0;
}

Object::Object(World *world):
    motherWorld(world),
    visible(true)
{
    pos.x=0.0f;
    pos.y=0.0f;
    pos.z=0.0f;
    angle.x=0.0f;
    angle.y=0.0f;
    angle.z=0.0f;
	dispList = 0;
}


void Object::Draw()
{
    if(visible)
    {
        //cout << "Draw Object at " << posx << " / " << posy << " / " << posz<<"\n";
        glPushMatrix();
    	glTranslatef (pos.x, pos.y, pos.z);							// Translate to Object Position
    	glRotatef (angle.x, 1.0f, 0.0f, 0.0f);						// Rotate On The X-Axis By angle
    	glRotatef (angle.y, 0.0f, 1.0f, 0.0f);						// Rotate On The Y-Axis By angle
    	glRotatef (angle.z, 0.0f, 0.0f, 1.0f);						// Rotate On The Z-Axis By angle
        glCallList(dispList);
        glPopMatrix();
    }
}
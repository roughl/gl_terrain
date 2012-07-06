// Object.cpp

#include <iostream>

#include "Object.hpp"
#include <lua.hpp>

#include "World.hpp"

using namespace std;

Object::Object(World *world)
    :visible(true)
	,pos(0,0,0)
	,angle(0,0,0)
	,dispList(0)
    ,motherWorld(world)
{
}

Object::~Object()
{
	cout << "~Object()" << endl;
	if(dispList) {
		glDeleteLists(dispList,1);
	}
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

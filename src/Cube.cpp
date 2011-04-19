// Cube.cpp

#include <iostream>

#include "Cube.hpp"
#include <lua.hpp>
#include <SDL/SDL.h>

#include "VectorCalc.hpp"
#include "World.hpp"

Cube::Cube():
	Object(),
	speedx(0.0f),
	speedy(0.0f),
	speedz(0.0f),
	size(0)
{
	dispList=0;
}

Cube::Cube(World *world):
	speedx(0.0f),
	speedy(0.0f),
	speedz(0.0f),
	size(0)
{
}


Uint8 Cube::Create(float posx, float posy, float posz, float newsize=2.0f)
{
	this->size=newsize;
	this->pos.x=posx;
	this->pos.y=posy;
	this->pos.z=posz;

	
	// --- if you just want to change cube the old one will be overwritten ---
	if(glIsList(dispList))
		glDeleteLists(dispList,1);
	else
		dispList=glGenLists(1);
	glNewList(dispList,GL_COMPILE);

	glBegin (GL_QUADS);
	
	// Bottom
	GLfloat vert1[] = { size, -size,  size };
	GLfloat vert2[] = { size, -size, -size };
	GLfloat vert3[] = {-size, -size, -size };
	GLfloat norm[3];
	vec::CalculateVectorNormal(vert1,vert2,vert3, norm);
	
	glNormal3fv(norm);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex3f(-size, -size, -size);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex3f( size, -size, -size);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex3f( size, -size,  size);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex3f(-size, -size,  size);
	
	// Top
	{
	GLfloat vert1[] = {-size,  size, -size };
	GLfloat vert2[] = { size,  size, -size };
	GLfloat vert3[] = { size,  size,  size };
	vec::CalculateVectorNormal(vert1,vert2,vert3, norm);
	glNormal3fv(norm);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex3f(-size,  size, -size);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex3f(-size,  size,  size);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex3f( size,  size,  size);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex3f( size,  size, -size);
	}

	// Side
	{
	GLfloat vert1[] = { size, -size, -size };
	GLfloat vert2[] = { size,  size, -size };
	GLfloat vert3[] = {-size,  size, -size };
	vec::CalculateVectorNormal(vert1,vert2,vert3, norm);
	glNormal3fv(norm);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex3f(-size,  size, -size);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex3f( size,  size, -size);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex3f( size, -size, -size);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex3f(-size, -size, -size);
	}

	// Side
	{
	GLfloat vert1[] = { size,  size,  size };
	GLfloat vert2[] = { size,  size, -size };
	GLfloat vert3[] = { size, -size, -size };
	vec::CalculateVectorNormal(vert1,vert2,vert3, norm);
	glNormal3fv(norm);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex3f( size, -size, -size);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex3f( size,  size, -size);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex3f( size,  size,  size);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex3f( size, -size,  size);
	}

	// Side
	{
	GLfloat vert1[] = {-size,  size,  size };
	GLfloat vert2[] = { size,  size,  size };
	GLfloat vert3[] = { size, -size,  size };
	vec::CalculateVectorNormal(vert1,vert2,vert3, norm);
	glNormal3fv(norm);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex3f( size, -size,  size);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex3f( size,  size,  size);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex3f(-size,  size,  size);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex3f(-size, -size,  size);
	}

	// Side
	{
	GLfloat vert1[] = {-size,  size, -size };
	GLfloat vert2[] = {-size,  size,  size };
	GLfloat vert3[] = {-size, -size,  size };
	vec::CalculateVectorNormal(vert1,vert2,vert3, norm);
	glNormal3fv(norm);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex3f(-size, -size,  size);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex3f(-size,  size,  size);
	glColor3f (1.0f, 0.0f, 0.0f); glVertex3f(-size,  size, -size);
	glColor3f (0.0f, 0.0f, 1.0f); glVertex3f(-size, -size, -size);
	}

	glEnd ();    
	glEndList();
}

void Cube::Update(Uint32 milliseconds, Uint8 *keystate)
{
	#ifdef __DEBUG__
	std::cout << "Updateing Cube\n";
	#endif
	angle.x+=milliseconds*0.2f;
	angle.y+=milliseconds*0.1f;
	
	if(angle.x>360.0f)
		angle.x=angle.x-360.0f;
		
	if(angle.y>360.0f)
		angle.y=angle.y-360.0f;
		
	// calculate distance to viewer
	// sqrt((-camx+partx)^2+(-camz+partz)^2)
	float distance;
	Pos mypos;
	mypos.x=pos.x;
	mypos.y=pos.y;
	mypos.z=pos.z;
	Pos worldpos;
	#ifdef __DEBUG__
	std::cout << "GetCamPos\n";
	motherWorld->GetCamPos(&worldpos);
	std::cout << "getDistance\n";
	distance=vec::getDistance(&worldpos, &mypos);
	#endif
	/*
	if(distance-size > (float)motherWorld->GetDepth())
	{
		visible=false;
		std::cout << "Cube is not visible\n";
	}
	else
	{
		visible=true;
		std::cout << "Cube is visible\n";
	}
		*/
	
}


// Cube.cpp

#include <iostream>

#include "Cube.hpp"
#include <lua.hpp>
#include <SDL/SDL.h>

#include "VectorCalc.hpp"
#include "World.hpp"

Cube::Cube(World *world):
	Object(world),
	speedx(0.0f),
	speedy(0.0f),
	speedz(0.0f),
	size(0)
{
}


Uint8 Cube::Create(float posx, float posy, float posz, float newsize=2.0f)
{
	static const int n = 6*4;
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

	GLfloat vertices[n][3] = {
	 // Bottom
	 -size, -size, -size,
	  size, -size, -size,
	  size, -size,  size,
	 -size, -size,  size,
	
	// Top
	-size,  size, -size,
	-size,  size,  size,
	 size,  size,  size,
	 size,  size, -size,
	
	-size,  size, -size,
	 size,  size, -size,
	 size, -size, -size,
	-size, -size, -size,

	 size, -size, -size,
	 size,  size, -size,
	 size,  size,  size,
	 size, -size,  size,

	 size, -size,  size,
	 size,  size,  size,
	-size,  size,  size,
	-size, -size,  size,
		
	-size, -size,  size,
	-size,  size,  size,
	-size,  size, -size,
	-size, -size, -size
	};

	GLfloat colors[n][3] = {
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	
	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,

	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,

	0.0f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	};

	GLfloat normals[n][3] = { };

	for(int i=0; i<n; i+=4) {
		vec::CalculateVectorNormal( vertices[i], vertices[i+1], vertices[i+2], normals[i] );
		vec::CalculateVectorNormal( vertices[i], vertices[i+1], vertices[i+2], normals[i+1] );
		vec::CalculateVectorNormal( vertices[i], vertices[i+1], vertices[i+2], normals[i+2] );
		vec::CalculateVectorNormal( vertices[i], vertices[i+1], vertices[i+2], normals[i+3] );
	}

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );

	glVertexPointer( 3, GL_FLOAT, 0, vertices );
	glColorPointer(  3, GL_FLOAT, 0, colors );
	glNormalPointer( GL_FLOAT, 0, normals );

	glDrawArrays( GL_QUADS, 0, n );
	
	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_NORMAL_ARRAY );

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
	Pos mypos(pos.x, pos.y, pos.z);
	Pos worldpos(0,0,0);
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


// Terrain.cpp

#include "Terrain.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <cassert>

#include <SDL/SDL.h>
#include <lua.hpp>
#include <GL/gl.h>
#include <math.h>
#include <string>

#include "HMapReader.hpp"
#include "LuaFuncs.h"
#include "OpenGL.h"
#include "VectorCalc.hpp"

using namespace std;


zTerrain::zTerrain(lua_State *L, World *world)
  :motherWorld(world)
  ,height(0)
  ,width(0)
{
	this->L=L;
	
	anglex=0.0f;
	angley=0.0f;
	anglez=0.0f;
	
	bool ok=false;
	waterlevel = (float)lua_GetNumber(L, "waterlevel", &ok);
	if(!ok)
		waterlevel=1.0f;
	maxFontains= (unsigned int)lua_GetNumber(L, "maxFontains", &ok);
	if(!ok)
		maxFontains=10;
}


bool zTerrain::Create(const char* Map)
{
   ofstream logTerrain( "Terrain.log", ios::out );
   logTerrain << "Starting reading " << Map << "\n";
   
   hmap.push_back( new Hmap(Map) );
  
   aheightmap = hmap[0]->Data;
   height     = hmap[0]->height;
   width      = hmap[0]->width;
   
   
   logTerrain << "Map Height: " << height << " Map Width: " << width << endl;
   
   terrvertex *aterr = new terrvertex[(height)*(width)*4];
   
   if (aheightmap==NULL)
	  return false;

   int num=0;
   for (int z=0; z < height; z++) {
	  for (int x=0; x < width; x++) {
		aterr[num].x = (float) x;
		aterr[num].z = (float) z;
		aterr[num].y = GetMapY(x,z);
	  // logTerrain <<"x="<<x<<" z="<<z<<" -> aheigtmap["<<x+z*(width) << "] = " << aheightmap[x+z*(width)] << endl;
	  // logTerrain <<"aterr[" << num <<"].y = " << aterr[num].y << endl;
		
		aterr[num+1].x = (float) x;
		aterr[num+1].z = (float) z+1;
		aterr[num+1].y = GetMapY(x, z+1);
		
		aterr[num+2].x = (float) x+1;
		aterr[num+2].z = (float) z+1;
		aterr[num+2].y = GetMapY(x+1,z+1);
		//logTerrain <<"x="<<x+1<<" z="<<z+1<<" -> aheigtmap["<<x+1+(z+1)*(width) << "] = " << aheightmap[x+1+(z+1)*(width)] << endl;
		aterr[num+3].x = (float) x+1;
		aterr[num+3].z = (float) z;
		aterr[num+3].y = GetMapY(x+1,z);
		//logTerrain <<"x="<<x+1<<" z="<<z<<" -> aheigtmap["<<x+1+z*(width) << "] = " << aheightmap[ind(x+1,z,width)] << endl;

		//logTerrain <<"x="<<x<<" z="<<z+1<<" -> aheigtmap["<<x+(z+1)*(width) << "] = " << aheightmap[x+(z+1)*(width)] << endl;
		GLfloat vert1[3], vert2[3], vert3[3];
		
		vert1 = {(GLfloat)x  , GetMapY(x  ,z  ), (GLfloat)z  };
		vert2 = {(GLfloat)x-1, GetMapY(x-1,z  ), (GLfloat)z  };
		vert3 = {(GLfloat)x-1, GetMapY(x-1,z-1), (GLfloat)z-1};
		GLfloat norm1[3];
		vec::CalculateVectorNormal(vert1,vert2,vert3, norm1);
		
		vert1 = {(GLfloat)x+1, GetMapY(x+1,z  ), (GLfloat)z  };
		vert2 = {(GLfloat)x  , GetMapY(x  ,z  ), (GLfloat)z  };
		vert3 = {(GLfloat)x  , GetMapY(x  ,z-1), (GLfloat)z-1};
		GLfloat norm2[3];
		vec::CalculateVectorNormal(vert1,vert2,vert3, norm2);
		
		vert1 = {(GLfloat)x+2, GetMapY(x+2,z  ), (GLfloat)z  };
		vert2 = {(GLfloat)x+1, GetMapY(x+1,z  ), (GLfloat)z  };
		vert3 = {(GLfloat)x+1, GetMapY(x+1,z-1), (GLfloat)z-1};
		GLfloat norm3[3];
		vec::CalculateVectorNormal(vert1,vert2,vert3, norm3);

		vert1 = {(GLfloat)x+0, GetMapY(x+0,z+1), (GLfloat)z+1};
		vert2 = {(GLfloat)x-1, GetMapY(x-1,z+1), (GLfloat)z+1};
		vert3 = {(GLfloat)x-1, GetMapY(x-1,z+0), (GLfloat)z+0};
		GLfloat norm4[3];
		vec::CalculateVectorNormal(vert1,vert2,vert3, norm4);

		vert1 = {(GLfloat)x+1, GetMapY(x+1,z+1), (GLfloat)z+1};//&(aterr[num+2].x);
		vert2 = {(GLfloat)x  , GetMapY(x  ,z+1), (GLfloat)z+1};//&(aterr[num+2].x);
		vert3 = {(GLfloat)x  , GetMapY(x  ,z  ), (GLfloat)z  };//&(aterr[num+2].x);
		GLfloat norm5[3];
		vec::CalculateVectorNormal(vert1,vert2,vert3, norm5);

		vert1 = {(GLfloat)x+2, GetMapY(x+2,z+1), (GLfloat)z+1};
		vert2 = {(GLfloat)x+1, GetMapY(x+1,z+1), (GLfloat)z+1};
		vert3 = {(GLfloat)x+1, GetMapY(x+1,z+0), (GLfloat)z+0};
		GLfloat norm6[3];
		vec::CalculateVectorNormal(vert1,vert2,vert3, norm6);

		vert1 = {(GLfloat)x+0, GetMapY(x+0,z+2), (GLfloat)z+2};
		vert2 = {(GLfloat)x-1, GetMapY(x-1,z+2), (GLfloat)z+2};
		vert3 = {(GLfloat)x-1, GetMapY(x-1,z+1), (GLfloat)z+1};
		GLfloat norm7[3];
		vec::CalculateVectorNormal(vert1,vert2,vert3, norm7);

		vert1 = {(GLfloat)x+1, GetMapY(x+1,z+2), (GLfloat)z+2};
		vert2 = {(GLfloat)x+0, GetMapY(x+0,z+2), (GLfloat)z+2};
		vert3 = {(GLfloat)x+0, GetMapY(x+0,z+1), (GLfloat)z+1};
		GLfloat norm8[3];
		vec::CalculateVectorNormal(vert1,vert2,vert3, norm8);

		vert1 = {(GLfloat)x+2, GetMapY(x+2,z+2), (GLfloat)z+2};
		vert2 = {(GLfloat)x+1, GetMapY(x+1,z+2), (GLfloat)z+2};
		vert3 = {(GLfloat)x+1, GetMapY(x+1,z+1), (GLfloat)z+1};
		GLfloat norm9[3];
		vec::CalculateVectorNormal(vert1,vert2,vert3, norm9);
		logTerrain << norm9[0] << " " << norm9[1] << " " << norm9[2] << " " << sqrt(norm9[0]*norm9[0]+norm9[1]*norm9[1]+ norm9[2]*norm9[2]) << endl ;
		aterr[num+0].normalVector[0] = (norm1[0] + norm2[0] + norm4[0] + norm5[0])/4.0f;
		aterr[num+0].normalVector[1] = (norm1[1] + norm2[1] + norm4[1] + norm5[1])/4.0f;
		aterr[num+0].normalVector[2] = (norm1[2] + norm2[2] + norm4[2] + norm5[2])/4.0f;
		
		aterr[num+1].normalVector[0] = (norm7[0] + norm8[0] + norm4[0] + norm5[0])/4.0f;
		aterr[num+1].normalVector[1] = (norm7[1] + norm8[1] + norm4[1] + norm5[1])/4.0f;
		aterr[num+1].normalVector[2] = (norm7[2] + norm8[2] + norm4[2] + norm5[2])/4.0f;
		
		aterr[num+2].normalVector[0] = (norm6[0] + norm8[0] + norm9[0] + norm5[0])/4.0f;
		aterr[num+2].normalVector[1] = (norm6[1] + norm8[1] + norm9[1] + norm5[1])/4.0f;
		aterr[num+2].normalVector[2] = (norm6[2] + norm8[2] + norm9[2] + norm5[2])/4.0f;
		
		aterr[num+3].normalVector[0] = (norm6[0] + norm2[0] + norm3[0] + norm5[0])/4.0f;
		aterr[num+3].normalVector[1] = (norm6[1] + norm2[1] + norm3[1] + norm5[1])/4.0f;
		aterr[num+3].normalVector[2] = (norm6[2] + norm2[2] + norm3[2] + norm5[2])/4.0f;
		
		num += 4;
	  }
	}
   
   
	dispList=glGenLists(1);
	glNewList(dispList,GL_COMPILE);
	glBegin (GL_QUADS);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	num=0;
	srand(SDL_GetTicks());
	
	std::vector<int> ParticlePlaces;
	unsigned int numPoints=(height)*(width)*4;
	for (int z=0; z < (height)*(width); z++) {
		for (int cnt=0; cnt<4; cnt++) {
			GLfloat red=0.0f, green=1.0f, blue=0.0f;
			if( ((int)round(aterr[num].y*25.5f)) % 2)
				red=0.5f;
			if (aterr[num].y<waterlevel)
			{
				GLfloat specReflection[] = {0.8f, 0.8f, 0.8f, 1.0f};
				glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
				glMateriali(GL_FRONT, GL_SHININESS, 96);
				blue=aterr[num].y* (-1.0)/waterlevel + 1.0f;
				green=1.0f-blue;
				// Good Place for Particle??
				if(blue>0.85f)
				{
					ParticlePlaces.push_back(num);
				}
				if(red==0.0f)
					red+=0.1f;
				else;
					//red-=0.1f;
			}
			else
			{
				GLfloat specReflection[] = {0.0f, 0.0f, 0.0f, 1.0f};
				glMaterialfv(GL_FRONT, GL_SPECULAR, specReflection);
				glMateriali(GL_FRONT, GL_SHININESS, 0);
			}
			glNormal3fv(aterr[num].normalVector);
			glColor4f (red, green, blue, 1.0f);
			glVertex3f(aterr[num].x,aterr[num].y, aterr[num].z);
			num++;
		}

	}
	glEnd ();	
	// draw normals
	/*glBegin(GL_LINES);
	glColor4f(1.0,1.0,1.0,1.0f);
	glLineWidth(3);
	num=0;
	for (int z=0; z < (height)*(width)*4; z++) {
		glVertex3f(aterr[num].x,aterr[num].y, aterr[num].z);
		glVertex3f(aterr[num].x+aterr[num].normalVector[0],aterr[num].y+aterr[num].normalVector[1], aterr[num].z+aterr[num].normalVector[2]);
		num++;
	}
	glEnd();*/
   glEndList();

   logTerrain << "Found " << ParticlePlaces.size() << " Good Places for Fontains" << endl;
   if(ParticlePlaces.size()) {
		unsigned texture=LoadAlphaTexture("Data/test_alpha.bmp");		
	   Uint32 numFontains = rand()%(maxFontains+1);
	   logTerrain << "Creating " << numFontains << " Fontains" << endl;
	   for(int cnt=0; cnt <numFontains; cnt++)
	   {
			int num=ParticlePlaces[rand()%ParticlePlaces.size()];
			float x=aterr[num].x,y=aterr[num].y,z=aterr[num].z;
			int numParts= (rand()%90)+10;
			particles.push_back( new Particle(motherWorld, this, numParts, x, y, z, 0.0f, texture));
	   }
	}
   delete[] aterr;
   aterr=NULL;   
   logTerrain.close();   
   return true;
} 


zTerrain::~zTerrain()
{
	glDeleteLists(dispList, 1);
	for(;hmap.size();)
	{
		delete hmap[hmap.size()-1];
		hmap.pop_back();
	}
}


float zTerrain::GetMapY(int x, int z)
{
 //   cout << "GetMapY für " <<x <<" / " << z <<endl;
 	if(x<0)	x=width+x;
	x = x%width;
	if(z<0) z = height+z;
	z = z%height;
	assert(!(x<0 || z<0 || x>width || z>height)); // out of map?
//	int x1=(int)floor(x), z1=(int)floor(z), x2=(int)ceil(z), z2=(int)ceil(z);
//	float y1, y2, y3, y4;
	return (float)aheightmap[ind(x, z, width)] / 25.5f; 
}

float zTerrain::GetMapY(float x, float z)
{
 //   cout << "GetMapY für " <<x <<" / " << z <<endl;
	if(x<0.0f || z<0.0f || x>width || z>height) // out of map?
		return -1.0f;
//	int x1=(int)floor(x), z1=(int)floor(z), x2=(int)ceil(z), z2=(int)ceil(z);
//	float y1, y2, y3, y4;
	return (float)aheightmap[ind((int)round(x), (int)round(z),width)] / 25.5f; 
}

void zTerrain::Update (SDL_KeyboardEvent *keyevent)
{
}


void zTerrain::Update (Uint32  milliseconds, Uint8 *keystate)								// Perform Motion Updates Here
{
	std::vector<Particle *>::iterator partsit;
	for(partsit=particles.begin(); partsit<particles.end(); partsit++)
	{
		(*partsit)->Update(milliseconds, keystate);
	}
}



void zTerrain::Update(SDL_MouseMotionEvent *mouse)
{
}

void zTerrain::DrawChildren(void)
{
	std::vector<Particle *>::iterator partsIt;
	for(partsIt=particles.begin(); partsIt<particles.end(); partsIt++)
	{
		(*partsIt)->Draw();
	}
}


void zTerrain::Draw(void)
{  
	#ifdef __DEBUG__
	std::cout << "Drawing Terrain at " << posx << " / " << posy << " / " << posz << " / ";
	#endif
	glCallList(dispList);
	DrawChildren();
} 

// Get Value for Depth Buffer
float zTerrain::GetDepth()
{
	if(width>height)
		return ((float)width/2.0f)-2.0f;
	return ((float)height/2.0f)-2.0f;
}


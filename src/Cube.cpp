// Cube.cpp

#include <iostream>

#include "Cube.hpp"
#include <lua.hpp>
#include <SDL/SDL.h>

#include "VectorCalc.hpp"
#include "World.hpp"

Cube::Cube()
{
   posx=3.0f;
   posy=2.0f;
   posz=16.0f;
   
   anglex=0.0f;
   angley=0.0f;
   anglez=0.0f;

   
   dispList=0;

}

/*
Cube::Cube(lua_State *L)
{
   Object::L=L;
   
   posx=3.0f;
   posy=2.0f;
   posz=16.0f;
   
   anglex=0.0f;
   angley=0.0f;
   anglez=0.0f;

   dispList=0;
   
}*/
Cube::Cube(World *world):
    speedx(0.0f),
    speedy(0.0f),
    speedz(0.0f)
{
}


Uint8 Cube::Create(float posx, float posy, float posz, float newsize=2.0f)
{
    this->size=newsize;
    this->posx=posx;
    this->posy=posy;
    this->posz=posz;

    
    // --- if you just want to change cube the old one will be overwritten ---
    if(glIsList(dispList))
        glDeleteLists(dispList,1);
    else
        dispList=glGenLists(1);
    glNewList(dispList,GL_COMPILE);

    glBegin (GL_QUADS);
    // Button
    glColor3f (0.0f, 0.0f, 1.0f); glVertex3f(-size, -size, -size);
    glColor3f (0.0f, 0.0f, 1.0f); glVertex3f( size, -size, -size);
    glColor3f (0.0f, 0.0f, 1.0f); glVertex3f( size, -size,  size);
    glColor3f (0.0f, 0.0f, 1.0f); glVertex3f(-size, -size,  size);
    
    // Top
    glColor3f (1.0f, 0.0f, 0.0f); glVertex3f(-size,  size, -size);
    glColor3f (1.0f, 0.0f, 0.0f); glVertex3f( size,  size, -size);
    glColor3f (1.0f, 0.0f, 0.0f); glVertex3f( size,  size,  size);
    glColor3f (1.0f, 0.0f, 0.0f); glVertex3f(-size,  size,  size);
    
    // Side
    glColor3f (0.0f, 0.0f, 1.0f); glVertex3f(-size, -size, -size);
    glColor3f (0.0f, 0.0f, 1.0f); glVertex3f( size, -size, -size);
    glColor3f (1.0f, 0.0f, 0.0f); glVertex3f( size,  size, -size);
    glColor3f (1.0f, 0.0f, 0.0f); glVertex3f(-size,  size, -size);
    
    // Side
    glColor3f (0.0f, 0.0f, 1.0f); glVertex3f( size, -size, -size);
    glColor3f (0.0f, 0.0f, 1.0f); glVertex3f( size, -size,  size);
    glColor3f (1.0f, 0.0f, 0.0f); glVertex3f( size,  size,  size);
    glColor3f (1.0f, 0.0f, 0.0f); glVertex3f( size,  size, -size);
    
    // Side
    glColor3f (0.0f, 0.0f, 1.0f); glVertex3f( size, -size,  size);
    glColor3f (0.0f, 0.0f, 1.0f); glVertex3f(-size, -size,  size);
    glColor3f (1.0f, 0.0f, 0.0f); glVertex3f(-size,  size,  size);
    glColor3f (1.0f, 0.0f, 0.0f); glVertex3f( size,  size,  size);
    
    // Side
    glColor3f (0.0f, 0.0f, 1.0f); glVertex3f(-size, -size,  size);
    glColor3f (0.0f, 0.0f, 1.0f); glVertex3f(-size, -size, -size);
    glColor3f (1.0f, 0.0f, 0.0f); glVertex3f(-size,  size, -size);
    glColor3f (1.0f, 0.0f, 0.0f); glVertex3f(-size,  size,  size);
    

    glEnd ();    
    //glEnable(GL_CULL_FACE);
   glEndList();
}

void Cube::Update(Uint32 milliseconds, Uint8 *keystate)
{
    #ifdef __DEBUG__
    std::cout << "Updateing Cube\n";
    #endif
    anglex+=milliseconds*0.2f;
    angley+=milliseconds*0.1f;
    
    if(anglex>360.0f)
        anglex=anglex-360.0f;
        
    if(angley>360.0f)
        angley=angley-360.0f;
        
    // calculate distance to viewer
    // sqrt((-camx+partx)^2+(-camz+partz)^2)
    float distance;
    Pos mypos;
    mypos.x=posx;
    mypos.y=posy;
    mypos.z=posz;
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




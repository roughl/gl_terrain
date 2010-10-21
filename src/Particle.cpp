// Particle.cpp
#include "Particle.hpp"

#include <vector>
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>

#include "World.hpp"
#include "OpenGL.h"

using namespace std;

const float Part::colors[12][3]=				// Rainbow Of Colors
{
	{1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
	{0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
	{0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};
const float Part::colors2[12][3]=				// Rainbow Of Colors
{
	{1.00f,0.00f,0.00f},{1.0f,0.25f,0.0f},{1.0f,0.5f,0.0f},{0.75f,0.75f,0.0f},
	{0.75f,1.00f,0.00f},{0.75f,1.00f,0.25f},{0.5f,1.00f,0.25f},{0.5f,1.0f,0.5f},
	{0.5f,0.75f,0.75f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};

const float Part::colors3[12][3]=				// Rainbow Of Colors
{
	{0.50f,0.00f,0.00f},{0.75f,0.00f,0.00f},{1.00f,0.00f,0.00f},{0.50f,0.25f,0.00f},
	{0.75f,0.25f,0.00f},{1.00f,0.25f,0.00f},{0.50f,0.50f,0.00f},{0.75f,0.50f,0.00f},
	{1.00f,0.50f,0.00f},{0.50f,0.75f,0.00f},{0.75,0.75f,0.00f},{1.00f,1.00f,0.00f}
};

const float Part::colors4[12][3]=				// Rainbow Of Colors
{
	{1.00f,0.25f,0.00f},{1.00f,0.50f,0.00f},{1.00f,0.50f,0.25f},{1.00f,0.25f,0.50f},
	{0.25f,1.00f,0.00f},{0.50f,1.00f,0.00f},{0.50f,1.00f,0.25f},{0.75f,1.00f,0.50f},
	{0.25f,0.75f,1.00f},{0.50f,0.50f,1.00f},{0.75,0.25f,1.00f},{1.00f,0.00f,1.00f}
};

const float Part::colorsred[12][3]=				// Rainbow Of Colors
{
	{0.75f,0.00f,0.00f},{1.00f,0.00f,0.00f},{0.75f,0.75f,0.00f},{1.00f,0.75f,0.00f},
	{1.00f,1.00f,0.00f},{1.00f,1.00f,0.25f},{1.00f,1.00f,0.50f},{1.00f,1.00f,0.75f},
	{1.00f,0.50f,0.25f},{1.00f,0.50f,0.50f},{1.00f,0.75f,0.75f},{1.00f,1.00f,1.00f}
};

const float Part::colorsBlue[12][3]=				// Rainbow Of Colors Blue Version
{
	{0.00f,0.00f,0.75f},{0.00f,0.00f,1.00f},{0.25f,0.00f,1.00f},{0.50f,0.00f,1.00f},
	{0.50f,0.25f,1.00f},{0.25f,0.25f,1.00f},{0.00f,0.50f,1.00f},{0.00f,0.75f,1.00f},
	{0.25f,0.75f,1.00f},{0.50f,0.50f,1.00f},{0.50f,0.75f,1.00f},{0.75f,0.75f,1.00f}
};

const float Part::colorsBlueWhite[12][3]=
{
	{0.25f,0.25f,1.00f},{0.50f,0.50f,1.00f},{0.75f,0.75f,1.00f},{1.00f,1.00f,1.00f},
	{1.00f,0.75f,1.00f},{0.75f,1.00f,1.00f},{0.25f,0.25f,1.00f},{0.25f,0.25f,1.00f},
	{0.25f,0.25f,1.00f},{0.25f,0.25f,1.00f},{0.25f,0.25f,1.00f},{0.25f,0.25f,1.00f}
}; 

Part::Part(Particle *group)
    :   partGroup(group),
        visible(true)
{
	life=1.0f;					// Give All The Particles Full Life

	fade=( (float)rand()/RAND_MAX +0.05f)/100.0f;		// Random Fade Speed

	r=colors[rand()%12][0];		// Select Red Rainbow Color
	g=colors[rand()%12][1];		// Select Red Rainbow Color
	b=colors[rand()%12][2];		// Select Red Rainbow Color

	xpos=(float)rand()/(RAND_MAX)-0.5f;					// Random On X Axis
	ypos=0.0f;					                                // Center On Y Axis
	zpos=(float)rand()/(RAND_MAX)-0.5f;				    // Random On Z Axis		

    xspeed=((float)rand()/(RAND_MAX) -0.5f)/75.0f ;		   // Random Speed On X Axis
    yspeed=((float)rand()/(RAND_MAX) +0.1f)/50.0f ;		       // Random Speed On Y Axis
    zspeed=((float)rand()/(RAND_MAX) -0.5f)/75.0f ;		   // Random Speed On Z Axis

	xacc=0.0f;						  // Set Horizontal Pull To Zero
	yacc=-0.05f/1000.0f;					  // Set Vertical Pull Downward
	zacc=0.0f;						  // Set Pull On Z Axis To Zero
	
   dispList=glGenLists(1);
   glNewList(dispList,GL_COMPILE);
	glBegin (GL_TRIANGLE_STRIP);
	   glTexCoord2d(0,1);/**/ glVertex2f(-0.2f,+0.2f); // Top Left
	   glTexCoord2d(1,1);/**/ glVertex2f(+0.2f,+0.2f); // Top Right
	   glTexCoord2d(0,0);/**/ glVertex2f(-0.2f,-0.2f); // Bottom Left
	   glTexCoord2d(1,0);/**/ glVertex2f(+0.2f,-0.2f); // Bottom Right
	glEnd();
   glEndList();
}

Part::Part(Particle *group, const float colorTable[][3])
    :   partGroup(group),
        visible(true)
{
	life=1.0f;					// Give All The Particles Full Life

	fade=( (float)rand()/RAND_MAX +0.05f)/100.0f;		// Random Fade Speed

	r=colorTable[rand()%12][0];		// Select Red Rainbow Color
	g=colorTable[rand()%12][1];		// Select Red Rainbow Color
	b=colorTable[rand()%12][2];		// Select Red Rainbow Color

	xpos=(float)rand()/(RAND_MAX)-0.5f;					// Random On X Axis
	ypos=0.0f;					                                // Center On Y Axis
	zpos=(float)rand()/(RAND_MAX)-0.5f;				    // Random On Z Axis		

    xspeed=((float)rand()/(RAND_MAX) -0.5f)/75.0f ;		   // Random Speed On X Axis
    yspeed=((float)rand()/(RAND_MAX) +0.1f)/50.0f ;		       // Random Speed On Y Axis
    zspeed=((float)rand()/(RAND_MAX) -0.5f)/75.0f ;		   // Random Speed On Z Axis

	xacc=0.0f;						  // Set Horizontal Pull To Zero
	yacc=-0.07f/1000.0f;					  // Set Vertical Pull Downward
	zacc=0.0f;						  // Set Pull On Z Axis To Zero
	
   dispList=glGenLists(1);
   glNewList(dispList,GL_COMPILE);
	glBegin (GL_TRIANGLE_STRIP);
	   glTexCoord2d(1,1);/**/ glVertex2f(+0.2f,+0.2f); // Top Right
	   glTexCoord2d(0,1);/**/ glVertex2f(-0.2f,+0.2f); // Top Left
	   glTexCoord2d(1,0);/**/ glVertex2f(+0.2f,-0.2f); // Bottom Right
	   glTexCoord2d(0,0);/**/ glVertex2f(-0.2f,-0.2f); // Bottom Left
	glEnd();
   glEndList();
}

void Part::Update(Uint32 milliseconds)
{
 
	if (life<=0.0f )					// If Particle Is Burned Out
	{
	    life=1.0f;				                                // Give It New Life
	   fade=( (float)rand()/(float)RAND_MAX +0.01f)/100.0f;		// Random Fade Speed
		xpos=0.0f;//(float)rand()/(RAND_MAX)-0.5f;				// Random On X Axis
		zpos=0.0f;//(float)rand()/(RAND_MAX)-0.5f;				// Center On Z Axis
		ypos=partGroup->getGround(xpos,zpos)-0.2f;				// Put on Ground
        xspeed=((float)rand()/(RAND_MAX) -0.5f) /75.0f;		   // Random Speed On X Axis
        yspeed=((float)rand()/(RAND_MAX) +0.1f) /50.0f;		       // Random Speed On Y Axis
        zspeed=((float)rand()/(RAND_MAX) -0.5f) /75.0f;		   // Random Speed On Z Axis
        return;
    }
    //cout << "Update Part für "<<xpos<< " / "<<zpos <<"-> MapY= "<<MapY <<endl;
    float Ground=partGroup->getGround(xpos,zpos)+0.2f;
    if(yspeed<=0.0f && ypos<=Ground)
    {
        xspeed/=1.5f;
        yspeed/=2.0f;
        zspeed/=1.5f;
        fade+=0.001f;
    }
    else
    {
        xspeed+=xacc*milliseconds ;
        yspeed+=yacc*milliseconds ;
        zspeed+=zacc*milliseconds ;
    }
    
    ypos+=(yspeed*milliseconds) ;
    xpos+=(xspeed*milliseconds) ;
    zpos+=(zspeed*milliseconds) ;
    
    
    life-=fade*milliseconds;		// Reduce Particles Life By 'Fade'

    // calculate distance to viewer
    // sqrt((-camx+partx)^2+(-camz+partz)^2)
 /*   float distance;
    distance=sqrt(partGroup->
    if(*/

}

void Part::Draw( )
{
    if(visible)
    {
     //   cout << "Draw Part at: " << xpos << " / " << ypos << " / " << zpos << endl;
    
        glPushMatrix();
    	glTranslatef (xpos, ypos, zpos);							// Translate to Particle Position
    
    	glRotatef(angley, 0.0f, 1.0f, 0.0f);
    	glRotatef(anglex, 1.0f, 0.0f, 0.0f);
    
        glColor4f(r,g,b, life);
        glCallList(dispList); 
    	glPopMatrix();
    	//cout << "Finished Draw Part" << endl;
    }
}



Particle::Particle(World *world, zTerrain *terrain, Uint16 num, float x, float y, float z):
    motherTerrain(terrain)
{
    this->motherWorld=world;
    posx=x;
    posy=y;
    posz=z;
    for(int cnt=0; cnt<num; cnt++)
    {
        Parts.push_back(new Part(this));

    }
    cout << "Creating " << num <<" Particles" << endl;
}


Particle::Particle(World *world, zTerrain *terrain, Uint16 num):
    motherTerrain(terrain)
{
    this->motherWorld=world;
    posx=64.0f;
    posy=0.5f;
    posz=64.0f;
    for(int cnt=0; cnt<num; cnt++)
    {
        Parts.push_back(new Part(this));

    }
    cout << "Creating " << num <<" Particles" << endl;
}

Particle::Particle(World *world, zTerrain *terrain, Uint16 num, float x, float y, float z,
                    float angley,unsigned texture )
{
    this->motherWorld=world;
    this->motherTerrain=terrain;
    posx=x;
    posy=y;
    posz=z;
    this->texture=texture;
    this->angley=angley;
    for(int cnt=0; cnt<num; cnt++)
    {
        Parts.push_back(new Part(this, Part::colorsBlue));

    }
    cout << "Creating " << num <<" Particles" << endl;

}

Particle::~Particle()
{
    for(;Parts.size();)
    {
        delete Parts[Parts.size()-1];
        Parts.pop_back();
    }
}



void Particle::Update(Uint32 milliseconds, Uint8 *keystate)
{
    //cout << "Updating Particles" << endl;
    std::vector<Part *>::iterator part;
    for(part=Parts.begin(); part<Parts.end(); part++)
    {
        (*part)->Update(milliseconds);
    }
}

void Particle::Draw( )
{
    //cout << "draw Particles at " << posx << " / " << posy << " / " << posz << endl;
    glPushMatrix();
	glTranslatef (posx, posy, posz);							// Translate to Particle Position
	
    glRotatef (anglex, 1.0f, 0.0f, 0.0f);						// Rotate On The X-Axis By angle
	glRotatef (angley, 0.0f, 1.0f, 0.0f);						// Rotate On The Y-Axis By angle
	glRotatef (anglez, 0.0f, 0.0f, 1.0f);						// Rotate On The Z-Axis By angle
   


    glEnable(GL_TEXTURE_2D);// Texture Mapping aktivieren
    glBindTexture(GL_TEXTURE_2D, texture);    
    glAlphaFunc ( GL_GREATER, 0.01 ) ;
    glEnable ( GL_ALPHA_TEST ) ;
    
	glEnable(GL_BLEND);							                 // Enable Blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);					         // Type Of Blending To Perform
//	glDisable(GL_DEPTH_TEST);
    //glBlendFunc(GL_DST_COLOR,GL_ZERO);
    //glEnable(GL_POINT_SMOOTH);                                 // Enable Nice looking points
    //glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA);  
    //glBlendFunc(GL_SRC_COLOR,GL_DST_ALPHA);  

    glEnable(GL_POLYGON_STIPPLE);
    vector<Part *>::iterator part;
	Angle angle;
    motherWorld->GetCamAngle(&angle);
    for(part=Parts.begin(); part<Parts.end(); part++)
    {   
        // --- Turn Part (more or less) in direction of viewer ---
        (*part)->setAngleX(-angle.x);
        (*part)->setAngleY(-angle.y);
        (*part)->Draw();
    }
    glDisable(GL_POLYGON_STIPPLE);

    //glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA); 
    glDisable(GL_TEXTURE_2D);  
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
   // glEnable(GL_DEPTH_TEST);
   // glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA);					         // Type Of Blending To Perform   
    glPopMatrix();
}


void Particle::Draw(float anglex, float angley, float anglez)
{
    //cout << "draw Particles at " << posx << " / " << posy << " / " << posz << endl;
    glPushMatrix();
	glTranslatef (posx, posy, posz);							// Translate to Particle Position
	
    glRotatef (anglex, 1.0f, 0.0f, 0.0f);						// Rotate On The X-Axis By angle
	glRotatef (angley, 0.0f, 1.0f, 0.0f);						// Rotate On The Y-Axis By angle
	glRotatef (anglez, 0.0f, 0.0f, 1.0f);						// Rotate On The Z-Axis By angle
   


    glEnable(GL_TEXTURE_2D);// Texture Mapping aktivieren
    glBindTexture(GL_TEXTURE_2D, texture);    
    glAlphaFunc ( GL_GREATER, 0.01 ) ;
    glEnable ( GL_ALPHA_TEST ) ;
    
	glEnable(GL_BLEND);							                 // Enable Blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);					         // Type Of Blending To Perform
//	glDisable(GL_DEPTH_TEST);
    //glBlendFunc(GL_DST_COLOR,GL_ZERO);
    //glEnable(GL_POINT_SMOOTH);                                 // Enable Nice looking points
    //glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA);  
    //glBlendFunc(GL_SRC_COLOR,GL_DST_ALPHA);  

    glEnable(GL_POLYGON_STIPPLE);
    vector<Part *>::iterator part;
    
    for(part=Parts.begin(); part<Parts.end(); part++)
    {   
        (*part)->Draw();
    }
    glDisable(GL_POLYGON_STIPPLE);

    //glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA); 
    glDisable(GL_TEXTURE_2D);  
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
   // glEnable(GL_DEPTH_TEST);
   // glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA);					         // Type Of Blending To Perform   
    glPopMatrix();
}

float Particle::getGround(float x, float z)
{
    return motherTerrain->GetMapY(x+posx, z+posz);
}

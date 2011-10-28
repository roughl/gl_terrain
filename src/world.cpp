// world.cpp

#include "World.hpp"

#include <iostream>
#include <cmath>
#include <SDL/SDL.h>
#include "LuaFuncs.h"

#include "OpenGL.h"
#include "VectorCalc.hpp"
#include "sphere.hpp"


using namespace std;

World::World(lua_State *luaState):
	L(luaState),
	oldpos(64.0f, 64.0f, 25.0f),
	pos(oldpos),
	angle(0,0,0)
{
    posyoffset=0.0f;
    
    
    zspeed=0.05f;
    xspeed=0.05f;
    yspeed=0.0f;
    
    turnspeed=0.1f;
    mousespeed=0.5f;
    gravity=2.0f;
    maxheight=2.0f;
    
    jumpvelocity=0.1f;
    
    waterlevel=1.0f;

    drawtop=false;
    drawbuttom=false;
    drawleft=false;
    drawright=false;
}

World::~World()
{
    for(;terrain.size();)
    {
        delete terrain[terrain.size()-1];
        terrain.pop_back();
    }
    for(;objects.size();)
    {
        delete objects[objects.size()-1];
        objects.pop_back();
    }
}

bool World::Create(const char* fileName)
{
    const char *Map;
    if (luaL_loadfile(L, fileName)==0)
    {
        // execute Lua program or script
        lua_pcall(L, 0, LUA_MULTRET, 0);
        Map=lua_GetString(L, "map");
        zspeed= lua_GetNumber(L, "zspeed");
        xspeed= lua_GetNumber(L, "xspeed");
        turnspeed= lua_GetNumber(L, "turnspeed");
        mousespeed= lua_GetNumber(L, "mousespeed");
        waterlevel= lua_GetNumber(L, "waterlevel");
        gravity= lua_GetNumber(L, "gravity");
        jumpvelocity= lua_GetNumber(L, "jumpvelocity");
        maxheight= lua_GetNumber(L, "maxheight");
        
    }
    else
    {
        Map="Data/Default.bmp";
    }
    cout << "--- Creating Terrain ---"<<endl;
    terrain.push_back(new zTerrain(L, this));
    if( !terrain[0]->Create(Map) ) {
		cout << "Creating Terrain failed!" << endl;
		return false;
	}
    cout << "--- Terrain Finished! ---"<<endl;
	return true;
}



lua_State *World::getLuaState()
{
    return L;
}

void World::Update (SDL_KeyboardEvent *keyevent)
{
    switch(keyevent->keysym.sym)
    {
    case SDLK_KP_PLUS:
	case SDLK_PLUS:
        if(keyevent->type==SDL_KEYUP)
        {
            float x, y, z, size;
            x=( (float)rand()/RAND_MAX )* terrain[0]->GetWidth();
            z=( (float)rand()/RAND_MAX )* terrain[0]->GetHeight();
            size=(float)rand()/(RAND_MAX/1.0)+1.0; // between 1.0 and 2.0
            y=terrain[0]->GetMapY(x, z)+size*1.8f;

            cout << "creating cube at " << x << " / " << y << " / ";
            cout << z << " with size " << size << endl;

			Cube *cub = new Cube();
			cub->Create(x,y,z,size);
            
            objects.push_back( cub );
            /*
            objects.push_back( new Sphere(this) );
            spheres.back()->Create(x,y,z,size);*/
        }
        break;
    case SDLK_KP_MINUS: 
	case SDLK_MINUS:
        if(keyevent->type==SDL_KEYUP)
        {
            if(objects.size())
            {
                delete objects.back();
                objects.pop_back();
            }
        }
        break;
    case 'p':
        if(keyevent->type==SDL_KEYDOWN)
            {
                printf("current State:\n");
                printf("pos.x= %f\tpos.y= %f\tpos.z= %f\n", pos.x, pos.y, pos.z);     
                cout << "angle.y: " << angle.y << " -> ";
                if(drawtop) cout << "drawtop ";
                if(drawbuttom) cout << "drawbuttom ";
                if(drawright) cout << "drawright ";
                if(drawleft) cout << "drawleft ";
                cout << endl;
            }
        break;
        
    case SDLK_SPACE:
        if(keyevent->type==SDL_KEYDOWN)
        {
        //    if(yspeed==0)
             //   yspeed+=jumpvelocity;
        }
        else
        {
        }
        break;
    }
}


void World::Update (Uint32  milliseconds, Uint8 *keystate)								// Perform Motion Updates Here
{
    terrain[0]->Update(milliseconds, keystate);
  //  cout << "Entering Upddate..." << endl;
    srand(SDL_GetTicks());
	if (keystate[SDLK_UP] || keystate['w'])
	{
        pos.z-=cos(angle.y/180.0f*M_PI)*(float)(milliseconds)*zspeed; // / 20.0f;
        pos.x+=sin(angle.y/180.0f*M_PI)*(float)(milliseconds)*xspeed; // / 20.0f;
    }
	if (keystate[SDLK_DOWN] || keystate['s'])
	{
        pos.z+=cos(angle.y/180.0f*M_PI)*(float)(milliseconds)*zspeed; // / 20.0f;
        pos.x-=sin(angle.y/180.0f*M_PI)*(float)(milliseconds)*xspeed; // / 20.0f;
    }
    if (keystate[SDLK_RIGHT] || keystate['d'])
    {
        pos.z-=cos((angle.y+90)/180.0f*M_PI)*(float)(milliseconds)*zspeed; // / 20.0f;
        pos.x+=sin((angle.y+90)/180.0f*M_PI)*(float)(milliseconds)*xspeed; // / 20.0f;
    }
    if (keystate[SDLK_LEFT] || keystate['a'])
    {
        pos.z-=cos((angle.y-90)/180.0f*M_PI)*(float)(milliseconds)*zspeed; // / 20.0f;
        pos.x+=sin((angle.y-90)/180.0f*M_PI)*(float)(milliseconds)*xspeed; // / 20.0f;
    }
	if (keystate['q'] )
	{
	   angle.y -= (float)(milliseconds) * turnspeed;						// Update angle Based On The Clock
	   if(angle.y<0)
	       angle.y=360.0f;
	}
	if (keystate['e'] )
	{
	   angle.y += (float)(milliseconds) * turnspeed;						// Update angle Based On The Clock
	   if(angle.y>360)
	       angle.y=0.0f;
	}


   /* if(pos.x > width-1)  pos.x = width-1;
    if(pos.x < 0)        pos.x = 0.0f;
    if(pos.z > height-1) pos.z = height-1;
    if(pos.z < 0)        pos.z = 0.0f;    
    */
    if(pos.x > terrain[0]->GetWidth()-1)  pos.x = 0.0f;
    if(pos.x < 0)        pos.x = terrain[0]->GetWidth()-1;
    if(pos.z > terrain[0]->GetHeight()-1) pos.z = 0.0f;
    if(pos.z < 0)        pos.z = terrain[0]->GetHeight()-1;    
    
    if (keystate[SDLK_PAGEUP])
    {
      // pos.y+=1.0f;
        
	   angle.x -= (float)(milliseconds) * turnspeed;						// Update angle Based On The Clock
	   if(angle.x<-60.0f)
	       angle.x=-60.0f;/**/
    }
    if (keystate[SDLK_PAGEDOWN])
    {
       //pos.y-=1.0f; 
	   angle.x += (float)(milliseconds) * turnspeed;						// Update angle Based On The Clock
	   if(angle.x>60.0f)
	       angle.x=60.0f;/**/
    }
    
    
    if (keystate['r']) // reset position
    {
        pos.x=+64.0f;
        pos.z=+64.0f;
    }

	// jetpack style
	if (keystate[SDLK_SPACE])
	{
		yspeed += (gravity+gravity/10.0f)*milliseconds;
	}

    vector<IObject *>::iterator obj;
    for(obj=objects.begin(); obj<objects.end(); obj++)
    {
        (*obj)->Update(milliseconds, keystate);
    }
    
   // cout << "Calculating ypos" << endl;
    float mapheight, futmapheight;//deltax=pos.x-oldpos.x, deltaz=pos.z-oldpos.z;
   // cout << "Calculating Y-Position" << endl;
    mapheight=terrain[0]->GetMapY(pos.x, pos.z) +2.0f;
    
    //if(deltax>0.0f/* && deltax< 1.0f*/) deltax= 1.0f;
    //if(deltax<0.0f/* && deltax>-1.0f*/) deltax=-1.0f;
    //if(deltaz>0.0f/* && deltaz< 1.0f*/) deltaz= 1.0f;
    //if(deltaz<0.0f/* && deltaz>-1.0f*/) deltaz=-1.0f;
    
    futmapheight=terrain[0]->GetMapY((float)(pos.x-sin(angle.y/180.0f*M_PI)), (float)(pos.z+cos(angle.y/180.0f*M_PI)) ) +2.0f;
    pos.y+=yspeed*milliseconds;
    
    if(pos.y < mapheight) //we are climbing
    {
        //cout << "We are climbing" << endl;
        if(yspeed<0.0f)   
            yspeed=0.0f;
        // maximal climb
        if(mapheight>pos.y+maxheight || futmapheight>pos.y+maxheight)
        {
            pos.x=oldpos.x;
            pos.z=oldpos.z;
            pos.y=oldpos.y;
        }
        else
        {
            pos.y=mapheight;
        }
    }
    // we are falling
    else if( pos.y>mapheight )
    {
        //cout << "We are falling yspeed = "<<yspeed << endl;
        yspeed-=gravity*milliseconds;
    }
    else if( pos.y==mapheight)
    {
        //cout << "We are on Ground" << endl;
        yspeed=0.0f;
    }
  
    oldpos.x=pos.x;
    oldpos.z=pos.z;
    oldpos.y=pos.y;
    if(pos.x>(terrain[0]->GetWidth()/2.0f)+2.0f  &&  ( angle.y>(360-45) || angle.y < (180.0f+45.0f) ) )
    {
        drawright=true;
    }
    else
    {
        drawright=false;
    }
    
    if(pos.x< (terrain[0]->GetWidth()/2.0f)-2.0f && (angle.y> (180.0f-45.0f) || angle.y<(45.0f) ))
    {
        drawleft=true;
    }
    else
    {
        drawleft=false;
    }
    
    if(pos.z<(terrain[0]->GetHeight()/2.0f)-2.0f && ( angle.y < (90.0f+45.0f) || angle.y > (270.0f-45.0f)))
    {
        drawtop=true;
    }
    else
    {
        drawtop=false;
    }
    if(pos.z> (terrain[0]->GetHeight()/2.0f)+2.0f && (angle.y > (90.0f-45.0f) && angle.y < (270.0f+45.0f)))
    {
       drawbuttom=true;
    }
    else
    {
        drawbuttom=false;
    }
   // cout << "pos.x= " << pos.x << " pos.z = " << pos.z << "\n";
   // cout << "aheightmap[" << ind((int)fabs(pos.x), (int)fabs(pos.z)) <<"] = ";
   // cout << aheightmap[ind((int)fabs(pos.x), (int)fabs(pos.z))];
   // cout << "-> pos.y = " << pos.y <<"\n";

}




void World::Update(SDL_MouseMotionEvent *mouse)
{
    angle.x += (float) mouse->yrel * mousespeed;
    if(angle.x>90.0f)
	    angle.x=90.0f;/**/
	if(angle.x<-90.0f)
	    angle.x=-90.0f;/**/
	    
    angle.y += (float) mouse->xrel * mousespeed;
    if(angle.y>360)
	    angle.y=angle.y-360.0f;
	if(angle.y<0)
	    angle.y=360.0f+angle.y;  
}


void World::Update()
{
    
}

void World::DrawChildren(void)
{
    std::vector<zTerrain *>::iterator terrainIt;
    for(terrainIt=terrain.begin(); terrainIt<terrain.end(); terrainIt++)
    {
        (*terrainIt)->Draw();
    }
    
    vector<IObject *>::iterator it;
    for(it=objects.begin(); it<objects.end(); it++)
    {
        (*it)->Draw();
    }
}


void World::Draw(void)
{
    //std::cout << "Drawing Terrain at " << posx << " / " << posy << " / " << posz << " / ";

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear Screen And Depth Buffer
	glLoadIdentity ();											// Reset The Modelview Matrix
	
	// --- Go to Cam Pos ---
	glRotatef (angle.x, 1.0f, 0.0f, 0.0f);						// Rotate On The X-Axis By angle
	glRotatef (angle.y, 0.0f, 1.0f, 0.0f);						// Rotate On The Y-Axis By angle
	glRotatef (angle.z, 0.0f, 0.0f, 1.0f);						// Rotate On The Z-Axis By angle
	glTranslatef (-this->pos.x, -this->pos.y, -this->pos.z);	// Translate to Cam Pos
	
	static const float max = 100.0f;
	static const float min = 100.0f;
    static Cube mycube;
	static float speed =  0.10f;
    static float pos[4] = {(float)terrain[0]->GetWidth()*2, max, (float)terrain[0]->GetHeight()*2, 1.0f};
	static float amb[4] = {0.01f, 0.01f, 0.01f, 1.0f};
	static float dif[4] = {0.5f, 0.5f, 0.5f, 1.0f};
	static float spec[4]= {1.0f, 1.0f, 1.0f, 1.0f};
    GL_SetLight(pos, amb, dif, spec);
    mycube.Create(pos[0],pos[1],pos[2],1.0f);
	pos[1]+=speed;
	if(pos[1] >= max){
		speed = -speed;
		pos[1]=max;
	}
	else if(pos[1] <= min){
		speed = -speed;
		pos[1]=min;
	}
	mycube.Draw();


    DrawChildren();
    
    if(drawright)
    {
        glPushMatrix();
        glTranslatef(terrain[0]->GetWidth(), 0.0f, 0.0f);
        DrawChildren();
        glPopMatrix();
    }
    if(drawleft)
    {
        glPushMatrix();
        glTranslatef(-(terrain[0]->GetWidth()), 0.0f, 0.0f);
        DrawChildren();
        glPopMatrix();
    }
    
    if(drawtop)
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -terrain[0]->GetHeight());
        DrawChildren();
        if(drawright)
        {
            glTranslatef(terrain[0]->GetWidth(), 0.0f, 0.0f);
            DrawChildren();
            glTranslatef(-terrain[0]->GetWidth(), 0.0f, 0.0f);
        }
        if(drawleft)
        {
            glTranslatef(-(terrain[0]->GetWidth()), 0.0f, 0.0f);
            DrawChildren();
        }
        glPopMatrix();
    }
    if(drawbuttom)
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, terrain[0]->GetHeight());
        DrawChildren();
        if(drawright)
        {
            glTranslatef(terrain[0]->GetWidth(), 0.0f, 0.0f);
            DrawChildren();
            glTranslatef(-terrain[0]->GetWidth(), 0.0f, 0.0f);
        }
        if(drawleft)
        {
            glTranslatef(-(terrain[0]->GetWidth()), 0.0f, 0.0f);
            DrawChildren();
        }
        glPopMatrix();
    }/**/


	glFlush ();													// Flush The GL Rendering Pipeline
}


// Get Value for Depth Buffer
float World::GetDepth()
{
    cout << "Getting depth\n";
    cout << "terrain[0]->GetWidth() = " << terrain[0]->GetWidth() << endl;
    if(terrain[0]->GetWidth()>terrain[0]->GetHeight())
    {
        cout << ((float)terrain[0]->GetWidth()/2.0f)-2.0f;
        cout << "\n";
        return ((float)terrain[0]->GetWidth()/2.0f)-2.0f;
    }
        cout << ((float)terrain[0]->GetHeight()/2.0f)-2.0f;
        cout << "\n";
    return ((float)terrain[0]->GetHeight()/2.0f)-2.0f;
}

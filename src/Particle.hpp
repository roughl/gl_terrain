// Particle.hpp

#ifndef __PARTICLE_HPP
#define __PARTICLE_HPP

#include "Object.hpp"
#include <vector>
#include <GL/gl.h>

class World;
class zTerrain;
class Particle;

class Part
{
public:
    Part(Particle *group);
    Part(Particle *group, const float colortable[][3]);
    void Update(Uint32 milliseconds);
    void Draw();
    static const float colors[12][3];			// Rainbow Of Colors
    static const float colors2[12][3];			// Rainbow Of Colors
    static const float colors3[12][3];			// Rainbow Of Colors
    static const float colors4[12][3];			// Rainbow Of Colors
    static const float colorsred[12][3];			// Rainbow Of Colors
    static const float colorsBlue[12][3];			// Rainbow Of Colors
    static const float colorsBlueWhite[12][3];
    
    void setAngleX(float angle){anglex=angle;}
    void setAngleY(float angle){angley=angle;}
    
private:
	float	life;					// Particle Life
	float	fade;					// Fade Speed
    Particle *partGroup;
    float xpos, ypos, zpos;         // positions
    float anglex, angley;
    float r,g,b;                    // colors
    float xspeed, yspeed, zspeed;   // speed
    float xacc, yacc, zacc;       
    GLuint dispList;
    bool visible;
};



class Particle : Object
{
public:
    Particle(World *world, zTerrain *terrain, Uint16 num);
    Particle(World *world, zTerrain *terrain, Uint16 num, float x, float y, float z);
    Particle(World *world, zTerrain *terrain, Uint16 num, float x, float y, float z, float angley, unsigned texture);
    ~Particle();
    //void Create();
    float getGround(float x, float z);
    void Update(Uint32 milliseconds, Uint8 *keystate);
    void Draw();
    void Draw(float Xangle, float Yangle, float Zangle);
protected:
private:
    zTerrain *motherTerrain;
    std::vector <Part *> Parts;
    GLuint texture;
};    

#endif //__PARTICLE_HPP

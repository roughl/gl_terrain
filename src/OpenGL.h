// OpenGL.h

#include <GL/gl.h>
#include <GL/glu.h>												// Header File For The GLu32 Library

#ifndef __OPENGL_H
#define __OPENGL_H

typedef struct{
    float x,y,z;
}stVec;

typedef struct {
  unsigned char  r;
  unsigned char  g;
  unsigned char  b;
  unsigned char  a;
} Pixel;

unsigned LoadAlphaTexture(const char *filename);
unsigned LoadTexture(const char *filename);
void ReshapeGL (int width, int height, float depth=100);
bool InitializeGL (void);
void DeinitializeGL(void);
void GL_SetLight(float *Position, float *Ambient, float *div, float *spec);
GLvoid CalculateVectorNormal(GLfloat fVert1[], GLfloat fVert2[],
                             GLfloat fVert3[], GLfloat fNormal[]);
#endif // __OPENGL_H

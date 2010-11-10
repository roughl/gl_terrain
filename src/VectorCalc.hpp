// VectorCalc.hpp

#ifndef __VECTOR_CALC_HPP
#define __VECTOR_CALC_HPP

#include "World.hpp"

class vec
{
public:
    static GLfloat getDistance(const Pos &world, const Pos &object);    
	static GLvoid  CalculateVectorNormal(GLfloat fVert1[], GLfloat fVert2[],
                             GLfloat fVert3[], GLfloat fNormal[]);
	static GLfloat scalarProduct(GLfloat fVert1[], GLfloat fVert2[]);
    
};


#endif // __VECTOR_CALC_HPP

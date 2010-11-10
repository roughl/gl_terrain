// VectorCalc.cpp

#include "VectorCalc.hpp"

#include <cmath>
#include <iostream>

#include "World.hpp"

using namespace std;

GLfloat vec::getDistance( const Pos &world, const Pos &object)
{   
    cout << "getDistance("<<&world << ", " <<&object <<");"<< endl;
    GLfloat distance=sqrt( (-(world.x)+(object.x))*(-world.x+object.x) + (-world.z+object.z)*(-world.z+object.z));
    std::cout << "Distance is: " << distance << std::endl;
    return distance;
}

GLvoid vec::CalculateVectorNormal(GLfloat fVert1[], GLfloat fVert2[],
                             GLfloat fVert3[], GLfloat fNormal[])
{
   GLfloat Qx, Qy, Qz, Px, Py, Pz;

   Qx = fVert2[0]-fVert1[0];
   Qy = fVert2[1]-fVert1[1];
   Qz = fVert2[2]-fVert1[2];
   Px = fVert3[0]-fVert1[0];
   Py = fVert3[1]-fVert1[1];
   Pz = fVert3[2]-fVert1[2];

   fNormal[0] = Py*Qz - Pz*Qy;
   fNormal[1] = Pz*Qx - Px*Qz;
   fNormal[2] = Px*Qy - Py*Qx;

   // i² * (fNormal[0]² + fNormal[1]² + fNormal[2]²) = 1
   GLfloat i = sqrt(1 / (fNormal[0]*fNormal[0] + fNormal[1]*fNormal[1] + fNormal[2]*fNormal[2]));
   fNormal[0] = i*fNormal[0];
   fNormal[1] = i*fNormal[1];
   fNormal[2] = i*fNormal[2];

}
GLfloat vec::scalarProduct(GLfloat u[3], GLfloat v[3])
{
	return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

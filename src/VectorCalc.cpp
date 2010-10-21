// VectorCalc.cpp

#include "VectorCalc.hpp"

#include <cmath>
#include <iostream>

#include "World.hpp"

using namespace std;

float vec::getDistance(Pos *world, Pos *object)
{   
    cout << "getDistance("<<world << ", " <<object <<");"<< endl;
    float distance=sqrt( (-(world->x)+(object->x))*(-world->x+object->x) + (-world->z+object->z)*(-world->z+object->z));
    std::cout << "Distance is: " << distance << std::endl;
    return distance;
}

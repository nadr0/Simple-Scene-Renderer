#include "Ray.h"
#include "Vec4.h"

// Default Constructor
Ray::Ray()
    :   o(0.0,0.0,0.0),
        d(0.0,0.0,0.0)
{}


// Overloaded Constructor
// Takes a vector for the origin position and direction
Ray::Ray(Vec4 & origin, Vec4 & direction)
    :   o(origin),
        d(direction)
{}

// Assignment operator
// Takes a ray to set the left side equal to the ray.
Ray & Ray::operator=(Ray & rhs){

    if(this != &rhs){
        o = rhs.o;
        d = rhs.d;
    }

    return *this;
}

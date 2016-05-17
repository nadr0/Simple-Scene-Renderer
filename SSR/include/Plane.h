#ifndef PLANE_H_
#define PLANE_H_
#include "GeometricObject.h"

class Plane : public GeometricObject{
public:
    Plane();
    Plane(Vec4 p, Vec4 n);
    virtual bool hit(Ray & ray, double & tmin, ShadeRec & sr);
    virtual bool shadow_hit(Ray & ray, float & tmin) ;
    Vec4 point;
    Vec4 normal;
    double kEpsilon;

};
#endif

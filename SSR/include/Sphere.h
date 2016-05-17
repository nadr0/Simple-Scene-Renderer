#ifndef SPHERE_H_
#define SPHERE_H_

#include "Ray.h"
#include "ShadeRec.h"
#include "Vec4.h"
#include "GeometricObject.h"
#include "MultiJitter.h"

class Ray;
class ShadeRec;

class Sphere: public GeometricObject{
public:

    Sphere();
    Sphere(Vec4 & c, double r);
    virtual bool hit(Ray & ray, double & tmin, ShadeRec & sr);
    bool shadow_hit(Ray & ray, float & tmin);
    float pdf(ShadeRec & sr);
    Vec4 get_normal(Vec4 p);
    void compute_BBox();
    MultiJitter * sampler_ptr;
    virtual Vec4 sample();
    Vec4 center;
    double radius;
    double kEpsilon;

};
#endif

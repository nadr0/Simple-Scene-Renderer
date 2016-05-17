#ifndef TRIANGLE_H_
#define TRIANGLE_H_
#include "GeometricObject.h"

class Triangle: public GeometricObject{
public:
    Triangle();
    Triangle(Vec4 & a, Vec4 & b, Vec4 & c, Vec4 & n);
    virtual bool hit(Ray & ray, double & tmin, ShadeRec & sr);
    virtual bool shadow_hit(Ray & ray, float & tmin);
    void compute_BBox();

    // 3 points to define a triangle
    Vec4 a;
    Vec4 b;
    Vec4 c;

    // Normal for the triangle
    Vec4 normal;

    double kEpsilon;

};

#endif

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "GeometricObject.h"
#include "MultiJitter.h"

class Rectangle: public GeometricObject{
public:
    Rectangle();
    Rectangle(Vec4 p0, Vec4 _a, Vec4 _b, Vec4 n);
    virtual bool hit(Ray & ray, double &t, ShadeRec & s);
    virtual bool shadow_hit(Ray & ray, float & tmin);
    virtual Vec4 sample();
    virtual Vec4 get_normal(Vec4 p);
    virtual float pdf(ShadeRec & sr);
    void compute_bbox();
    Vec4 p0; // corner vertex
    Vec4 a;
    Vec4 b;
    double a_len_squared;
    double b_len_squared;
    Vec4 normal;

    float area;
    float inv_area;
    MultiJitter * sampler_ptr;

    double kEpsilon;
};


#endif

#ifndef DISK_H_
#define DISK_H_

#include "GeometricObject.h"
#include "MultiJitter.h"

class Disk : public GeometricObject{
public:
    Disk();
    Disk(Vec4 c, Vec4 n, float r);
    virtual bool hit(Ray & ray, double & tmin, ShadeRec & sr);
    virtual bool shadow_hit(Ray & ray, float & tmin);
    virtual Vec4 sample();
    virtual Vec4 get_normal(Vec4 p);
    virtual float pdf(ShadeRec & sr);
    void compute_bbox();
    Vec4 center;
    Vec4 normal;
    double kEpsilon;
    float radius;

    float area;
    float inv_area;
    MultiJitter * sampler_ptr;

};
#endif

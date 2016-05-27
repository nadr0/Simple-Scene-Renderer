#ifndef DISK_H_
#define DISK_H_

#include "GeometricObject.h"

class Disk : public GeometricObject{
public:
    Disk();
    Disk(Vec4 c, Vec4 n, float r);
    virtual bool hit(Ray & ray, double & tmin, ShadeRec & sr);
    virtual bool shadow_hit(Ray & ray, float & tmin);
    void compute_bbox();
    Vec4 center;
    Vec4 normal;
    double kEpsilon;
    float radius;
};
#endif

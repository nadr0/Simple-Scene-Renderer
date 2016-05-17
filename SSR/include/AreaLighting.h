#ifndef AREALIGHTING_H_
#define AREALIGHTING_H_

#include "Tracer.h"
#include "Ray.h"
#include "World.h"

class AreaLighting: public Tracer{
public:
    virtual RGBColor trace_ray(Ray & ray, int depth);
    AreaLighting();
    AreaLighting(World * w_ptr);
};
#endif

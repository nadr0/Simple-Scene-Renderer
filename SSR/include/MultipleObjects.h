#ifndef MULTIPLEOBJECTS_H
#define MULTIPLEOBJECTS_H

#include "Tracer.h"
#include "RGBColor.h"
#include "Ray.h"
#include "World.h"

class MultipleObjects: public Tracer{
public:
    virtual RGBColor trace_ray(Ray & ray, int depth);
    MultipleObjects();
    MultipleObjects(World * w_ptr);
};


#endif

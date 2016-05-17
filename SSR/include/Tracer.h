#ifndef TRACER_H_
#define TRACER_H_


#include "Ray.h"
#include "World.h"

class World;


class Tracer{
public:

    Tracer();
    Tracer(World * w_ptr);
    virtual RGBColor trace_ray(Ray & ray, int depth);
    World * world_ptr;

};
#endif

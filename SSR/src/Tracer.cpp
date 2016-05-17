#include <stddef.h>
#include "Tracer.h"
#include "ShadeRec.h"

Tracer::Tracer(){
    world_ptr = NULL;
}

Tracer::Tracer(World * w_ptr){
    world_ptr = w_ptr;
}

RGBColor Tracer::trace_ray(Ray & ray, int depth){
    ShadeRec sr(world_ptr);
    double t;

    return RGBColor();
}

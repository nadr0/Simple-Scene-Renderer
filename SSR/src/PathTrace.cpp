#include "PathTrace.h"

PathTrace::PathTrace(){}

PathTrace::PathTrace(World * w_ptr){
    world_ptr = w_ptr;
}

RGBColor PathTrace::trace_ray(Ray & ray, int depth){

    if(depth > world_ptr->vp.maxDepth){
        return (black);
    }else{

        ShadeRec sr(world_ptr->hit_bare_bones_objects(ray));

        if(sr.hit_an_object){
            sr.depth = depth;
            sr.ray = ray;
            return (sr.material_ptr->path_shade(sr));
        }else{
            return (world_ptr->background_color);
        }
    }

}

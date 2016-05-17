#include "MultipleObjects.h"

MultipleObjects::MultipleObjects(){};


MultipleObjects::MultipleObjects(World * w_ptr){
    world_ptr = w_ptr;
}


RGBColor MultipleObjects::trace_ray(Ray & ray, int depth){
    ShadeRec sr(world_ptr->hit_bare_bones_objects(ray));

    if(sr.hit_an_object){
        sr.ray = ray;
        return sr.material_ptr->shade(sr);
    }else{
        return world_ptr->background_color;
    }

}

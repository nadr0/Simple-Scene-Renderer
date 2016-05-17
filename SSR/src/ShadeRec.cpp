#include "ShadeRec.h"

ShadeRec::ShadeRec(World * wr)
    :   w(wr),
        hit_an_object(false),
        local_hit_point(),
        normal(),
        color(),
        ray(),
        hit_point(),
        depth(0),
        u(0.0),
        v(0.0)
{}

ShadeRec::ShadeRec(ShadeRec const &sr){
    this->w = sr.w;
    this->hit_an_object = sr.hit_an_object;
    this->local_hit_point = sr.local_hit_point;
    this->normal = sr.normal;
    this->hit_point = sr.hit_point;
    this->material_ptr = sr.material_ptr;
    this->ray.o = sr.ray.o;
    this->ray.d = sr.ray.d;
    this->depth = sr.depth;
}

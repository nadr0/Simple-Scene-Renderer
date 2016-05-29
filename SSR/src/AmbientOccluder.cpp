#include <iostream>
#include "AmbientOccluder.h"

using std::cout;
using std::endl;

AmbientOccluder::AmbientOccluder(){
    min_amount = RGBColor(0.0,0.0,0.0);
}


void AmbientOccluder::set_sampler(Sampler * s_ptr){
    sample_ptr = s_ptr;
    sample_ptr->map_samples_to_hemisphere(1);
}

Vec4 AmbientOccluder::get_direction(ShadeRec & sr){
    Vec4 sp = sample_ptr->sample_hemisphere();
    return (sp.x() * u + sp.y() * v + sp.z() * w);
}

bool AmbientOccluder::in_shadow(Ray & ray, ShadeRec & sr){
    vector<GeometricObject *> tempObjs;
    BVH_TRAVERSE(ray,sr.w->flat_BVH,tempObjs,sr.w);
    // hitBBox(ray, sr.w->BVH_root, tempObjs);
    float t;
    int num_objects = tempObjs.size();
    for (int j = 0; j < num_objects; j++) {

        if(tempObjs[j]->shadow_hit(ray,t)){
            return true;
        }

    }
    return false;
}

RGBColor AmbientOccluder::L(ShadeRec & sr){
    w = sr.normal;
    // v = cross(w,Vec4(0.0072,1.0,0.0034));
    // v = normalize(v);
    // u = cross(v,w);
    // Building an Orthonormal Basis from a 3D Unit Vector Without Normalization
    float a = 1.0f/(1.0f + w.z());
    float b = -w.x()*w.y()*a;
    u = Vec4(b,1.0f - w.y()*w.y()*a, -w.y());
    v = Vec4(1.0f - w.x()*w.x()*a, b, -w.x());

    Ray shadow_ray;
    shadow_ray.o = sr.hit_point;
    shadow_ray.d = get_direction(sr);

    if(in_shadow(shadow_ray,sr)){
        return (color * ls * min_amount);
    }else{
        return (color * ls);
    }

}

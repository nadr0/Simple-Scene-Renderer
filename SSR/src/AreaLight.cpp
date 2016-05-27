#include <iostream>
#include "AreaLight.h"

using std::cout;
using std::endl;

AreaLight::AreaLight(){
    obj_ptr = 0;
    material_ptr = 0;
    sample_point = Vec4(0.0,0.0,0.0);
    light_normal = Vec4(0.0,0.0,0.0);
    wi = Vec4(0.0,0.0,0.0);
}

Vec4 AreaLight::get_direction(ShadeRec &sr){
    light_normal = obj_ptr->get_normal(sample_point);
    sample_point = obj_ptr->sample();
    wi= sample_point - sr.hit_point;
    wi = normalize(wi);

    return wi;
}


RGBColor AreaLight::L(ShadeRec & sr){
    float ndotd = dot(-light_normal, wi);

    if(ndotd > 0.0){
        return (material_ptr->get_Le(sr));
    }else{
        return RGBColor(0.0,0.0,0.0);
    }
}

bool AreaLight::in_shadow(Ray & ray, ShadeRec & sr){
    vector<GeometricObject *> tempObjs;
    hitBBox(ray, sr.w->BVH_root, tempObjs);

    float t;
    int num_objects = tempObjs.size();
    Vec4 direction = (sample_point - ray.o);
    float ts = dot(direction, ray.d);

    for (int j = 0; j < num_objects; j++) {

        if (tempObjs[j]->shadow_hit(ray, t) && t < ts){
            return true;
        }

    }
    return false;
}


float AreaLight::G(ShadeRec & sr){
    float ndotd = dot(-light_normal, wi);
    float d2 = distance(sample_point, sr.hit_point);
    float distance_squared = d2 * d2;

    return ndotd/distance_squared;
}

float AreaLight::pdf(ShadeRec & sr){
    return obj_ptr->pdf(sr);
}

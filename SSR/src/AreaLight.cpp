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
    sample_point = obj_ptr->sample();
    light_normal = obj_ptr->get_normal(sample_point);
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

    float t;
    int num_objects = sr.w->objects.size();
    Vec4 direction = (sample_point - ray.o);
    float ts = dot(direction, ray.d);

    for (int j = 0; j < num_objects; j++) {

        if (sr.w->objects[j]->shadow_hit(ray, t) && t < ts){
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

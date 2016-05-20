#include <iostream>
#include "Reflective.h"
#include "PerfectSpecular.h"
#include "Phong.h"

Reflective::Reflective(){
    reflective_brdf = new PerfectSpecular();
}

RGBColor Reflective::shade(ShadeRec & sr){
    RGBColor L(Phong::shade(sr));  // direct illumination

    Vec4 wo = -sr.ray.d;
    Vec4 wi;
    RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
    Ray reflected_ray(sr.hit_point, wi);

    L += fr * sr.w->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (dot(sr.normal, wi));

    return (L);
}

RGBColor Reflective::area_light_shade(ShadeRec & sr){
    RGBColor L(Phong::area_light_shade(sr));  // direct illumination

    Vec4 wo = -sr.ray.d;
    Vec4 wi;
    RGBColor fr = reflective_brdf->sample_f(sr, wo, wi);
    Ray reflected_ray(sr.hit_point, wi);

    L += fr * sr.w->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (dot(sr.normal, wi));

    return (L);
}

RGBColor Reflective::path_shade(ShadeRec & sr){
    Vec4 wo = -sr.ray.d;
    Vec4 wi;
    float pdf;
    RGBColor fr = reflective_brdf->sample_f(sr, wo, wi,pdf);
    Ray reflected_ray(sr.hit_point, wi);
    float ndotwi = dot(sr.normal, wi);

    return (fr * sr.w->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * ndotwi /pdf);

}

Reflective::~Reflective(){
    delete reflective_brdf;
}

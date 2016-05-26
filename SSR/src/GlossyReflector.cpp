#include <iostream>
#include "GlossyReflector.h"
#include "GlossySpecular.h"

using std::cout;
using std::endl;

GlossyReflector::GlossyReflector(){
    glossy_specular_brdf = new GlossySpecular();
}

RGBColor GlossyReflector::area_light_shade(ShadeRec & sr){
    RGBColor L = Phong::area_light_shade(sr);

    Vec4 wo = -sr.ray.d;
    Vec4 wi;
    float pdf;
    RGBColor fr = glossy_specular_brdf->sample_f(sr, wo, wi, pdf);

    Ray reflected_ray(sr.hit_point, wi);
    L += fr * sr.w->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) *
    (dot(sr.normal,wi)) / pdf;

    return (L);
}

RGBColor GlossyReflector::path_shade(ShadeRec & sr){
    Vec4 wo = -sr.ray.d;
    Vec4 wi;
    float pdf;
    RGBColor fr = glossy_specular_brdf->sample_f(sr, wo, wi, pdf);

    Ray reflected_ray(sr.hit_point, wi);
    float ndotwi = dot(sr.normal,wi);

    return (fr * sr.w->tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) *
    (ndotwi) / pdf);
}

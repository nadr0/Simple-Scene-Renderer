#include <iostream>
#include "Matte.h"
#include "World.h"

using std::cout;
using std::endl;

Matte::Matte(){
    ambient_brdf = new Lambertian();
    diffuse_brdf = new Lambertian();
}

RGBColor Matte::shade(ShadeRec & sr){
    Vec4 wo = -sr.ray.d;
    // * Can add world ambient color value for L
	RGBColor L = ambient_brdf->rho(sr, wo) * sr.w->ambient_ptr->L(sr);
	int num_lights = sr.w->lights.size();

	for (int j = 0; j < num_lights; j++) {
		Vec4 wi = sr.w->lights[j]->get_direction(sr);
		float ndotwi = dot(sr.normal, wi);

		if (ndotwi > 0.0){
            bool in_shadow = false;

            Ray shadowRay(sr.hit_point, wi);
            in_shadow = sr.w->lights[j]->in_shadow(shadowRay, sr);

            if(!in_shadow){
                L += diffuse_brdf->f(sr, wo, wi) * sr.w->lights[j]->L(sr) * ndotwi;
            }
        }

	}
	return (L);
}


RGBColor Matte::area_light_shade(ShadeRec & sr){
    Vec4 wo = -sr.ray.d;
    // * Can add world ambient color value for L
    RGBColor L = ambient_brdf->rho(sr, wo) * sr.w->ambient_ptr->L(sr);
    int num_lights = sr.w->lights.size();

    for (int j = 0; j < num_lights; j++) {
        Vec4 wi = sr.w->lights[j]->get_direction(sr);

        float ndotwi = dot(sr.normal, wi);

        if (ndotwi > 0.0){
            bool in_shadow = false;

            Ray shadowRay(sr.hit_point, wi);
            in_shadow = sr.w->lights[j]->in_shadow(shadowRay, sr);

            if(!in_shadow){
                L += diffuse_brdf->f(sr, wo, wi) * sr.w->lights[j]->L(sr) * sr.w->lights[j]->G(sr) * ndotwi / sr.w->lights[j]->pdf(sr);
            }
        }

    }
    return (L);
}

RGBColor Matte::path_shade(ShadeRec & sr){
    Vec4 wi;
    Vec4 wo = -sr.ray.d;

    float pdf;
    RGBColor f = diffuse_brdf->sample_f(sr,wo,wi,pdf);
    float ndotwi = dot(sr.normal,wi);

    Ray reflected_ray(sr.hit_point,wi);

    return (f * sr.w->tracer_ptr->trace_ray(reflected_ray, sr.depth +1) * ndotwi /pdf);

}

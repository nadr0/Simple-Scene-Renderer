#include <iostream>
#include "Phong.h"

using std::cout;
using std::endl;

Phong::Phong(){
    ambient_brdf = new Lambertian();
    diffuse_brdf = new Lambertian();
    specular_brdf = new GlossySpecular();
}


RGBColor Phong::shade(ShadeRec & sr){

    Vec4 wo = -sr.ray.d;
    // * Can add world ambient color value for L
	RGBColor L = ambient_brdf->rho(sr, wo);
	int num_lights = sr.w->lights.size();

	for (int j = 0; j < num_lights; j++) {
		Vec4 wi = sr.w->lights[j]->get_direction(sr);
		float ndotwi = dot(sr.normal, wi);

		if (ndotwi > 0.0){
            bool in_shadow = false;

            Ray shadowRay(sr.hit_point, wi);
            in_shadow = sr.w->lights[j]->in_shadow(shadowRay, sr);

            if(!in_shadow){
                L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr,wo,wi)) * sr.w->lights[j]->L(sr) * ndotwi;
            }
    }


	}

	return (L);

}

RGBColor Phong::area_light_shade(ShadeRec & sr){
    Vec4 wo = -sr.ray.d;
    // * Can add world ambient color value for L
    RGBColor L = ambient_brdf->rho(sr, wo);
    int num_lights = sr.w->lights.size();

    for (int j = 0; j < num_lights; j++) {
        Vec4 wi = sr.w->lights[j]->get_direction(sr);
        float ndotwi = dot(sr.normal, wi);

        if (ndotwi > 0.0){
            bool in_shadow = false;

            Ray shadowRay(sr.hit_point, wi);
            in_shadow = sr.w->lights[j]->in_shadow(shadowRay, sr);

            if(!in_shadow){
                L += (diffuse_brdf->f(sr, wo, wi) + specular_brdf->f(sr,wo,wi))* sr.w->lights[j]->L(sr) * sr.w->lights[j]->G(sr) * ndotwi / sr.w->lights[j]->pdf(sr);
            }
        }


    }
    return (L);
}

Phong::~Phong(){
    delete diffuse_brdf;
    delete specular_brdf;
}

#include "Lambertian.h"
#include "Utility.h"
#include "MultiJitter.h"

Lambertian::Lambertian(){
    kd = 1.0;
    cd = RGBColor(0.0,0.0,0.0);
    // int num_samples = 64;
    // sampler_ptr = new MultiJitter(num_samples);
    // sampler_ptr->map_samples_to_hemisphere(1);
}

void Lambertian::set_kd(float _kd){
    kd = _kd;
}

void Lambertian::set_cd(RGBColor c){
    cd = c;
}

RGBColor Lambertian::rho(ShadeRec & sr, Vec4 & wo){
    return (cd * kd);
}

RGBColor Lambertian::f(ShadeRec & sr, Vec4 & wo, Vec4 & wi){
    return (cd * kd * invPI);
}

RGBColor Lambertian::sample_f(ShadeRec & sr, Vec4 & wo, Vec4 & wi){
    return black;
}

RGBColor Lambertian::sample_f(const ShadeRec& sr, const Vec4& wo, Vec4& wi, float& pdf){
    Vec4 w = sr.normal;

    Vec4 v = cross(Vec4(0.0034, 1, 0.0071),w);
    v = normalize(v);
    Vec4 u = cross(v,w);

    // Building an Orthonormal Basis from a 3D Unit Vector Without Normalization
    // float a = 1.0f/(1.0f + w.z());
    // float b = -w.x()*w.y()*a;
    // Vec4 u = Vec4(b,1.0f - w.y()*w.y()*a, -w.y());
    // Vec4 v = Vec4(1.0f - w.x()*w.x()*a, b, -w.x());

    Vec4 sp = sampler_ptr->sample_hemisphere();
    wi = sp.x() * u + sp.y() * v + sp.z() * w;
    wi = normalize(wi);

    pdf = dot(sr.normal, wi) * invPI;

    return (cd * kd * invPI);
}

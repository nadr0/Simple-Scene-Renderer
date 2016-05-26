#include <iostream>
#include <math.h>
#include "MicrofacetSpecular.h"
#include "MultiJitter.h"
#include "Utility.h"

using std::cout;
using std::endl;

MicrofacetSpecular::MicrofacetSpecular(){
    ks = 0.1;
    cs = RGBColor(1.0,1.0,1.0);
    Fo = RGBColor(1.00,0.86,0.57);
}

RGBColor MicrofacetSpecular::f(ShadeRec & sr, Vec4 & wo, Vec4 & wi){
    return RGBColor(0.0,0.0,0.0);
}

// http://ruh.li/GraphicsCookTorrance.html
RGBColor MicrofacetSpecular::sample_f(ShadeRec& sr, Vec4 & wo, Vec4 & wi){

    wi = normalize(wi);
    wo = normalize(wo);

    float roughnessValue = 0.15; // 0 : smooth, 1: rough
    // half vector
    // incoming light and view direction, half vector between them
    Vec4 h = normalize(wi + wo);


    // Dot products
    float ldoth = dot(wi, h);
    float ndoth = dot(sr.normal, h);
    float ndotv = dot(sr.normal, wo);
    float vdoth = dot(wo,h);
    float ndotl = dot(sr.normal, wi);

    float mSquared = roughnessValue * roughnessValue;

    // Geometric Attenuation
    float NH2 = 2.0 * ndoth;
    float g1 = (NH2 * ndotv)/vdoth;
    float g2 = (NH2 * ndotl)/vdoth;
    float GeoAtt = fmin(1.0,fmin(g1,g2));

    // Beckmann distribution function
    float r1 = 1 / (4.0 * mSquared * pow(ndoth,4.0));
    float r2 = (ndoth * ndoth - 1.0)/(mSquared * ndoth * ndoth);
    float roughness = r1 * exp(r2);

    // Fresnel schlick approximation
    RGBColor RGBFresnel = Fo + (RGBColor(1.0,1.0,1.0) - Fo) * pow(1.0 - vdoth, 5.0);
    // float fresnel = pow(1.0 - vdoth, 5.0);
    // fresnel *= (1.0 - Fo);
    // fresnel += Fo;

    // float brdf = fresnel * GeoAtt * roughness / (ndotv * ndotl * PI);
    RGBColor brdf = RGBFresnel * GeoAtt * roughness / (ndotv * ndotl * PI);

    return (cs * ks * brdf);
 }

 RGBColor MicrofacetSpecular::sample_f(ShadeRec& sr, Vec4 & wo, Vec4 & wi, float & pdf){
     return RGBColor(0.0,0.0,0.0);
 }

RGBColor MicrofacetSpecular::rho(ShadeRec & sr, Vec4 & wo){
    return RGBColor(0.0,0.0,0.0);
}

void MicrofacetSpecular::set_samples(int num_samples, float _exp){
    sampler = new MultiJitter(num_samples);
    sampler->map_samples_to_hemisphere(_exp);
}

void MicrofacetSpecular::set_ks(float _ks){
    ks = _ks;
}

void MicrofacetSpecular::set_cs(RGBColor c){
    cs = c;
}

void MicrofacetSpecular::set_Fo(RGBColor _Fo){
    Fo = _Fo;
}

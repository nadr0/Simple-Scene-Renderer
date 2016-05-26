#ifndef MICROFACETSPECULAR_H_
#define MICROFACETSPECULAR_H_

#include "BRDF.h"
#include "RGBColor.h"

class MicrofacetSpecular : public BRDF{
public:
    MicrofacetSpecular();
    virtual RGBColor f(ShadeRec & sr, Vec4 & wo, Vec4 & wi);
    virtual RGBColor rho(ShadeRec & sr, Vec4 & wo);
    virtual RGBColor sample_f(ShadeRec& sr, Vec4 & wo, Vec4 & wi);
    virtual RGBColor sample_f(ShadeRec& sr, Vec4 & wo, Vec4 & wi, float & pdf);

    void set_ks(float ks);
    void set_cs(RGBColor c);
    void set_samples(int num_samples, float exp);
    void set_Fo(RGBColor Fo);

    Sampler * sampler;

    float ks;
    RGBColor cs;
    RGBColor Fo;
};
#endif

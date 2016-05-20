#ifndef GLOSSYSPECULAR_H_
#define GLOSSYSPECULAR_H_

#include "BRDF.h"
#include "Sampler.h"

class GlossySpecular : public BRDF{
public:
    GlossySpecular();
    virtual RGBColor f(ShadeRec & sr, Vec4 & wo, Vec4 & wi);
    virtual RGBColor rho(ShadeRec & sr, Vec4 & wo);
    virtual RGBColor sample_f(ShadeRec& sr, Vec4 & wo, Vec4 & wi);
    virtual RGBColor sample_f(ShadeRec& sr, Vec4 & wo, Vec4 & wi, float & pdf);

    void set_ks(float ks);
    void set_cs(RGBColor c);
    void set_exp(float exp);
    void set_samples(int num_samples, float exp);

    Sampler * sampler;

    float ks;
    RGBColor cs;
    float exp;
};
#endif

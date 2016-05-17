#ifndef PERFECTSPECULAR_H_
#define PERFECTSPECULAR_H_

#include "BRDF.h"

class PerfectSpecular: public BRDF{
public:
    PerfectSpecular();
    virtual RGBColor f(ShadeRec & sr, Vec4 & wo, Vec4 & wi);
    virtual RGBColor rho(ShadeRec & sr, Vec4 & wo);
    virtual RGBColor sample_f(ShadeRec& sr, Vec4 & wo, Vec4 & wi);
    virtual RGBColor sample_f(const ShadeRec& sr, const Vec4& wo, Vec4& wi, float& pdf);
    float kr;
    RGBColor cr;
};

#endif

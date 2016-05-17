#ifndef BRDF_H_
#define BRDF_H_

#include "Vec4.h"
#include "RGBColor.h"
#include "ShadeRec.h"

class BRDF{
public:
    BRDF();
    virtual RGBColor f(ShadeRec & sr, Vec4 & wo, Vec4 & wi);
    virtual RGBColor rho(ShadeRec & sr, Vec4 & wo);
    virtual RGBColor sample_f(ShadeRec & sr, Vec4 & wo, Vec4 & wi);
    virtual RGBColor sample_f(const ShadeRec& sr, const Vec4& wo, Vec4& wi, float& pdf);
    Sampler* sampler_ptr;
};
#endif

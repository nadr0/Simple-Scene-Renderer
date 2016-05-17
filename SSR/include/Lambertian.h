#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "ShadeRec.h"
#include "Vec4.h"
#include "BRDF.h"

class Lambertian : public BRDF{
public:
    Lambertian();
    virtual RGBColor f(ShadeRec & sr, Vec4 & wo, Vec4 & wi);
    virtual RGBColor rho(ShadeRec & sr, Vec4 & wo);
    virtual RGBColor sample_f(ShadeRec& sr, Vec4 & wo, Vec4 & wi);
    virtual RGBColor sample_f(const ShadeRec& sr, const Vec4& wo, Vec4& wi, float& pdf);
    float kd;
    RGBColor cd;

    void set_kd(float kd);
    void set_cd(RGBColor c);

};

#endif

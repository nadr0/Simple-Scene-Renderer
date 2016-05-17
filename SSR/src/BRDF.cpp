#include "BRDF.h"
#include "RGBColor.h"
#include "Vec4.h"
#include "ShadeRec.h"

BRDF::BRDF(){}

RGBColor BRDF::f(ShadeRec & sr, Vec4 & wo, Vec4 & wi){
    return RGBColor(0.0,0.0,0.0);
}

RGBColor BRDF::rho(ShadeRec & sr, Vec4 & wo){
    return RGBColor(0.0,0.0,0.0);
}

RGBColor BRDF::sample_f(ShadeRec & sr, Vec4 & wo, Vec4 & wi){
    return RGBColor(0.0,0.0,0.0);
}


RGBColor BRDF::sample_f(const ShadeRec& sr, const Vec4& wo, Vec4& wi, float& pdf){
    return RGBColor(0.0,0.0,0.0);
}

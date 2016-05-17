#include <iostream>
#include "PerfectSpecular.h"


PerfectSpecular::PerfectSpecular(){
    kr = 1.0;
    cr = RGBColor(1.0,1.0,1.0);
}

RGBColor PerfectSpecular::f(ShadeRec & sr, Vec4 & wo, Vec4 & wi){
    return RGBColor(0.0,0.0,0.0);
}

RGBColor PerfectSpecular::rho(ShadeRec & sr, Vec4 & wo){
    return RGBColor(0.0,0.0,0.0);
}

RGBColor PerfectSpecular::sample_f(ShadeRec & sr, Vec4 & wo, Vec4 & wi){
    float ndotwo = dot(sr.normal, wo);
	wi = -wo + 2.0 * sr.normal * ndotwo;
	return ((cr * kr) / fabs(dot(sr.normal, wi)));
}

RGBColor PerfectSpecular::sample_f(const ShadeRec& sr, const Vec4& wo, Vec4& wi, float& pdf) {
	float ndotwo = dot(sr.normal, wo);
	wi = -wo + 2.0 * sr.normal * ndotwo;
	pdf = fabs(dot(sr.normal, wi));

	return (cr * kr);
}

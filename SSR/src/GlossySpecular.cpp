#include "GlossySpecular.h"


GlossySpecular::GlossySpecular(){
    ks = 1.0;
    exp = 25.0;
    cs = RGBColor(1.0,1.0,1.0);
}

RGBColor GlossySpecular::f(ShadeRec & sr, Vec4 & wo, Vec4 & wi){
    RGBColor L;
    float ndotwi = dot(sr.normal,wi);
    Vec4 r(-wi + 2.0 * sr.normal * ndotwi);
    r = normalize(r);
    wo = normalize(wo);
    float rdotwo = dot(r,wo);

    if (rdotwo > 0.0){
        L =   cs * ks * pow(rdotwo, exp);
    }
    return (L);
}

 RGBColor GlossySpecular::sample_f(ShadeRec& sr, Vec4 & wo, Vec4 & wi){
     return RGBColor(0.0,0.0,0.0);
 }

RGBColor GlossySpecular::rho(ShadeRec & sr, Vec4 & wo){
    return RGBColor(0.0,0.0,0.0);
}

void GlossySpecular::set_ks(float _ks){
    ks = _ks;
}

void GlossySpecular::set_cs(RGBColor c){
    cs = c;
}

void GlossySpecular::set_exp(float _exp){
    exp = _exp;
}

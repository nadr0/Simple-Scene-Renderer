#include "GlossySpecular.h"
#include "MultiJitter.h"

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

 RGBColor GlossySpecular::sample_f(ShadeRec& sr, Vec4 & wo, Vec4 & wi, float & pdf){

    float ndotwo = dot(sr.normal,wo);
    Vec4 r = -wo + 2.0 * dot(sr.normal,wo) * sr.normal;
    r = normalize(r);
    Vec4 w = r;
    Vec4 u = cross(Vec4(0.00424, 1, 0.00764),w);
    u = normalize(u);
    Vec4 v = cross(u,w);

    Vec4 sp = sampler->sample_hemisphere();
    wi = sp.x() * u + sp.y() * v + sp.z() * w;

    if (dot(sr.normal,wi) < 0.0){
        wi = -sp.x() * u - sp.y() * v + sp.z() * w;
    }

    float phong_lobe = pow(dot(r,wi), exp);
    pdf = phong_lobe * (dot(sr.normal,wi));
    return (cs * ks * phong_lobe);

 }

RGBColor GlossySpecular::rho(ShadeRec & sr, Vec4 & wo){
    return RGBColor(0.0,0.0,0.0);
}

void GlossySpecular::set_samples(int num_samples, float _exp){
    sampler = new MultiJitter(num_samples);
    sampler->map_samples_to_hemisphere(_exp);
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

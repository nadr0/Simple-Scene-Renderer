#ifndef GLOSSYREFLECTOR_H_
#define GLOSSYREFLECTOR_H_

#include "Phong.h"

class GlossyReflector : public Phong{
public:
    GlossyReflector();
    virtual RGBColor area_light_shade(ShadeRec & sr);
    GlossySpecular * glossy_specular_brdf;
    void set_kd(float kd);
    void set_ka(float ka);
    void set_cd(RGBColor c);
    void set_ks(float ks);
    void set_cs(RGBColor c);
    void set_exp(float exp);
    void set_kr(float kr);
    void set_exponent(float exp);
    void set_samples(int num_samples, float exp);
};
#endif

inline void GlossyReflector::set_samples(int num_samples, float exp){
    glossy_specular_brdf->set_samples(num_samples, exp);
}

inline void GlossyReflector::set_kd(float _kd){
    Phong::diffuse_brdf->set_kd(_kd);
}

inline void GlossyReflector::set_ka(float _ka){
    Phong::ambient_brdf->set_kd(_ka);
}

inline void GlossyReflector::set_cd(RGBColor c){
    Phong::ambient_brdf->set_cd(c);
    Phong::diffuse_brdf->set_cd(c);
}

inline void GlossyReflector::set_ks(float _ks){
    Phong::specular_brdf->set_ks(_ks);
}

inline void GlossyReflector::set_cs(RGBColor c){
    Phong::specular_brdf->set_cs(c);
}

inline void GlossyReflector::set_exp(float _exp){
    Phong::specular_brdf->set_exp(_exp);
}

inline void GlossyReflector::set_kr(float _kr){
    glossy_specular_brdf->set_ks(_kr);
}

inline void GlossyReflector::set_exponent(float _exp){
    glossy_specular_brdf->set_exp(_exp);
}

#ifndef REFLECTIVE_H_
#define REFLECTIVE_H_

#include "Phong.h"
#include "PerfectSpecular.h"


class Reflective : public Phong{
public:
    PerfectSpecular * reflective_brdf;
    Reflective();
    virtual RGBColor shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec & sr);
    virtual RGBColor path_shade(ShadeRec & sr);
    ~Reflective();

    void set_kd(float kd);
    void set_ka(float ka);
    void set_cd(RGBColor c);
    void set_ks(float ks);
    void set_cs(RGBColor c);
    void set_exp(float exp);
    void set_kr(float kr);
    void set_cr(RGBColor c);
};
#endif

inline void Reflective::set_cr(RGBColor c){
    reflective_brdf->cr = c;
}

inline void Reflective::set_kr(float _kr){
    reflective_brdf->kr = _kr;
}

inline void Reflective::set_kd(float _kd){
    Phong::diffuse_brdf->set_kd(_kd);
}

inline void Reflective::set_ka(float _ka){
    Phong::ambient_brdf->set_kd(_ka);
}

inline void Reflective::set_cd(RGBColor c){
    Phong::ambient_brdf->set_cd(c);
    Phong::diffuse_brdf->set_cd(c);
}

inline void Reflective::set_ks(float _ks){
    Phong::specular_brdf->set_ks(_ks);
}

inline void Reflective::set_cs(RGBColor c){
    Phong::specular_brdf->set_cs(c);
}

inline void Reflective::set_exp(float _exp){
    Phong::specular_brdf->set_exp(_exp);
}

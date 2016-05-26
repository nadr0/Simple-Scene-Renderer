#ifndef PHONG_H_
#define PHONG_H_

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

class Phong: public Material{
public:
    Lambertian * ambient_brdf;
    Lambertian * diffuse_brdf;
    GlossySpecular * specular_brdf;


    void set_kd(float kd);
    void set_ka(float ka);
    void set_cd(RGBColor c);
    void set_ks(float ks);
    void set_cs(RGBColor c);
    void set_exp(float exp);

    Phong();
    virtual RGBColor shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec & sr);
    ~Phong();
};

inline void Phong::set_kd(float _kd){
    diffuse_brdf->set_kd(_kd);
}

inline void Phong::set_ka(float _ka){
    ambient_brdf->set_kd(_ka);
}

inline void Phong::set_cd(RGBColor c){
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

inline void Phong::set_ks(float _ks){
    specular_brdf->set_ks(_ks);
}

inline void Phong::set_cs(RGBColor c){
    specular_brdf->set_cs(c);
}

inline void Phong::set_exp(float _exp){
    specular_brdf->set_exp(_exp);
}


#endif

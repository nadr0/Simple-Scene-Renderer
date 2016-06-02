#ifndef MICROFACET_H_
#define MICROFACET_H_

#include "MicrofacetSpecular.h"
#include "Lambertian.h"

class Microfacet : public Material{
public:
    Lambertian * ambient_brdf;
    Lambertian * diffuse_brdf;
    MicrofacetSpecular * specular_brdf;

    void set_kd(float kd);
    void set_ka(float ka);
    void set_cd(RGBColor c);
    void set_ks(float ks);
    void set_cs(RGBColor c);

    Microfacet();
    virtual RGBColor area_light_shade(ShadeRec& sr);
    virtual RGBColor shade(ShadeRec & sr);

    ~Microfacet();
};

inline void Microfacet::set_kd(float _kd){
    diffuse_brdf->set_kd(_kd);
}

inline void Microfacet::set_ka(float _ka){
    ambient_brdf->set_kd(_ka);
}

inline void Microfacet::set_cd(RGBColor c){
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

inline void Microfacet::set_ks(float _ks){
    specular_brdf->set_ks(_ks);
}

inline void Microfacet::set_cs(RGBColor c){
    specular_brdf->set_cs(c);
}
#endif

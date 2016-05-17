#ifndef MATTE_H_
#define MATTE_H_

#include "Material.h"
#include "Lambertian.h"
#include "RGBColor.h"

class Matte : public Material{
public:

    Matte();
    virtual RGBColor shade(ShadeRec & sr);
    virtual RGBColor area_light_shade(ShadeRec & sr);
    virtual RGBColor path_shade(ShadeRec & sr);

    void set_kd(float kd);
    void set_ka(float ka);
    void set_cd(RGBColor c);

    Lambertian * ambient_brdf;
    Lambertian * diffuse_brdf;

};

inline void Matte::set_kd(float _kd){
    diffuse_brdf->set_kd(_kd);
}

inline void Matte::set_ka(float _ka){
    ambient_brdf->set_kd(_ka);
}

inline void Matte::set_cd(RGBColor c){
    ambient_brdf->set_cd(c);
    diffuse_brdf->set_cd(c);
}

#endif

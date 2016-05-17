#include "Material.h"

Material::Material(){}

RGBColor Material::shade(ShadeRec & sr){
    return RGBColor(0.0,0.0,0.0);
}

RGBColor Material::get_Le(ShadeRec & sr){
    return RGBColor(0.0,0.0,0.0);
}

RGBColor Material::area_light_shade(ShadeRec & sr){
    return RGBColor(0.0,0.0,0.0);
}

RGBColor Material::path_shade(ShadeRec & sr){
    return RGBColor(0.0,0.0,0.0);
}

inline void Material::set_kd(float _kd){
}

inline void Material::set_ka(float _ka){
}

inline void Material::set_cd(RGBColor c){
}


void Material::set_ks(float _ks){}

void Material::set_cs(RGBColor c){}

void Material::set_exp(float _exp){}

void Material::set_kr(float kr){}

void Material::set_cr(RGBColor c){}

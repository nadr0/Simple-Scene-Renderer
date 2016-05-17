#include "Emissive.h"

Emissive::Emissive(){
    ls = 1.0;
    ce = RGBColor(1.0,1.0,1.0);
}

Emissive::Emissive(float ls, RGBColor ce){
    this->ls = ls;
    this->ce = ce;
}

RGBColor Emissive::shade(ShadeRec &sr){
    return RGBColor(0,0,0);
}

RGBColor Emissive::get_Le(ShadeRec & sr){
    return (ce * ls);
}

RGBColor Emissive::area_light_shade(ShadeRec & sr){
    float ndotd = dot(-sr.normal,sr.ray.d);

    if(ndotd > 0.0){
        return (ce * ls);
    }else{
        return RGBColor(0,0,0);
    }
}

RGBColor Emissive::path_shade(ShadeRec & sr){
    float ndotd = dot(-sr.normal,sr.ray.d);

    if(ndotd > 0.0){
        return (ce * ls);
    }else{
        return RGBColor(0,0,0);
    }
}


void Emissive::set_kd(float kd){}
void Emissive::set_ka(float ka){}
void Emissive::set_cd(RGBColor c){}

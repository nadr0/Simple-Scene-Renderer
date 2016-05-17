#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "ShadeRec.h"

class ShadeRec;

class Material{
public:
    Material();
    virtual RGBColor shade(ShadeRec & sr);
    virtual RGBColor get_Le(ShadeRec & sr);
    virtual RGBColor area_light_shade(ShadeRec & sr);
    virtual RGBColor path_shade(ShadeRec & sr);

    virtual void set_kd(float kd) = 0;
    virtual void set_ka(float ka) = 0 ;
    virtual void set_cd(RGBColor c) = 0;
    virtual void set_ks(float ks);
    virtual void set_cs(RGBColor c);
    virtual void set_exp(float exp);
    virtual void set_kr(float kr);
    virtual void set_cr(RGBColor c);

};
#endif

#ifndef EMISSIVE_H_
#define EMISSIVE_H_

#include "Material.h"

class Emissive: public Material {
public:
    float ls; // Radiance scaling factor
    RGBColor ce; // Color
    Emissive();
    Emissive(float ls, RGBColor ce);
    virtual RGBColor shade(ShadeRec & sr);
    virtual RGBColor get_Le(ShadeRec & sr);
    virtual RGBColor area_light_shade(ShadeRec & sr);
    virtual RGBColor path_shade(ShadeRec & sr);

    virtual void set_kd(float kd);
    virtual void set_ka(float ka);
    virtual void set_cd(RGBColor c);
};

#endif

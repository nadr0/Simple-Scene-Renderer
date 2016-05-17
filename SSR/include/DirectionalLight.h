#ifndef DIRECTIONALLIGHT_H_
#define DIRECTIONALLIGHT_H_

#include "Vec4.h"
#include "ShadeRec.h"
#include "Ray.h"
#include "RGBColor.h"

class DirectionalLight: public Light{

public:
    virtual Vec4 get_direction(ShadeRec & sr);
    virtual RGBColor L(ShadeRec & sr);
    virtual bool in_shadow(Ray & ray, ShadeRec & sr);

    float ls;
    RGBColor color;
    Vec4 direction;

    DirectionalLight();
    DirectionalLight(Vec4 dir, RGBColor c, float ls);
};

#endif

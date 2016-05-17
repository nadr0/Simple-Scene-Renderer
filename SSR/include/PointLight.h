#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_
#include "Vec4.h"
#include "RGBColor.h"
#include "Light.h"

class PointLight: public Light{

public:
    virtual Vec4 get_direction(ShadeRec & sr);
    virtual RGBColor L(ShadeRec & sr);
    virtual bool in_shadow(Ray & ray, ShadeRec & sr);

    float ls;
    RGBColor color;
    Vec4 position;

    PointLight();
    PointLight(Vec4 position, RGBColor color, float ls);

};
#endif

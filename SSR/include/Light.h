#ifndef LIGHT_H_
#define LIGHT_H_

#include "Vec4.h"
#include "ShadeRec.h"
#include "Ray.h"

class ShadeRec;

class Light{
public:

    virtual Vec4 get_direction(ShadeRec & sr);
    virtual RGBColor L(ShadeRec & sr);
    virtual bool in_shadow(Ray & ray, ShadeRec & sr) = 0;
    virtual float G(ShadeRec & sr);
    virtual float pdf(ShadeRec & sr);

    Light();
};


#endif

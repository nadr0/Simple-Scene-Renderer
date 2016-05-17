#ifndef AREALIGHT_H_
#define AREALIGHT_H_

#include "Light.h"

class AreaLight: public Light{
public:

    virtual Vec4 get_direction(ShadeRec & sr);
    virtual RGBColor L(ShadeRec & sr);
    virtual bool in_shadow(Ray & ray, ShadeRec & sr);
    virtual float G(ShadeRec & sr);
    virtual float pdf(ShadeRec & sr);

    AreaLight();

    GeometricObject * obj_ptr; // pointer to object
    Material * material_ptr; // an emissive material
    Vec4 sample_point; // sample point on the surface
    Vec4 light_normal; // normal at sample point
    Vec4 wi; // unit vector from him point to sample
};

#endif
